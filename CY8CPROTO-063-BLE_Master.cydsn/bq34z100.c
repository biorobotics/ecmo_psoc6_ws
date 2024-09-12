/**
 * Biorobotics Lab Project 4.2 Fall 2024
 * @file bq34z100.c
 * @brief Source code for bq34z100EVM / bq34z100G1 BMS chip driver
 *
 * @author: Zhaonan Shi <zhaonans> 
 * @author: Haoran Zheng <hzheng5>
*/

/*include files*/
#include "project.h" 
#include "bq34z100.h" 
#include <inttypes.h>  
#include <stdio.h>  



/* communication functions */

/**
 * @brief  send control command to the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 * @param  control - The control command to send
 *
 */
void sendControlCommand(BQ34Z100_t *device, Control_t control) {
    write_two_bytes(device, COMMAND_CONTROL, control & 0xFF, control >> 8);
}

/**
 * @brief  read the register value
 *
 * @param  device - The BQ34Z100 device struct
 * @param  control - The control command to send
 *
 * @return read value
 */
uint16_t readControlCommand(BQ34Z100_t *device, Control_t control) {
    sendControlCommand(device, control);
    return read(device, COMMAND_CONTROL, 2);
}

/**
 * @brief  write the register value
 *
 * @param  device - The BQ34Z100 device struct
 * @param  command -specific command
 * @param  cmd - value to send
 *
 */
void write(BQ34Z100_t *device, Command_t command, uint8_t cmd) {
    (void) device;
    I2C_MasterSendStart(BQ34Z100, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(command);
    I2C_MasterWriteByte(cmd);
    I2C_MasterSendStop();
}

/**
 * @brief  write the register value with two bytes, in case of 16-bit command
 *
 * @param  device - The BQ34Z100 device struct
 * @param  command -specific command
 * @param  cmd1 - value to send
 * @param  cmd2 - value to send
 *
 */
void write_two_bytes(BQ34Z100_t *device, Command_t command, uint8_t cmd1, uint8_t cmd2) {
    (void) device;
    I2C_MasterSendStart(BQ34Z100, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(command);
    I2C_MasterWriteByte(cmd1);
    I2C_MasterWriteByte(cmd2);
    I2C_MasterSendStop();
}

/**
 * @brief  read the value into 32-bit integer
 *
 * @param  device - The BQ34Z100 device struct
 * @param  command -specific command
 * @param  length - length of the data to read
 *
 * @return read value
 */
uint32_t read(BQ34Z100_t *device, Command_t command, uint8_t length) {
    (void) device;
    uint32_t result = 0;
    I2C_MasterSendStart(BQ34Z100, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(command);
    I2C_MasterSendRestart(BQ34Z100, I2C_READ_XFER_MODE);

    for (uint8_t i = 0; i < length; i++) {
        uint8_t ack = (i == (length - 1)) ? I2C_NAK_DATA : I2C_ACK_DATA;
        uint8_t byte = I2C_MasterReadByte(ack);
        result |= (uint32_t)byte << (8 * i);
    }

    I2C_MasterSendStop();
    return result;
}


/*Main functions*/

/**
 * @brief  get the status of the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return status value
 */
uint16_t BQ34Z100_GetStatus(BQ34Z100_t *device) {
    return readControlCommand(device, CONTROL_CONTROL_STATUS);
}

/**
 * @brief  get the chemical ID of the battery
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return chemical ID
 */
uint16_t BQ34Z100_GetChemID(BQ34Z100_t *device) {
    return readControlCommand(device, CONTROL_CHEM_ID);
}

/**
 * @brief  get the state of health of the battery
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return state of health
 */
uint16_t BQ34Z100_GetStateOfHealth(BQ34Z100_t *device) {
    return read(device, COMMAND_STATEOFHEALTH, 2);
}

/**
 * @brief  get the state of charge of the battery
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return state of charge
 */
uint8_t BQ34Z100_GetSOC(BQ34Z100_t *device) {
    return (uint8_t)read(device, COMMAND_STATEOFCHARGE, 1);
}

/**
 * @brief  get the max error of the battery
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return max error
 */
uint16_t BQ34Z100_GetError(BQ34Z100_t *device) {
    return read(device, COMMAND_MAXERROR, 1);
}

/**
 * @brief  get the battery remaining capacity
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return remaining capacity
 */
uint16_t BQ34Z100_GetRemaining(BQ34Z100_t *device) {
    return read(device, COMMAND_REMAININGCAPACITY, 2);
}

/**
 * @brief  get the battery voltage
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return voltage
 */
uint16_t BQ34Z100_GetVoltage(BQ34Z100_t *device) {
    return read(device, COMMAND_VOLTAGE, 2);
}

/**
 * @brief  get the battery current flow
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return current
 */
int16_t BQ34Z100_GetCurrent(BQ34Z100_t *device) {
    int16_t result = read(device, COMMAND_CURRENT, 2);
    return result < 0 ? -result : result;  // Making sure the result is non-negative
}

/**
 * @brief  get the battery temperature
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return temperature
 */
double BQ34Z100_GetTemperature(BQ34Z100_t *device) {
    int16_t rawTemp = read(device, COMMAND_TEMPERATURE, 2);
    return (rawTemp / 10.0) - 273.15;  // Convert from deci-Kelvin to Celsius
}

/**
 * @brief  get the serial number
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return serial number
 */
int BQ34Z100_GetSerial(BQ34Z100_t *device) {
    return read(device, COMMAND_SERIALNUMBER, 2);
}

/**
 * @brief  reset the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
void BQ34Z100_Reset(BQ34Z100_t *device) {
    sendControlCommand(device, CONTROL_RESET);
    CyDelay(175);  // Wait for the device to reset properly
}

/**
 * @brief  Read the device type
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return device type
 */
uint16_t BQ34Z100_ReadDeviceType(BQ34Z100_t *device) {
    return readControlCommand(device, CONTROL_DEVICE_TYPE);
}

/**
 * @brief  Read the firmware version
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return firmware version
 */
uint16_t BQ34Z100_ReadFWVersion(BQ34Z100_t *device) {
    return readControlCommand(device, CONTROL_FW_VERSION);
}

/**
 * @brief  Read the hardware version
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return hardware version
 */
uint16_t BQ34Z100_ReadHWVersion(BQ34Z100_t *device) {
    return readControlCommand(device, CONTROL_HW_VERSION);
}


/*Calibration functions and flash configurations*/
/*  
    Following functions are unused based on our requirments, 
    Some of the configurations and calibration is achieved by EV2400
    comment the following functions to reduce the code size,
    if needed, uncomment the functions and use them.
*/

/**
 * @brief  enable calibration mode
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_EnableCal(BQ34Z100_t *device) {
    sendControlCommand(device, CONTROL_CAL_ENABLE);
}
*/

/**
 * @brief  enter calibration mode
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_EnterCal(BQ34Z100_t *device) {
    sendControlCommand(device, CONTROL_ENTER_CAL);
}
*/

/**
 * @brief  exit calibration mode
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ExitCal(BQ34Z100_t *device) {
    sendControlCommand(device, CONTROL_EXIT_CAL);
}
*/

/**
 * @brief  enable Inpedance Track
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ITEnable(BQ34Z100_t *device) {
    sendControlCommand(device, CONTROL_IT_ENABLE);
}
*/

/**
 * @brief  unseal the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_Unseal(BQ34Z100_t *device) {
    sendControlCommand(device, CONTROL_UNSEAL_KEY1);
    sendControlCommand(device, CONTROL_UNSEAL_KEY2);
}
*/

/**
 * @brief  seal the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_Seal(BQ34Z100_t *device) {
    sendControlCommand(device, CONTROL_SEALED);
}
*/

/**
 * @brief  change the page of the BQ34Z100 to access different registers
 *
 * @param  device - The BQ34Z100 device struct
 * @param  subclass - The subclass of the page
 * @param  offset - The offset of the page
 *
 */
/*
void BQ34Z100_ChangePage(BQ34Z100_t *device, char subclass, uint16_t offset) {
    CyDelay(10); // Delay 10 milliseconds

    write(device, COMMAND_BLOCKDATACONTROL, 0x00);
    CyDelay(10); // Delay 10 milliseconds

    write(device, COMMAND_DATAFLASHCLASS, subclass);
    device->currFlashPage = subclass;
    CyDelay(10); // Delay 10 milliseconds

    // Select the block offset location
    device->currFlashBlockIndex = (uint8_t)(offset / 32);
    write(device, COMMAND_DATAFLASHBLOCK, device->currFlashBlockIndex);
    CyDelay(20); // Delay 20 milliseconds
}
*/

/**
 * @brief  update the checksum of the BQ34Z100 flash memory
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_UpdateChecksum(BQ34Z100_t *device) {
    uint8_t newChecksum = calcChecksum(device->flashbytes);

    // Send new checksum through I2C
    write(device, COMMAND_BLOCKDATACHECKSUM, newChecksum);
    printf("Writing new checksum for page %" PRIu8 " block %" PRIu8 ": 0x%" PRIx8 "\r\n",
           device->currFlashPage, device->currFlashBlockIndex, newChecksum);

    CyDelay(50); // Wait for BQ34Z100 to process
}
*/

/**
 * @brief  read the flash memory of the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ReadFlash(BQ34Z100_t *device) {
    char command = COMMAND_BLOCKDATA; // Command to read Data Flash

    // Request read flash
    if (I2C_MasterSendStart(BQ34Z100, I2C_WRITE_XFER_MODE) != I2C_MSTR_NO_ERROR) {
        printf("A write error has occurred when transmitting address.\r\n");
        //return;
    }
    I2C_MasterWriteByte(command);
    I2C_MasterSendStop();

    // Read all bytes from page (which is 32 bytes long)
    if (I2C_MasterSendStart(BQ34Z100, I2C_READ_XFER_MODE) != I2C_MSTR_NO_ERROR) {
        printf("A read error has occurred when setting read mode.\r\n");
        return;
    }
    for (int i = 0; i < 32; i++) {
        device->flashbytes[i] = I2C_MasterReadByte((i < 31) ? I2C_ACK_DATA : I2C_NAK_DATA);
    }
    I2C_MasterSendStop();

    // Checksum verification
    uint8_t expectedChecksum = read(device, COMMAND_BLOCKDATACHECKSUM, 1);
    uint8_t calculatedChecksum = calcChecksum(device->flashbytes);

    if (expectedChecksum != calculatedChecksum) {
        printf("ERROR: Checksum of flash memory block does not match. I2C read was likely corrupted.\r\n");
    }

    printf("Page %" PRIu8 " block %" PRIu8 " contents:", device->currFlashPage, device->currFlashBlockIndex);
    for (size_t byteIndex = 0; byteIndex < 32; ++byteIndex) {
        printf(" %" PRIx8, device->flashbytes[byteIndex]);
    }
    printf("\r\n");
    printf("Checksum: 0x%" PRIx8 "\r\n", expectedChecksum);

    CyDelay(10); // Wait to ensure I2C bus stability or BQ34Z100 processing
}
*/

/**
 * @brief  write to the flash memory of the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_WriteFlash(BQ34Z100_t *device, uint8_t index, uint32_t value, int len) {
    // Ensure index is within the valid range
    if (index > 31) index %= 32;

    // Write to I2C bus and update the flashbytes array at the same time
    if (len == 1) {
        device->flashbytes[index] = (uint8_t)value;
        write(device, COMMAND_BLOCKDATA + index, (unsigned char)value);
        printf("Flash[%d] <- 0x%" PRIx8 "\n", index, device->flashbytes[index]);
    } else if (len > 1) {
        // Process every byte except the last
        for (int i = 0; i < len - 1; i++) {
            device->flashbytes[index + i] = (uint8_t)(value >> (8 * ((len - 1) - i)));
            printf("Flash[%d] <- 0x%" PRIx8 "\n", index + i, device->flashbytes[index + i]);
            write(device, COMMAND_BLOCKDATA + index + i, device->flashbytes[index + i]);
        }
        // Last byte (lower byte)
        device->flashbytes[index + len - 1] = (uint8_t)(value & 0xFF);
        printf("Flash[%d] <- 0x%" PRIx8 "\n", index + len - 1, device->flashbytes[index + len - 1]);
        write(device, COMMAND_BLOCKDATA + index + len - 1, device->flashbytes[index + len - 1]);
    }
}
*/

/**
 * @brief  retrieve the pointer to the flashbytes array
 *
 * @param  device - The BQ34Z100 device struct
 * @return pointer to the flashbytes array
 */
/*
uint8_t* BQ34Z100_GetFlashBytes(BQ34Z100_t *device) {
    return device->flashbytes;
}
*/

/**
 * @brief  Change to Page 48 and update design capacity and energy
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ChangePage48(BQ34Z100_t *device) {
    BQ34Z100_ChangePage(device, 48, 0);
    BQ34Z100_ReadFlash(device);
    BQ34Z100_WriteFlash(device, 11, DESIGNCAP, 2);
    BQ34Z100_WriteFlash(device, 13, DESIGNENERGY, 2);
    BQ34Z100_UpdateChecksum(device);
    CyDelay(300);  // Delay for 300ms for settings to take effect
}
*/

/**
 * @brief  Change to Page 64 and modify configuration settings
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ChangePage64(BQ34Z100_t *device) {
    BQ34Z100_ChangePage(device, 64, 0);
    BQ34Z100_ReadFlash(device);

    uint8_t packConfig_high = device->flashbytes[0];
    uint8_t packConfig_low = device->flashbytes[1];

    if (VOLTSEL) {
        packConfig_high |= 0x08;
    }
    packConfig_high |= 0x40;  

    packConfig_low &= ~(1);
    packConfig_low |= USE_EXTERNAL_THERMISTOR;

    BQ34Z100_WriteFlash(device, 0, packConfig_high, 1);
    BQ34Z100_WriteFlash(device, 1, packConfig_low, 1);

    uint8_t packConfigB = device->flashbytes[2];
    packConfigB &= ~1;  
    BQ34Z100_WriteFlash(device, 2, packConfigB, 1);

    BQ34Z100_WriteFlash(device, 4, LEDCONFIG, 1);
    BQ34Z100_WriteFlash(device, 7, 0x04, 1);  
    BQ34Z100_UpdateChecksum(device);
    CyDelay(300);
}
*/

/**
 * @brief  Change to Page 80 and adjust load configuration
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ChangePage80(BQ34Z100_t *device) {
    BQ34Z100_ChangePage(device, 80, 0);
    BQ34Z100_ReadFlash(device);

    BQ34Z100_WriteFlash(device, 0, LOADSELECT, 1);
    BQ34Z100_WriteFlash(device, 1, LOADMODE, 1);
    BQ34Z100_WriteFlash(device, 10, 10, 2);
    BQ34Z100_UpdateChecksum(device);
    CyDelay(300);

    BQ34Z100_ChangePage(device, 80, 53);
    BQ34Z100_ReadFlash(device);

    BQ34Z100_WriteFlash(device, 53, ZEROCHARGEVOLT, 2);
    BQ34Z100_UpdateChecksum(device);
    CyDelay(300);
}
*/

/**
 * @brief  Change to Page 82 and update QMax
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ChangePage82(BQ34Z100_t *device) {
    BQ34Z100_ChangePage(device, 82, 0);
    BQ34Z100_ReadFlash(device);
    BQ34Z100_WriteFlash(device, 0, QMAX0, 2);
    BQ34Z100_UpdateChecksum(device);
    CyDelay(300);
}
*/

/**
 * @brief  Calibrate the voltage divider
 *
 * @param  device - The BQ34Z100 device struct
 * @param  currentVoltage - The current voltage
 *
 * @return the new voltage divider value
 */
/*
uint16_t BQ34Z100_CalibrateVoltage(BQ34Z100_t *device, uint16_t currentVoltage) {
    BQ34Z100_ChangePage(device, 104, 0);
    BQ34Z100_ReadFlash(device);

    // Gets the voltage divider value stored in flash
    uint16_t flashVoltage = (uint16_t)(device->flashbytes[14] << 8);
    flashVoltage |= (uint16_t)(device->flashbytes[15]);

    float readVoltage = (float)BQ34Z100_GetVoltage(device);
    float newSetting = ((float)(currentVoltage) / readVoltage) * (float)(flashVoltage);
    uint16_t writeSetting; // This 2-byte integer will be written to the chip
    if (newSetting > 65535.0f) {
        writeSetting = 65535;
    } else if (newSetting < 0.0f) {
        writeSetting = 0;
    } else {
        writeSetting = (uint16_t)(newSetting);
    }
    BQ34Z100_WriteFlash(device, 14, writeSetting, 2);
    BQ34Z100_UpdateChecksum(device);
    CyDelay(10); // Delay for 10ms

    BQ34Z100_ChangePage(device, 68, 0);
    BQ34Z100_ReadFlash(device);

    int16_t oldUpdateOK = 0;
    oldUpdateOK |= (uint16_t)(device->flashbytes[0] << 8);
    oldUpdateOK |= device->flashbytes[1];

    int16_t newUpdateOK = (int16_t)(round(FLASH_UPDATE_OK_VOLT * CELLCOUNT * (5000.0f / writeSetting)));
    printf("Changing Flash Update OK Voltage from %" PRIi16 " to %" PRIi16 "\r\n", oldUpdateOK, newUpdateOK);

    BQ34Z100_WriteFlash(device, 0, newUpdateOK, 2);
    BQ34Z100_UpdateChecksum(device);

    // Test output
    printf("Register (voltage divider): %d\r\n", flashVoltage);
    printf("New Ratio: %f\r\n", ((float)(currentVoltage) / readVoltage));
    printf("READ VOLTAGE (mv): %f\r\n", readVoltage);
    return writeSetting;
}
*/

/**
 * @brief  Reset the voltage divider
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_ResetVoltageDivider(BQ34Z100_t *device) {
    BQ34Z100_ChangePage(device, 104, 0); // Change to page 104, offset 0
    BQ34Z100_ReadFlash(device); // Read current settings from flash
    BQ34Z100_WriteFlash(device, 14, RESETVOLTAGE, 2); // Write the RESETVOLTAGE value to the appropriate register
    BQ34Z100_UpdateChecksum(device); // Update checksum to ensure data integrity
    CyDelay(300); // Wait for 300ms for settings to take effect
}
*/

/**
 * @brief  Calibrate the shunt resistor
 *
 * @param  device - The BQ34Z100 device struct
 * @param  calCurrent - The calibration current
 *
 */
/*
void BQ34Z100_CalibrateShunt(BQ34Z100_t *device, int16_t calCurrent) {
    if (calCurrent < 0) calCurrent = -calCurrent;

    int16_t currentReading = BQ34Z100_GetCurrent(device);
    if (currentReading < 0) currentReading = -currentReading;

    BQ34Z100_ChangePage(device, 104, 0); // Change to page 104, offset 0 as per table 11 in datasheet
    BQ34Z100_ReadFlash(device); // Read current settings from flash
    CyDelay(30); // Wait for 30ms

    // Read and convert CC Gain
    uint32_t currentGainDF = ((uint32_t)device->flashbytes[0] << 24) | ((uint32_t)device->flashbytes[1] << 16) |
                             ((uint32_t)device->flashbytes[2] << 8) | (uint32_t)device->flashbytes[3];
    float currentGainResistance = (4.768f / xemicsToFloat(currentGainDF));

    uint32_t currentDeltaDF = ((uint32_t)device->flashbytes[4] << 24) | ((uint32_t)device->flashbytes[5] << 16) |
                              ((uint32_t)device->flashbytes[6] << 8) | (uint32_t)device->flashbytes[7];
    float currentDeltaResistance = (5677445 / xemicsToFloat(currentGainDF));

    float newGain = (((float)currentReading) / ((float)calCurrent)) * currentGainResistance;

    uint32_t newGainDF = floatToXemics(4.768 / newGain);
    float DeltaDF = floatToXemics(5677445 / newGain);

    printf("currentGainDF = 0x%" PRIx32 ", currentGainResistance = %f, currentDeltaDF = %" PRIx32 ", currentDeltaResistance = %f, newGain = %f, newGainDF = 0x%" PRIx32 "\n",
           currentGainDF, currentGainResistance, currentDeltaDF, currentDeltaResistance, newGain, newGainDF);

    BQ34Z100_WriteFlash(device, 0, newGainDF, 4);
    BQ34Z100_WriteFlash(device, 4, DeltaDF, 4);

    BQ34Z100_UpdateChecksum(device);
    CyDelay(300); // Delay for 300ms for settings to take effect
}
*/

/**
 * @brief  Set the sense resistor, for resetting the shunt resistor
 *
 * @param  device - The BQ34Z100 device struct
 *
 */
/*
void BQ34Z100_SetSenseResistor(BQ34Z100_t *device) {
    BQ34Z100_ChangePage(device, 104, 0);
    BQ34Z100_ReadFlash(device);
    CyDelay(30); // Delay to ensure data is ready

    // Constants used to convert mOhm to the BQ34Z100 data flash units
    uint32_t GainDF = floatToXemics(4.768 / SENSE_RES);
    uint32_t DeltaDF = floatToXemics(5677445 / SENSE_RES);
    BQ34Z100_WriteFlash(device, 0, GainDF, 4);
    BQ34Z100_WriteFlash(device, 4, DeltaDF, 4);

    printf("newGain = %f, GainDF = 0x%" PRIx32 "\n", SENSE_RES, GainDF);

    BQ34Z100_UpdateChecksum(device);
    CyDelay(300); // Wait for changes to take effect
}
*/



/**
 * @brief  Convert float to Xemics floating point format
 *
 * @param  value - The float value to convert
 * 
 * @return Xemics floating point format
 */
/*
uint32_t floatToXemics(float value) {
    int iByte1, iByte2, iByte3, iByte4, iExp;
    bool bNegative = false;
    float fMantissa;
    
    // Handle zero input
    if (value == 0) value = 0.00001F;

    if (value < 0) {
        bNegative = true;
        value = -value;
    }

    // Calculate exponent
    iExp = (int)(log(value) / log(2) + 1);

    // MS byte is the exponent + 0x80
    iByte1 = iExp + 128;

    // Calculate mantissa
    fMantissa = value / pow(2, iExp);
    fMantissa = fMantissa / pow(2, -24);

    // Convert mantissa into three bytes
    iByte2 = (int)(fMantissa / pow(2, 16));
    iByte3 = (int)((fMantissa - (iByte2 * pow(2, 16))) / pow(2, 8));
    iByte4 = (int)(fMantissa - (iByte2 * pow(2, 16)) - (iByte3 * pow(2, 8)));

    // Apply sign bit condition
    if (!bNegative) {
        iByte2 = iByte2 & 0x7F;
    }

    return (uint32_t)(iByte1 << 24 | iByte2 << 16 | iByte3 << 8 | iByte4);
}
*/

/**
 * @brief  Convert Xemics floating point format to float
 *
 * @param  xemics - The Xemics floating point format
 * 
 * @return float value
 */
/*
float xemicsToFloat(uint32_t xemics) {
    bool bIsPositive = true;
    float fExponent, fResult;
    uint8_t vMSByte = (uint8_t)(xemics >> 24);
    uint8_t vMidHiByte = (uint8_t)(xemics >> 16);
    uint8_t vMidLoByte = (uint8_t)(xemics >> 8);
    uint8_t vLSByte = (uint8_t)xemics;

    // Determine sign from the mid-high byte
    if (vMidHiByte & 0x80) {
        bIsPositive = false;
    }

    // Extract exponent
    fExponent = pow(2, (vMSByte - 128));

    // Restore mantissa
    vMidHiByte |= 0x80;
    fResult = vMidHiByte * 65536 + vMidLoByte * 256 + vLSByte;
    fResult = fResult * pow(2, -24); // Convert to fraction
    fResult = fResult * fExponent;   // Apply exponent

    // Apply sign
    return bIsPositive ? fResult : -fResult;
}
*/

/**
 * @brief  Get the current calibration status
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return calibration status
 */
/*
uint8_t BQ34Z100_GetUpdateStatus(BQ34Z100_t *device) {
    BQ34Z100_ChangePage(device, 82, 0); // Change to page 82, offset 0
    BQ34Z100_ReadFlash(device); // Read the data from flash into the buffer
    return device->flashbytes[4]; // Return the status byte from the flash memory buffer
}
*/

/**
 * @brief  Get the flags of the BQ34Z100
 *
 * @param  device - The BQ34Z100 device struct
 * 
 * @return flags
 */
/*
BQ34Z100_Flags_t BQ34Z100_GetFlags(BQ34Z100_t *device) {
    uint16_t flags = read(device, COMMAND_FLAGS, 2);
    uint16_t flagsB = read(device, COMMAND_FLAGSB, 2);

    BQ34Z100_Flags_t result;
    result.flagA = flags;
    result.flagB = flagsB;

    return result;
}
*/

/**
 * @brief  Calculate the checksum of the flash memory
 *
 * @param  flashbytes - The flash memory bytes
 * 
 * @return checksum
 */
/*
uint8_t calcChecksum(uint8_t *flashbytes) {
    uint8_t sum = 0;
    for (int i = 0; i < 32; i++) {
        sum += flashbytes[i];
    }
    return 255 - sum;
}
*/




