# Melati62 Smart Home


## Introduction
Project ini Saya buat sebagai solusi untuk membantu kegiatan sehari-hari di rumah. Dibuat dengan menggabungkan microcontroller ESP32 dengan relay dan aplikasi Blynk pada smartphone, smart home ini memiliki tiga tugas utama. Pertama, smart home ini dapat digunakan untuk menyala dan mematikan lampu rumah melalui aplikasi Blynk. Kedua, smart home dapat mendeteksi jika sedang terjadinya kebocoran gas dan mengirimkan notifikasi peringatan melalui aplikasi Blynk. Ketiga, smart home dapat mengontrol keran air secara otomatis berdasarkan ketinggian permukaan air pada bak mandi atau ember air menggunakan float switch. 

## Components
- ESP32-WROOM-32
- Arduino Nano R3
- NRF24L01+ WIRELESS TRANSCEIVER
- Relay 5VDC 4 Channel
- Relay 5VDC 1 Channel
- Solenoid Valve
- MQ-6 Gas Sensor(LPG and Butane)
- Water Level Float Switch
- Diode Rectifier
- Passive Buzzer
- Pushbutton
- DC Barrel Jack Adapter Female
- LED
- Resistior 220Ω
- Cable/Jumper

## Wiring and Assembling
### Schematic for ESP32 Main Hub
<p align="center">
    <img width="75%" src="Images/Main Hub Scheme.png">
</p>

### Schematic for Arduino Smoke Detector Node
<p align="center">
    <img width="75%" src="Images/Smoke Detector Scheme.png">
</p>
