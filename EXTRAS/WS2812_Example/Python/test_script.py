import serial
import time

# Define the serial port and baud rate
ser = serial.Serial('COM9', 115200) 

# Initialize the value to start from 0
value = 0

try:
    while True:
        # Format the value as a 3-character string with leading zeros
        data = f"{value:03d}"

        # Send the formatted data over the serial port
        ser.write(data.encode())

        # Increment the value by 5
        value = (value + 5) % 181  # Ensure it stays in the range 000-180

        # Wait for 50 ms
        time.sleep(0.05)

except KeyboardInterrupt:
    print("Script terminated by user.")
finally:
    ser.close()
