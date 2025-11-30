/*******************************************************
 * Arduino UNO/NANO + PZEM-004T v3 + DHT11 + SSD1306 OLED  
 * Shows:
 *   Voltage (V), Current (A), Power (W),
 *   PF, Frequency (Hz), Temperature (°C)
 *******************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>
SoftwareSerial pzemSerial(8, 9);  // RX=8, TX=9
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(pzemSerial);

// OLED CONFIG
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long lastRead = 0;

void safePrintLine(const String &label, float val, const String &unit, int y) {
  display.setCursor(0, y);
  if (isnan(val)) {
    display.print(label + ": --");
  } else {
    display.print(label + ": ");
    display.print(val);
    display.print(" " + unit);
  }
}

void setup() {
  Serial.begin(9600);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND!");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 5);
  display.println("Arduino Power Monitor");
  display.display();
  delay(1500);

  // DHT start
  dht.begin();

  // PZEM Serial start
  pzemSerial.begin(9600);

  delay(500);
}

void loop() {
  if (millis() - lastRead < 1000) return;
  lastRead = millis();

  float voltage = pzem.voltage();
  float current = pzem.current();
  float power   = pzem.power();
  float pf      = pzem.pf();
  float freq    = pzem.frequency();
  float tempC   = dht.readTemperature();

  display.clearDisplay();
  display.setTextSize(1);

  safePrintLine("V", voltage, "V", 10);
  safePrintLine("I", current, "A", 20);
  safePrintLine("P", power,   "W", 30);

  // PF + Frequency
  display.setCursor(0, 40);
  if (isnan(pf)) display.print("PF: --");
  else display.print("PF: " + String(pf, 2));

  display.setCursor(65, 40);
  if (isnan(freq)) display.print("F: --");
  else display.print("F: " + String(freq, 1) + "Hz");

  // Temp
  display.setCursor(0, 52);
  if (isnan(tempC)) display.print("Temp: --");
  else {
    display.print("Temp: ");
    display.print(tempC);
    display.print((char)247);
    display.print("C");
  }

  display.display();

  // Debug to Serial
  Serial.print("V="); Serial.print(voltage);
  Serial.print(" I="); Serial.print(current);
  Serial.print(" P="); Serial.print(power);
  Serial.print(" PF="); Serial.print(pf);
  Serial.print(" F="); Serial.print(freq);
  Serial.print(" T="); Serial.println(tempC);
}
