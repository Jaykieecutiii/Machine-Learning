import serial
import csv

ser = serial.Serial("COM5", 115200, timeout=1)

with open("battery_data.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)

    writer.writerow(["voltage", "current", "mAh", "time", "SOH"])

    while True:
        raw = ser.readline()

        try:
            line = raw.decode("utf-8", errors="ignore").strip()

            if not line or line.count(",") != 3:
                continue

            v, i, mAh, t = line.split(",")

            v = float(v)
            i = float(i)
            mAh = float(mAh)
            t = float(t)

            soh = max(100 - mAh / 10, 0)

            writer.writerow([v, i, mAh, t, soh])

            print(f"Saved: {v} {i} {mAh} SOH: {soh}")

        except Exception as e:
            print("Error:", e)