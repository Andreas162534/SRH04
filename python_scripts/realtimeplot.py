import serial
import matplotlib.pyplot as plt
import re

# COM-Port anpassen! z. B. "COM3" oder "/dev/ttyUSB0"
ser = serial.Serial("COM5", 9600)

plt.ion()
fig, ax = plt.subplots()
ax.set_xlabel("X [cm]")
ax.set_ylabel("Y [cm]")
ax.set_xlim(-5, 60)
ax.set_ylim(-5, 60)
ax.grid(True)

line, = ax.plot([], [], 'ro-', markersize=5)
x_data, y_data = []

pattern = re.compile(r"X:\s*([0-9.]+).*Y:\s*([0-9.]+)")

while True:
    raw = ser.readline().decode().strip()

    match = re.search(r"X:\s*([0-9.]+)\s*cm, Y:\s*([0-9.]+)\s*cm", raw)
    if match:
        x = float(match.group(1))
        y = float(match.group(2))

        x_data.append(x)
        y_data.append(y)

        line.set_xdata(x_data)
        line.set_ydata(y_data)
        ax.set_title(f"X={x:.1f} cm,  Y={y:.1f} cm")

        plt.pause(0.01)
