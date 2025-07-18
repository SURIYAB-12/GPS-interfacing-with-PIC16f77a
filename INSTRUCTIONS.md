# 📘 GPS Interfacing with PIC16F877A – Instructions & Working

This document explains in detail how the **uBlox G7020 GPS module** communicates using **USART (UART)** and how we extract **location coordinates** using **PIC16F877A** and display them on a **16x2 LCD**.

---

## 🛰 Getting Location Data from GPS

The uBlox GPS module transmits **NMEA formatted strings** over UART at **9600 baud**.

A sample data stream looks like this (when viewed on a UART terminal):

$GPRMC,141848.00,A,2237.63306,N,08820.86316,E,0.553,,100418,,,A73
$GPVTG,,T,,M,0.553,N,1.024,K,A27
$GPGGA,141848.00,2237.63306,N,08820.86316,E,1,03,2.56,1.9,M,-54.2,M,,74
$GPGSA,A,2,06,02,05,,,,,,,,,,2.75,2.56,1.0002
$GPGSV,1,1,04,02,59,316,30,05,43,188,25,06,44,022,23,25,03,324,76
$GPGLL,2237.63306,N,08820.86316,E,141848.00,A,A65


Out of these, we only care about the sentence starting with `$GPGGA` because it contains:

- UTC Time  
- Latitude  
- Longitude  
- Fix quality  
- Number of satellites  
- Altitude

---

## 🔍 Understanding `$GPGGA` Sentence

Here is a sample GPGGA line:

$GPGGA,141848.00,2237.63306,N,08820.86316,E,1,03,2.56,1.9,M,-54.2,M,,*74


### Field Breakdown:

| Field No. | Data             | Meaning                             |
|-----------|------------------|-------------------------------------|
| 1         | `$GPGGA`         | Global Positioning Fix Data         |
| 2         | `141848.00`      | UTC Time → 14:18:48.00              |
| 3         | `2237.63306`     | Latitude degrees-minutes            |
| 4         | `N`              | North/South                         |
| 5         | `08820.86316`    | Longitude degrees-minutes           |
| 6         | `E`              | East/West                           |
| 7         | `1`              | Fix Quality (0: Invalid, 1: Valid)  |
| 8         | `03`             | No. of satellites used              |
| 9–13      | ...              | Altitude, geoidal separation etc.   |

> For our project, we only need Field 3, 4 (Latitude) and Field 5, 6 (Longitude)

---

## 🔁 Step-by-Step Procedure

### ✅ Microcontroller Setup

1. **Configure oscillator**: Use 20 MHz crystal with capacitors.
2. **Set TRIS registers**: Set PORTB for LCD, and RC7 as RX.
3. **Initialize LCD**: In 4-bit mode with cursor OFF.
4. **Initialize UART**:
   - Baud rate: 9600
   - RX only
   - Continuous reception mode

---

## 📥 Data Reception Logic

1. Continuously read characters from UART using a loop.
2. Check if incoming character is `$`.
3. If yes, then buffer next characters and check if the first 6 characters match `GPGGA,`.
4. Once `GPGGA` is confirmed:
   - Skip time field.
   - Start saving characters to `latitude[]` until `N` is received.
   - Skip the comma.
   - Start saving characters to `longitude[]` until `E` is received.
5. Display latitude and longitude on the LCD.

---

## 🧪 Example Output on LCD

LAT: 2237.63306 N
LON: 08820.86316 E


This shows raw NMEA format coordinates.
- **Latitude** → 22°37.63306′ N
- **Longitude** → 88°20.86316′ E

---

## 📝 Notes

- `$GPRMC` sentence also contains position, speed, and date — can be used if needed.
- `$GPGGA` is preferred for accuracy and altitude data.
- Always wait for **fix quality = 1** to ensure valid data.
- Ignore lines starting with `$GPGSV`, `$GPGSA`, etc.

---

## 🔄 Optional Enhancements

- Convert DDMM.MMMM format to Decimal Degrees
- Print Altitude using GPGGA field 9
- Implement UART interrupt-based reception
- Store coordinates to SD card or EEPROM

---

## 📌 Summary

This project teaches how to:
- Interface GPS with PIC microcontroller over UART
- Parse NMEA strings manually
- Extract only required fields
- Display live GPS location on 16x2 LCD

You can now modify this logic to include more features like:
- SMS location using GSM
- Data logging
- Google Maps integration

---

