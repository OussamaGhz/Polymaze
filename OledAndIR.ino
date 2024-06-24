#include "OledAndIR.h"

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int OLED_I2C_ADDRESS = 0x3C;

int thresholdBlack = 0;
int thresholdBlue = 2000;
int thresholdRed = 3000;
int lastSensorValues[5] = {0, 0, 0, 0, 0};

void initializeDisplayAndSensors() {
  Wire.begin(21, 22);
  Serial.begin(9600);
  while (!Serial);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();

  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(irSensor3, INPUT);
  pinMode(irSensor4, INPUT);
  pinMode(irSensor5, INPUT);

  displayCalibrationSquares();
}

void runOnce() {
  thresholdBlack = calculateThreshold();

  int sensorValues[5];
  sensorValues[0] = analogRead(irSensor1);
  sensorValues[1] = analogRead(irSensor2);
  sensorValues[2] = analogRead(irSensor3);
  sensorValues[3] = analogRead(irSensor4);
  sensorValues[4] = analogRead(irSensor5);

  updateCalibrationSquares(sensorValues);

  for (int i = 0; i < 5; i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(sensorValues[i]);
    Serial.print(" - ");
  }
  Serial.println(" - ");
}

void displayCalibrationSquares() {
  display.clearDisplay();

  int squareSize = 16;
  int spacing = 8;
  int y = (SCREEN_HEIGHT / 2) - (squareSize / 2);

  for (int i = 0; i < 5; i++) {
    int x = i * (squareSize + spacing);
    display.drawRect(x, y, squareSize, squareSize, SSD1306_WHITE);
  }

  display.display();
}

void updateCalibrationSquares(int sensorValues[]) {
  bool needUpdate = false;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] != lastSensorValues[i]) {
      needUpdate = true;
      break;
    }
  }

  if (!needUpdate) {
    return;
  }

  display.clearDisplay();

  int squareSize = 16;
  int spacing = 8;
  int y = (SCREEN_HEIGHT / 2) - (squareSize / 2);

  for (int i = 0; i < 5; i++) {
    int x = i * (squareSize + spacing);
    if (sensorValues[i] >= thresholdBlack) {
      display.fillRect(x, y, squareSize, squareSize, SSD1306_WHITE);
    } else {
      display.drawRect(x, y, squareSize, squareSize, SSD1306_WHITE);
    }
  }

  display.display();

  for (int i = 0; i < 5; i++) {
    lastSensorValues[i] = sensorValues[i];
  }
}

int calculateThreshold() {
  long sensorValue1 = analogRead(irSensor1);
  long sensorValue2 = analogRead(irSensor2);
  long sensorValue3 = analogRead(irSensor3);
  long sensorValue4 = analogRead(irSensor4);
  long sensorValue5 = analogRead(irSensor5);

  long total = sensorValue1 + sensorValue2 + sensorValue3 + sensorValue4 + sensorValue5;
  int averageValue = total / 5;

  return averageValue;
}
