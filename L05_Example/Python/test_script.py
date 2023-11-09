import serial
import time
import matplotlib.pyplot as plt

def send_message(ser, message):
    ser.write(message.encode())
    print(f"Sent: {message}")

def read_message(ser):
    message = ser.read(10).decode().strip()
    print(f"Read: {message}")
    return float(message)

def plot_data(x_values, y_values, title='Plot', xlabel='X-axis', ylabel='Y-axis'):
    plt.plot(x_values, y_values, marker='.')
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.show()

def main():
    # Replace 'COM1' with your actual serial port
    serial_port = 'COM10'
    baud_rate = 115200

    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    dutys = range(0, 101, 1)
    readout = []
    try:
        for value in dutys:
            message = f'd{value:03}'
            send_message(ser, message)
            time.sleep(0.2)
            send_message(ser, 'read')
            readout.append( read_message(ser) )

    except KeyboardInterrupt:
        pass
    finally:
        ser.close()
    print("Done.")
    plot_data(dutys, readout, 'LED-BH1750 characteristic', 'Duty cycle [%]', 'Illuminance [lux]')
        

if __name__ == "__main__":
    main()
