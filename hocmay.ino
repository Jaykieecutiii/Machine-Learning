#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

TwoWire I2C_INA = TwoWire(0);
TwoWire I2C_OLED = TwoWire(1);

Adafruit_INA219 ina219;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2C_OLED, -1);

// dữ liệu đo
float voltage = 0;
float current = 0;
float mAh = 0;

unsigned long lastTime = 0;

// dữ liệu từ Python
float SOH = 100;
float SOH_future = 100;

void setup() {
  Serial.begin(115200);

  // INA219: SDA 21, SCL 22
  I2C_INA.begin(21, 22, 100000);
  if (!ina219.begin(&I2C_INA)) {
    Serial.println("INA219 FAIL");
    while (1);
  }

  // OLED SSD1306: SDA 18, SCL 19
  I2C_OLED.begin(18, 19, 100000);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED FAIL");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Battery ML Ready");
  display.display();

  lastTime = millis();
  delay(1000);
}

void loop() {
  voltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA() / 1000.0; // A

  unsigned long now = millis();
  float dt = (now - lastTime) / 3600000.0; // hour
  lastTime = now;

  if (current > 0) {
    mAh += current * dt * 1000.0;
  }

  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int p = data.indexOf(',');

    if (p > 0) {
      SOH = data.substring(0, p).toFloat();
      SOH_future = data.substring(p + 1).toFloat();
    }
  }

  // gửi sang Python: voltage,current,time,mAh
  // Đúng thứ tự model đang dùng: voltage,current,time,mAh
  Serial.print(voltage); Serial.print(",");
  Serial.print(current); Serial.print(",");
  Serial.print(now / 1000.0); Serial.print(",");
  Serial.println(mAh);

  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("V: "); display.print(voltage, 2); display.println("V");

  display.setCursor(0, 10);
  display.print("I: "); display.print(current, 2); display.println("A");

  display.setCursor(0, 20);
  display.print("mAh: "); display.print(mAh, 2);

  display.setCursor(0, 32);
  display.print("SOH: "); display.print(SOH, 2); display.println("%");

  display.setCursor(0, 44);
  display.print("Next: "); display.print(SOH_future, 2); display.println("%");

  display.display();

  delay(1000);
}