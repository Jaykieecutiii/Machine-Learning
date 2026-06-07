import serial
import time
import pandas as pd
import joblib
model = joblib.load("soh_model.pkl")
ser = serial.Serial("COM5", 115200, timeout=1)
time.sleep(2)

print("Connected ESP32...")
def parse_line(line):
    try:
        v, i, mAh, t = line.split(",")
        return float(v), float(i), float(mAh), float(t)
    except:
        return None
soh_smooth = None

while True:
    line = ser.readline().decode(errors="ignore").strip()

    if not line:
        continue

    data = parse_line(line)
    if data is None:
        continue

    v, i, mAh, t = data
    input_df = pd.DataFrame([[v, i, t, mAh]],
                            columns=["voltage", "current", "time", "mAh"])
    soh_pred = model.predict(input_df)[0]
    if soh_smooth is None:
        soh_smooth = soh_pred
    else:
        soh_smooth = 0.7 * soh_smooth + 0.3 * soh_pred

    soh_next = soh_smooth - 0.15
    ser.write(f"{soh_smooth:.2f},{soh_next:.2f}\n".encode())

    print(f"V={v:.2f} I={i:.2f} mAh={mAh:.2f} | SOH={soh_smooth:.2f} NEXT={soh_next:.2f}")

    time.sleep(0.2)