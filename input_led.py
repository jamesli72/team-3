from gpiozero import LED
from time import sleep

# Define GPIO pin for the LED
led_pin = 17  # GPIO17 (BCM pin numbering)

# Create LED object
led = LED(led_pin)

# Function to handle user input
def handle_user_input():
    while True:
        user_input = input("Enter 'on' to turn LED on, 'off' to turn LED off, or 'exit' to quit: ").strip().lower()
        
        if user_input == 'on':
            led.on()
            print("LED is ON")
        elif user_input == 'off':
            led.off()
            print("LED is OFF")
        elif user_input == 'exit':
            print("Exiting program")
            break
        else:
            print("Invalid input. Please enter 'on', 'off', or 'exit'.")

try:
    # Call function to handle user input
    handle_user_input()

except KeyboardInterrupt:
    print("\nProgram terminated by user")

finally:
    # Ensure the LED is turned off before exiting
    led.off()
