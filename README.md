# Battery Health Prediction using ESP32 and Machine Learning
## Giới thiệu
Đây là đồ án Machine Learning trong Robotics với mục tiêu xây dựng hệ thống giám sát và dự đoán độ chai pin (State of Health - SOH) theo thời gian thực.
Hệ thống sử dụng ESP32 kết hợp cảm biến INA219 để thu thập dữ liệu điện áp, dòng điện và dung lượng tiêu thụ của pin. Dữ liệu được gửi về máy tính để huấn luyện mô hình Machine Learning và dự đoán tình trạng pin.
## Phần cứng sử dụng
* ESP32 DevKit V1
* Cảm biến INA219
* Màn hình OLED SSD1306 0.96"
* Pin Lithium 3S 12V
* Module sạc/BMS
* Động cơ DC 12V (tải thử nghiệm)
## Kiến trúc hệ thống
ESP32 → INA219 → Python → Machine Learning Model → ESP32 → OLED
Chức năng:
* Đo điện áp pin
* Đo dòng điện
* Tính dung lượng tiêu thụ (mAh)
* Lưu dữ liệu thành dataset CSV
* Huấn luyện mô hình Machine Learning
* Dự đoán SOH hiện tại
* Dự đoán xu hướng SOH tương lai
* Hiển thị kết quả trên OLED
## Cấu trúc thư mục
hocmay/
│
├── battery_data.csv      # Dataset thu thập từ ESP32
├── hocmay.ino            # Chương trình điều khiển ESP32
├── mlmodel.py            # Huấn luyện mô hình Machine Learning
├── nhandulieutocsv.py    # Thu thập dữ liệu và lưu vào file CSV
├── sendtoesp.py          # Dự đoán SOH và gửi kết quả về ESP32
└── soh_model.pkl         # Mô hình Machine Learning đã huấn luyện
## Cài đặt thư viện
### Python
pip install pandas numpy scikit-learn pyserial joblib
### Arduino IDE
Cài đặt:

* Adafruit INA219
* Adafruit SSD1306
* Adafruit GFX
## Hướng dẫn sử dụng
### Bước 1: Upload code ESP32
Nạp chương trình ESP32 bằng Arduino IDE.
### Bước 2: Thu thập dữ liệu
Chạy:
python nhandulieutocsv.py

Dữ liệu sẽ được lưu vào:

battery_data.csv

### Bước 3: Huấn luyện mô hình

Chạy:

python mlmodel.py

Kết quả:

soh_model.pkl

### Bước 4: Dự đoán thời gian thực

Chạy:

python sendtoesp.py

Hệ thống sẽ:

* Nhận dữ liệu từ ESP32
* Dự đoán SOH
* Gửi kết quả về ESP32
* Hiển thị trên OLED


## Dataset

Các thuộc tính:

| Feature | Ý nghĩa             |
| ------- | ------------------- |
| voltage | Điện áp pin (V)     |
| current | Dòng điện (A)       |
| time    | Thời gian (s)       |
| mAh     | Dung lượng tích lũy |
| SOH     | Độ khỏe pin (%)     |

## Kết quả

Ví dụ đầu ra:

V=12.11 I=0.78 mAh=25.75 | SOH=97.26 NEXT=97.11

Mô hình Random Forest đạt độ chính xác cao trên tập dữ liệu thử nghiệm.


## Hướng phát triển

* Tích hợp cảm biến nhiệt độ pin
* Áp dụng LSTM cho dữ liệu chuỗi thời gian
* Tối ưu chạy TinyML trên ESP32
* Xây dựng Dashboard Web theo dõi từ xa

## Tác giả

Họ tên: LÊ XUÂN NAM

Mã sinh viên: 2321060003

Môn học: Machine Learning for Robotics

Trường: Đại học Mỏ Địa CHất
