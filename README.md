# T-Beam Location Tracker Prototype

Arduino-based location tracking prototype using the LilyGo T-Beam LoRa32 development board with integrated GPS and OLED display.

## Overview

This project is a prototype for a physical location tracker that combines GPS positioning with real-time visual feedback via an OLED display. The T-Beam platform provides the foundation for future enhancements including LoRa long-range communication, battery management, and portable tracking capabilities.

## Hardware

### Main Board
- **LilyGo T-Beam LoRa32** (AXP2101 V1.2)
  - ESP32-based microcontroller
  - Integrated u-blox GPS module
  - LoRa radio (SX1276/SX1278)
  - AXP2101 power management chip
  - Battery charging circuit

### Display
- **SSD1306 OLED Display** (128x64 pixels, I2C)
  - SDA: GPIO 21
  - SCL: GPIO 22

### GPS Module
- **u-blox GPS** (NEO-6M/NEO-M8N)
  - TX: GPIO 12
  - RX: GPIO 34
  - External antenna required

## Features

### Current Implementation
- ✅ Real-time GPS data acquisition
- ✅ OLED display with live updates
- ✅ Satellite tracking (count and signal quality)
- ✅ Location display (latitude/longitude)
- ✅ Altitude and speed monitoring
- ✅ Serial debug output

### Display Information
- Number of satellites in view
- HDOP (Horizontal Dilution of Precision - accuracy indicator)
- Current GPS coordinates (6 decimal places)
- Altitude in meters
- Speed in km/h

### Future Enhancements
- LoRa communication for long-range tracking
- Data logging to SD card or cloud
- Battery status monitoring
- Geofencing alerts
- Movement detection
- Low-power sleep modes

## Software Requirements

### Arduino IDE
- **Version:** 2.3.6 or later
- **Board Support:** ESP32 by Espressif Systems
  - Install via: Tools → Board → Boards Manager → Search "ESP32"

### Required Libraries
Install via Tools → Manage Libraries:

1. **Adafruit SSD1306** - OLED display driver
2. **Adafruit GFX Library** - Graphics primitives
3. **TinyGPSPlus** - GPS NMEA sentence parsing

## Installation

### 1. Hardware Setup
```
1. Ensure GPS antenna is securely connected to the U.FL connector
2. Connect T-Beam to computer via USB-C cable
3. Verify OLED display is properly seated (if removable)
```

### 2. Arduino IDE Configuration
```
1. Open Arduino IDE 2.3.6
2. Install ESP32 board support (if not already installed)
3. Select board: Tools → Board → ESP32 Arduino → "T-Beam"
4. Select port: Tools → Port → [Your COM port]
5. Install required libraries (see above)
```

### 3. Upload Sketch
```
1. Open the .ino file
2. Click "Upload" button (or Ctrl+U)
3. Wait for compilation and upload to complete
4. Open Serial Monitor (115200 baud) for debug output
```

## Usage

### First Time Setup
1. **Upload the sketch** to your T-Beam
2. **Go outdoors** - GPS requires clear view of the sky
3. **Wait 30-60 seconds** for initial GPS fix (cold start)
4. **Watch the display** for satellite acquisition

### Normal Operation
- **OLED Display** shows real-time GPS data
- **Serial Monitor** (115200 baud) shows detailed debug info
- **Green/Blue LED** on T-Beam indicates GPS activity

### Troubleshooting

#### "Waiting for GPS..." stays on screen
- ✓ Check antenna connection
- ✓ Go outdoors with clear sky view
- ✓ Wait 1-2 minutes for satellite acquisition
- ✓ Verify GPS module power (should have LED)

#### OLED shows "SSD1306 allocation failed"
- ✓ Check I2C connections
- ✓ Try changing I2C address to 0x3D in code
- ✓ Verify display is properly seated

#### No Serial output
- ✓ Check correct COM port selected
- ✓ Verify baud rate is 115200
- ✓ Try pressing reset button on T-Beam

## Technical Details

### Pin Configuration
```cpp
// I2C (OLED Display)
SDA: GPIO 21
SCL: GPIO 22

// GPS UART
GPS_RX: GPIO 34
GPS_TX: GPIO 12

// LoRa (not used in this prototype)
LoRa_SCK: GPIO 5
LoRa_MISO: GPIO 19
LoRa_MOSI: GPIO 27
LoRa_CS: GPIO 18
LoRa_RST: GPIO 23
LoRa_DIO0: GPIO 26
```

### GPS Data Format
- **Update Rate:** 1 Hz (once per second)
- **Coordinate Precision:** 6 decimal places (~0.11m accuracy)
- **Protocol:** NMEA 0183
- **Baud Rate:** 9600

### Power Consumption
- Active tracking: ~120-150mA
- Can be powered by USB or 18650 battery
- Battery life: 8-12 hours (depends on battery capacity)

## Development Roadmap

### Phase 1: Basic Tracking (Current)
- [x] GPS acquisition
- [x] OLED display
- [ ] Serial debugging

### Phase 2: Communication
- [ ] WiFi location broadcast functionality
- [ ] Bluetooth Low Energy location broadcast functionality
- [ ] Receive remote tracker data

### Phase 3: Data Management
- [ ] SD card logging
- [ ] Track history storage
- [ ] Waypoint marking

### Phase 4: Power Management
- [ ] Battery monitoring
- [ ] Deep sleep modes
- [ ] Wake on movement

### Phase 5: Advanced Features
- [ ] Geofencing
- [ ] Speed alerts
- [ ] Distance calculation
- [ ] Multi-tracker support
- [ ] Emergency beacons

## Contributing
This is a prototype project. Suggestions and improvements are welcome!

## License
Copyright (c) 2025 Mike Edukonis

### Terms

This software is provided for **educational and non-commercial use only**.

The Libraries being used in v1.0:
- Adafruit SSD1306 - BSD License
- Adafruit GFX - BSD License
- TinyGPSPlus - LGPL v2.1
- Arduino Core - LGPL v2.1

**Permitted:**
- Personal use and experimentation
- Educational purposes
- Non-commercial research

**Prohibited without written permission:**
- Commercial use or distribution
- Integration into commercial products
- Patent rights are explicitly reserved by the copyright holder

**Patent Notice:**
This software may be covered by pending patent applications. Use of this software does not grant any patent license or rights.

For commercial licensing inquiries, contact: medukonis@yahoo.com

## Acknowledgments
- LilyGo for the T-Beam hardware platform
- Adafruit for display libraries
- Mikal Hart for TinyGPSPlus library

## Support
For issues or questions:
1. Check the Troubleshooting section above
2. Review LilyGo T-Beam documentation
3. Open an issue on this repository

## Version History
- **v1.0** - Initial prototype with GPS and OLED display

---

**Note:** This is prototype software intended for development and testing. For production deployment, additional error handling, power management, and security features should be implemented.
