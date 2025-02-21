## <a name="introduction">🌿 IoT Plant Monitoring System with ESP32 & LoRa 📡🌱 </a>

<img src="https://github.com/rch-goldsnaker/esp32-lora-humidity-temperature/blob/main//banner.jpg" alt="Project Banner">

## 📋 <a name="table">Table of Contents</a>

1. 🤖 [Introduction](#introduction)
2. ⚙️ [Tech Stack](#tech-stack)
3. 🔋 [Features](#features)
4. 💻 [Youtube tutorial](#youtube)
5. 🤸 [Quick Start](#quick-start)
   
## <a name="introduction">🤖 Introduction</a>

In this project, we’ll build a complete IoT plant monitoring system from scratch! 🌾✨

Using an ESP32, a LoRa module, and sensors for soil moisture, air temperature, and humidity, we’ll create a custom solution for real-time plant monitoring. Long-range communication is handled via LoRaWAN, making it perfect for Smart Agriculture and remote sensing applications. 📡🌦️

This repository includes:

📟 ESP32 code for reading sensor data and transmitting via LoRa
🌐 LoRaWAN Gateway setup using a Thinknode gateway
🔗 Integration with The Things Stack (TTS) for data management
📊 Real-time dashboard on TagoIO for visualizing sensor data
Whether you're into DIY electronics, IoT projects, or exploring Smart Agriculture solutions, this repo has everything you need to get started! 🌱🚀

## <a name="tech-stack">⚙️ Tech Stack</a>

💎 The Things Stack (TTS)

💎 ESP32 LORA 

💎 TAGO.IO

## <a name="features">🔋 Features</a>

✅ ESP32 Integration — Code to read data from a capacitive soil moisture sensor (HW-390) and a DHT11 sensor for air temperature and humidity. 🌱🌡️

✅ LoRaWAN Communication — Long-range, low-power data transmission using an ESP32 LoRa module, connected to a Thinknode gateway. 📡🔗

✅ The Things Stack (TTS) Integration — Pre-configured device profiles and payload formatters for seamless data decoding and management. ⚙️📥

✅ TagoIO Dashboard — Real-time dashboard with custom widgets to visualize soil moisture, temperature, and humidity data. 📊💡

## <a name="youtube">🎬 Youtube tutorial</a>

See tutorial video [here](https://youtu.be/3G8kS25oRRI?si=o8mkDPI3U5oV8UBL)

## <a name="quick-start">🤸 Quick Start</a>

Get your IoT Plant Monitoring System up and running in no time! 🌱⚡

🛠 What You’ll Need:

📟 ESP32 LoRa module

🌾 HW-390 capacitive soil moisture sensor

🌡 DHT11 temperature & humidity sensor

🔋 Battery (for portable power)

📡 LoRaWAN Gateway (e.g., Thinknode)

💎 Free accounts on The Things Stack (TTS) and TagoIO

3D Models:

Main Case [here](https://drive.google.com/file/d/1JsBSK5fQnt4c022JBEDRmdKPCml3_VGz/view?usp=drive_link)

Case Cup [here](https://drive.google.com/file/d/1jItS_1_Zx4TILf-dj8dBhA6uBDGttseb/view?usp=drive_link)

Case Back [here](https://drive.google.com/file/d/1dJU65UFFDw4whuMo_ZQj6i-t7nW5yTFz/view?usp=drive_link)

⚡ Getting Started:

🔗 Watch the Full Tutorial Video — Follow along for the complete step-by-step guide. 🎥🚀

📥 Flash the ESP32 — Use the provided code in this repo to read sensor data and transmit it over LoRa.

🌐 Set Up TTS — Register your ESP32 device and connect it to your LoRaWAN Gateway (free tier works perfectly!).

📊 Integrate with TagoIO — Use the webhook integration to send data from TTS to TagoIO and visualize it on a real-time dashboard.

And that’s it! Your smart plant monitoring system is live and sending data! 🌾📡
