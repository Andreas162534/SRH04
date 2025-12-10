import serial
import csv

# CHANGE THIS TO YOUR PORT:
PORT = "COM5"
BAUD = 9600

ser = serial.Serial(PORT, BAUD)

with open("log.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["dA", "dB", "x", "y"])  # header

    print("Logging... Press CTRL+C to stop.")

    while True:
        line = ser.readline().decode().strip()
        if not line:
            continue

        values = line.split(",")
        writer.writerow(values)
        print(values)
