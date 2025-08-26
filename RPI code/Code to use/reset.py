import lgpio
import time

# Define the GPIO pin connected to the PSoC reset
RESET_PIN = 17

# Open the GPIO chip
h = lgpio.gpiochip_open(0)

# Set up the GPIO pin as an output
lgpio.gpio_claim_output(h, RESET_PIN)

def reset_psoc():
    # Pull the reset pin low
    lgpio.gpio_write(h, RESET_PIN, 0)
    time.sleep(2)
    # Release the reset pin
    lgpio.gpio_write(h, RESET_PIN, 1)
    print("PSoC has been reset.")

try:
    # Perform the reset
    reset_psoc()
finally:
    # Clean up GPIO settings
    lgpio.gpiochip_close(h)
