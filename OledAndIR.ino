#include "OledAndIR.h"
#include "Motors.h"

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int OLED_I2C_ADDRESS = 0x3C;

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
  pinMode(ledPin, OUTPUT); // Set the LED pin as output

  displayCalibrationSquares();
}

void runOnce() {
  int sensorValues[5];
  sensorValues[0] = analogRead(irSensor1);
  sensorValues[1] = analogRead(irSensor2);
  sensorValues[2] = analogRead(irSensor3);
  sensorValues[3] = analogRead(irSensor4);
  sensorValues[4] = analogRead(irSensor5);

  updateCalibrationSquares(sensorValues);
  controlMotorsAndBuzzer(sensorValues);

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
  display.clearDisplay();

  int squareSize = 16;
  int spacing = 8;
  int y = (SCREEN_HEIGHT / 2) - (squareSize / 2);

  for (int i = 0; i < 5; i++) {
    int x = i * (squareSize + spacing);
    if (sensorValues[i] >= thresholds[i]) {
      display.fillRect(x, y, squareSize, squareSize, SSD1306_WHITE);
    } else {
      display.drawRect(x, y, squareSize, squareSize, SSD1306_WHITE);
    }
  }

  display.display();

  // Update lastSensorValues for comparison in the next iteration
  for (int i = 0; i < 5; i++) {
    lastSensorValues[i] = sensorValues[i];
  }
}

int calculateThreshold(int sensorPin) {
  long totalBlack = 0;
  long totalWhite = 0;
  int readings = 5;

  // Take readings on black surface
  digitalWrite(ledPin, HIGH); // Turn on LED
  Serial.println("Place the sensor on a black surface.");
  delay(2000); // Give time to place the sensor
  for (int i = 0; i < readings; i++) {
    totalBlack += analogRead(sensorPin);
    delay(100); // Small delay between readings
  }

  // Take readings on white surface
  digitalWrite(ledPin, LOW); // Turn off LED
  Serial.println("Place the sensor on a white surface.");
  delay(2000); // Give time to place the sensor
  for (int i = 0; i < readings; i++) {
    totalWhite += analogRead(sensorPin);
    delay(100); // Small delay between readings
  }

  long averageBlack = totalBlack / readings;
  long averageWhite = totalWhite / readings;

  return (averageBlack + averageWhite) / 2;
}

int * calibrateRobot() {
  displayCalibrationSquares();

  // Calibrate each sensor individually
  thresholds[0] = calculateThreshold(irSensor1);
  thresholds[1] = calculateThreshold(irSensor2);
  thresholds[2] = calculateThreshold(irSensor3);
  thresholds[3] = calculateThreshold(irSensor4);
  thresholds[4] = calculateThreshold(irSensor5);

  // Display real-time sensor values during calibration
  unsigned long startTime = millis();
  unsigned long calibrationDuration = 4000;  // 30 seconds
  int sensorValues[5];

  while (millis() - startTime < calibrationDuration) {
    sensorValues[0] = analogRead(irSensor1);
    sensorValues[1] = analogRead(irSensor2);
    sensorValues[2] = analogRead(irSensor3);
    sensorValues[3] = analogRead(irSensor4);
    sensorValues[4] = analogRead(irSensor5);

    updateCalibrationSquares(sensorValues);

    // Optionally, print sensor values to Serial for debugging
    Serial.print("Sensor Values: ");
    for (int i = 0; i < 5; i++) {
      Serial.print(sensorValues[i]);
      Serial.print(" ");
    }
    Serial.println();

    // Add a small delay to prevent overwhelming the system with readings
    delay(100);  // Adjust delay as needed
  }

  // Display final threshold values after calibration
  Serial.println("Final Thresholds:");
  for (int i = 0; i < 5; i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(thresholds[i]);
  }

  return thresholds;
}
