import serial
import time
import matplotlib.pyplot as plt
import json

def send_duty(ser, message):
    message = str(message)
    ser.write(message.encode())
    print(f"Sent: {message}")

def read_temperature(ser):
    message = ser.readline().decode().strip()
    print(f"Read: {message}")
    message = json.loads(message)
    return message["temperature"]

def plot_data(x_values, y_values, title='Plot', xlabel='X-axis', ylabel='Y-axis'):
    plt.plot(x_values, y_values, marker='.')
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.show()

def main():
    # Replace 'COM1' with your actual serial port
    serial_port = 'COM8'
    baud_rate = 115200

    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    send_duty(ser, 100)
    readout = []
    timestamps = []
    t = 0
    ts = 1 
    try:
        while True:
            readout.append( read_temperature(ser) )
            timestamps.append(t)
            t = t + ts

    except KeyboardInterrupt:
        pass
    finally:
        ser.close()
    print("Done.")
    plot_data(timestamps, readout, 'Resistive heater-BMP280 step response', 'Time [s]', 'Temperature [degC]')
        

if __name__ == "__main__":
    main()
