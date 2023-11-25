import serial
import time
import matplotlib.pyplot as plt

def send_message(ser, message):
    ser.write(message.encode())
    print(f"Sent: {message}")


def main():
    # Replace 'COM1' with your actual serial port
    serial_port = 'COM8'
    baud_rate = 115200

    ser = serial.Serial(serial_port, baud_rate, timeout=1)

    try:
        while True:
            for x in range(8):
                message = '\001'
                send_message(ser, message)
                time.sleep(0.2)
                message = '\002'
                send_message(ser, message)
                time.sleep(0.2)
            for x in range(8):
                message = '\002'
                send_message(ser, message)
                time.sleep(0.2)
                message = '\001'
                send_message(ser, message)
                time.sleep(0.2)

    except KeyboardInterrupt:
        pass
    finally:
        ser.close()

if __name__ == "__main__":
    main()
