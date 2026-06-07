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

```text
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

Cài đặt các thư viện cần thiết bằng lệnh:

```bash
pip install pandas numpy scikit-learn pyserial joblib
```

### Arduino IDE

Cài đặt các thư viện sau trong Library Manager:

* Adafruit INA219
* Adafruit SSD1306
* Adafruit GFX

---

## Hướng dẫn sử dụng

### Bước 1: Nạp chương trình cho ESP32

Mở file `hocmay.ino` bằng Arduino IDE, chọn đúng loại bo mạch ESP32 và cổng COM tương ứng, sau đó tiến hành nạp chương trình.

### Bước 2: Thu thập dữ liệu

Chạy chương trình:

```bash
python nhandulieutocsv.py
```

Dữ liệu đo được từ cảm biến INA219 sẽ được lưu vào file:

```text
battery_data.csv
```

### Bước 3: Huấn luyện mô hình Machine Learning

Chạy chương trình:

```bash
python mlmodel.py
```

Sau khi huấn luyện hoàn tất, hệ thống sẽ tạo ra file mô hình:

```text
soh_model.pkl
```

### Bước 4: Dự đoán thời gian thực

Chạy chương trình:

```bash
python sendtoesp.py
```

Hệ thống sẽ thực hiện:

* Nhận dữ liệu từ ESP32 thông qua giao tiếp Serial
* Dự đoán trạng thái sức khỏe pin (SOH)
* Dự đoán xu hướng suy giảm SOH trong tương lai
* Gửi kết quả trở lại ESP32
* Hiển thị kết quả trên màn hình OLED

---

## Dataset

Bộ dữ liệu được thu thập trực tiếp từ hệ thống phần cứng thực tế sử dụng ESP32 và cảm biến INA219.

| Feature | Ý nghĩa                   |
| ------- | ------------------------- |
| voltage | Điện áp pin (V)           |
| current | Dòng điện sạc/xả (A)      |
| time    | Thời gian hoạt động (s)   |
| mAh     | Dung lượng tích lũy (mAh) |
| SOH     | Độ khỏe pin (%)           |

---

## Kết quả thực nghiệm

Ví dụ kết quả dự đoán thời gian thực:

```text
V=12.11 I=0.78 mAh=25.75 | SOH=97.26 NEXT=97.11
```

Mô hình Random Forest cho kết quả dự đoán ổn định với độ chính xác cao trên tập dữ liệu thu thập được từ hệ thống.

---

## Hướng phát triển

* Tích hợp cảm biến nhiệt độ pin để nâng cao độ chính xác
* Áp dụng mô hình LSTM cho dữ liệu chuỗi thời gian
* Tối ưu mô hình để triển khai trực tiếp trên ESP32 bằng TinyML
* Xây dựng giao diện Dashboard Web để theo dõi và giám sát từ xa
* Mở rộng hệ thống cho các loại pin Lithium dung lượng lớn

---

## Tác giả

**Họ và tên:** Lê Xuân Nam

**Mã sinh viên:** 2321060003

**Môn học:** Machine Learning for Robotics

**Trường:** Đại học Mỏ - Địa chất

