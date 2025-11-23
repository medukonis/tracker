/*
 * OLED Display + GPS Test for T-Beam
 * Uses SSD1306 128x64 OLED + NEO-6M/NEO-M8N GPS
 * SDA: Pin 21, SCL: Pin 22
 * GPS TX: Pin 12, GPS RX: Pin 34
 * 
 * Required Libraries: 
 * - Adafruit SSD1306
 * - Adafruit GFX Library
 * - TinyGPSPlus (Install via Library Manager)
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// GPS pins for T-Beam
#define GPS_RX_PIN 34
#define GPS_TX_PIN 12

// Create objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TinyGPSPlus gps;
HardwareSerial GPS(1);  // Use UART1

unsigned long lastUpdate = 0;
int satellites = 0;
bool gpsDataReceived = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("T-Beam OLED + GPS Test");
  
  // Initialize I2C
  Wire.begin(21, 22);
  
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  
  Serial.println("OLED initialized!");
  
  // Initialize GPS
  GPS.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Serial.println("GPS initialized, waiting for data...");
  
  // Show startup screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("T-Beam GPS Test");
  display.println();
  display.println("Searching for");
  display.println("satellites...");
  display.display();
  
  delay(2000);
}

void loop() {
  // Read GPS data
  while (GPS.available() > 0) {
    char c = GPS.read();
    gps.encode(c);
    gpsDataReceived = true;
    // Uncomment to see raw NMEA data in Serial Monitor:
    // Serial.write(c);
  }
  
  // Update display every second
  if (millis() - lastUpdate > 1000) {
    lastUpdate = millis();
    updateDisplay();
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  if (!gpsDataReceived) {
    display.println("Waiting for GPS...");
    display.println();
    display.println("Check:");
    display.println("- Antenna connected");
    display.println("- Clear sky view");
    display.println("- Wait 30-60 sec");
    display.display();
    Serial.println("No GPS data received yet");
    return;
  }
  
  // Display GPS status
  display.print("Sats: ");
  display.println(gps.satellites.value());
  
  display.print("HDOP: ");
  if (gps.hdop.isValid())
    display.println(gps.hdop.hdop());
  else
    display.println("N/A");
  
  display.println("---");
  
  // Location
  if (gps.location.isValid()) {
    display.print("Lat: ");
    display.println(gps.location.lat(), 6);
    display.print("Lng: ");
    display.println(gps.location.lng(), 6);
  } else {
    display.println("Lat: ---");
    display.println("Lng: ---");
  }
  
  // Altitude
  display.print("Alt: ");
  if (gps.altitude.isValid()) {
    display.print(gps.altitude.meters(), 1);
    display.println("m");
  } else {
    display.println("---");
  }
  
  // Speed
  display.print("Spd: ");
  if (gps.speed.isValid()) {
    display.print(gps.speed.kmph(), 1);
    display.println("km/h");
  } else {
    display.println("---");
  }
  
  display.display();
  
  // Print to Serial Monitor
  Serial.print("Satellites: ");
  Serial.print(gps.satellites.value());
  if (gps.location.isValid()) {
    Serial.print(" | Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" | Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(" | Alt: ");
    Serial.print(gps.altitude.meters(), 1);
    Serial.println("m");
  } else {
    Serial.println(" | No GPS fix yet");
  }
}