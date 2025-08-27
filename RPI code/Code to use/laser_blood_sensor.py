import serial
import os
import asyncio
import serial_asyncio
from datetime import datetime, timezone, timedelta
import numpy as np
from questdb.ingress import Sender, TimestampNanos

# Constants and Configurations
LOG_DIRECTORY = "/home/pas/Desktop/ecmo/log"
LASER_SENSOR_PORT = "/dev/serial/by-id/usb-Arduino_Nano_ESP32_ECDA3B60AD8C-if01"
LASER_SENSOR_BAUDRATE = 115200


class OutputProtocol(asyncio.Protocol):
    def connection_made(self, transport):
        self.transport = transport
        print("Port opened", transport)
        self.data = None
        self.lines = []


    def data_received(self, data):
        if b'\n' in data:
            if self.data is None:
                self.data = b""
                return
        if self.data is not None:
            self.data += data
            loc = self.data.find(b'\r\n')
            while loc >= 0:
                line = self.data[:loc].decode('utf-8').split(',')
                line[0] = datetime.now(timezone.utc)
                line[1:] = [int(v) for v in line[1:]]
                self.lines.append(line)
                self.data = self.data[loc+2:]
                loc = self.data.find(b'\r\n')

    
    def pause_reading(self):
        self.transport.pause_reading()

    def resume_reading(self):
        self.transport.resume_reading()

    def get_lines(self):
        lines = self.lines[:]
        self.lines = []
        return lines

    def connection_lost(self, exc):
        print("Port closed")
        self.transport.loop.stop()

async def reader():
    current_log_path = None
    fileio = None
    transport, protocol = await serial_asyncio.create_serial_connection(
            loop,
            OutputProtocol,
            LASER_SENSOR_PORT,
            LASER_SENSOR_BAUDRATE,
    )

    
    while True:
        await asyncio.sleep(1)
        filepath = generate_filename()
        if current_log_path != filepath:
            if fileio is not None:
                fileio.close()
            fileio = open(filepath, 'w')
            current_log_path = filepath
        with Sender.from_env() as sender:
            for line in protocol.get_lines():
                fileio.write(line[0].isoformat())
                for val in line[1:]:
                    fileio.write("," + str(val))
                fileio.write("\n")
                sender.row(
                    "2025_08_28_sheep_laser_sensor",
                    columns={"L680_1": line[1], "L850_1": line[2], "L680_2": line[3], "L850_2": line[4]},
                    at=TimestampNanos.from_datetime(line[0]),
                )
            sender.flush()   
        protocol.resume_reading()
    
    fileio.close()

def generate_filename():
    """
    Generate a filename based on the current date and hour.

    Returns:
        str: The full path to the log file.
    """
    # Ensure the directory exists; create it if it doesn't
    if not os.path.exists(LOG_DIRECTORY):
        os.makedirs(LOG_DIRECTORY)
        print(f"Created directory: {LOG_DIRECTORY}")
    current_time = datetime.now(timezone.utc).isoformat()[:11]
    # current_time = time.strftime("%Y-%m-%d_%H")  # e.g., 2024-10-31_16
    filename = f"laser_data_log_{current_time}.txt"
    return os.path.join(LOG_DIRECTORY, filename)

if __name__ == "__main__":

    # ser = serial.Serial(port)
    # data = ser.readline().decode().strip()

    loop = asyncio.get_event_loop()
    transport, protocol = loop.run_until_complete(reader())
    loop.close()
