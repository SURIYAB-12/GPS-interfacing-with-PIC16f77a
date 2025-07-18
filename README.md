# 📡 GPS Interfacing with PIC16F877A using uBlox G7020

This is a simple embedded systems project where I interfaced the **uBlox G7020 GPS module** with the **PIC16F877A** microcontroller. The goal was to receive **real-time GPS coordinates** over UART and display the **latitude and longitude** on a **16x2 LCD display**.

The project helped me understand UART communication, NMEA sentence parsing, and LCD interfacing in embedded C.

---

## 🧠 Project Overview

- **Microcontroller**: PIC16F877A  
- **GPS Module**: uBlox G7020 (NMEA output)  
- **Display**: 16x2 LCD (4-bit mode)  
- **Communication**: UART @ 9600 baud  
- **Toolchain**: MPLAB IDE + Hi-Tech C  
- **Programmer**: PICkit 2 (v2.61)

---

## 📷 Final Output

The LCD shows live GPS coordinates in this format:

LAT: 1234.5678 N
LON: 09876.5432 E


Note: These are in **raw NMEA format (DDMM.MMMM)**.

---

## 🔧 Components Used

| Component              | Quantity |
|------------------------|----------|
| PIC16F877A Microcontroller | 1      |
| uBlox G7020 GPS Module | 1        |
| 16x2 LCD Display       | 1        |
| 20 MHz Crystal Oscillator | 1     |
| 33pF Capacitors        | 2        |
| 10kΩ Potentiometer     | 1        |
| Breadboard & Wires     | As required |
| 5V DC Power Supply     | 1        |
| PICkit 2 Programmer    | 1        |

---

## 🔌 Circuit Connections

| GPS Module | PIC16F877A |
|------------|------------|
| TX         | RC7 (RX)   |
| VCC        | +5V        |
| GND        | GND        |

| LCD Pin | PIC Pin |
|---------|---------|
| RS      | RB0     |
| RW      | RB1     |
| E       | RB2     |
| D4–D7   | RB4–RB7 |

> LCD is connected in 4-bit mode. UART is set to 9600 baud.

---

## ⚙️ How It Works

1. **GPS Module** transmits continuous NMEA sentences over UART.
2. The **PIC16F877A** receives data via its **RC7 (RX)** pin.
3. It checks for the **`$GPGGA`** sentence which contains location data.
4. Extracts **Latitude** and **Longitude** fields.
5. Displays both values on the **16x2 LCD**.

---

## 🗂 File Structure

📁 gps-pic16f877a
├── main.c # Main source file
├── lcd.c # LCD function definitions
├── lcd.h # LCD header file
├── schematic.png # Circuit diagram 
└── README.md # Project documentation


---

## 🔄 Future Improvements

- Convert GPS format from DDMM.MMMM to Decimal Degrees
- Show Altitude and UTC Time from NMEA sentence
- Log GPS data to SD card or EEPROM
- Send coordinates to mobile app via GSM or Bluetooth
- Replace LCD with I2C OLED display to save GPIOs

---

## 📚 References

- [CircuitDigest GPS with PIC16F877A](https://circuitdigest.com/microcontroller-projects/gps-interfacing-with-pic16f877a)
- uBlox G7020 GPS Datasheet  
- MPLAB IDE and Hi-Tech C Compiler Documentation  

---

## 🙋‍♂️ About Me

I created this project as part of my embedded systems learning journey. It helped me understand:

- UART data parsing
- LCD control using 4-bit interface
- Handling external serial devices with PIC microcontroller

Feel free to fork or use the code for your own experiments!

---


