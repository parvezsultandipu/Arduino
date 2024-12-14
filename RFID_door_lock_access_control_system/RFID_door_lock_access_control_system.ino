/*
Author: Parvez Sultan  
Student, Department of EEE, Independent University, Bangladesh (IUB)  
Chairperson, IEEE IUB RAS  
Research Assistant (RA)- Sensor Instrument, Robotics, Biomedical Engineering, APPLIED ELECTROMAGNETICS RESEARCH GROUP (AERG), AI & Bio - Sensor Research Lab & Telecommunication Satellite Engineering.
Description: RFID door lock access control system   
*/


#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

// Pin definitions
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

// LCD pin definitions
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// LED pin
const int ledPin = 8;

// Authorized RFID card UID (replace with your own)
byte authorizedUID[] = {0xDE, 0xAD, 0xBE, 0xEF}; // Example UID

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize RFID reader
  SPI.begin();
  rfid.PCD_Init();
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Scan your card");
  
  // Initialize LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Look for a new RFID card
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Display UID on Serial Monitor
    Serial.print("UID:");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    
    // Check if the scanned card is authorized
    if (isAuthorized(rfid.uid.uidByte, rfid.uid.size)) {
      lcd.clear();
      lcd.print("Access Granted");
      digitalWrite(ledPin, HIGH); // Simulate door lock opening
      delay(5000); // Keep the door open for 5 seconds
      digitalWrite(ledPin, LOW); // Simulate door lock closing
    } else {
      lcd.clear();
      lcd.print("Access Denied");
      delay(2000);
    }
    
    // Stop reading the card
    rfid.PICC_HaltA();
  }
}

bool isAuthorized(byte *uid, byte uidSize) {
  if (uidSize != sizeof(authorizedUID)) {
    return false;
  }
  for (byte i = 0; i < uidSize; i++) {
    if (uid[i] != authorizedUID[i]) {
      return false;
    }
  }
  return true;
}
