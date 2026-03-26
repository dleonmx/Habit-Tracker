# 🧠 Automatic Habit Tracker (Hardware-Based)

## 📌 Overview
The **Automatic Habit Tracker** is a dedicated hardware device designed to reduce friction in daily habit tracking. Instead of relying on apps, it provides a **simple, tactile interface** that allows users to log habits quickly and receive immediate visual feedback.

The system emphasizes **speed, clarity, and consistency**, making habit tracking more engaging and less distracting than digital alternatives.

---

## 🎯 Features
- 📺 TFT display with icon-based habit visualization  
- 🎛️ Rotary encoder for intuitive navigation and input  
- 🌈 NeoPixel LEDs to display habit streak history  
- 🔄 Automatic daily reset using internet time sync  
- 💾 Non-volatile storage (ESP32 Preferences) to retain data  
- ⚡ Standalone device (no phone required)

---

## 🧩 How It Works
- Each habit is represented by an icon on the TFT screen  
- Habits start as **red (incomplete)**  
- Pressing the rotary encoder marks them as **green (completed)**  
- Users rotate the encoder to navigate between habits  

### 📊 Streak Visualization
- NeoPixel LEDs display historical data:
  - 🟢 Green = completed day  
  - 🔴 Red = missed day  

### ⏰ Daily Reset
- The system synchronizes with an internet time server  
- At the start of a new day:
  - All habits reset automatically  

### 💾 Data Persistence
- Uses ESP32 Preferences (NVS)
- Stores:
  - Habit completion status  
  - Historical streak data  
- Data is preserved even after power loss  

---

## 🛠️ Hardware
- ESP32 microcontroller  
- TFT display  
- Rotary encoder (with push button)  
- NeoPixel LED strip  
- Custom 3D-printed enclosure (Fusion 360)

---

## 💻 Software
- Language: C++ (Arduino framework)  
- Platform: ESP32  
- Storage: Non-Volatile Storage (Preferences)  

---

## 📂 Project Structure
```text
├── arduino/      # Main firmware code
├── case/         # Fusion 360 enclosure files
├── assets/       # TFT images converted to binary (Arduino-compatible)
```


---

## 🖼️ Assets (TFT Images)
Images used for the TFT display are preprocessed and stored as **binary arrays**, allowing efficient rendering on the ESP32.

---

## 🚀 Setup & Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/automatic-habit-tracker.git
Open the project in Arduino IDE or PlatformIO
Install required libraries:
Adafruit NeoPixel
TFT display library (specify model)
Upload the code to ESP32
🔌 Wiring (Optional Section)

Add your pin connections here (recommended)

Example:

TFT     -> ESP32 (SPI pins)
Encoder -> GPIO XX, XX
NeoPixel -> GPIO XX

---

## 🧠 Motivation

This project was built to address a key problem with habit tracking apps:

Too much friction and distraction.

By creating a dedicated physical interface, the system makes habit tracking:

- Faster
- More intentional
- Less cognitively demanding

## 🔮 Future Improvements
- Mobile or web sync
- Battery-powered version
- Custom habit configuration via UI
- Data analytics dashboard
