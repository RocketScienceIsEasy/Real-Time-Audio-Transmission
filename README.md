# 🎧 Real-Time Audio Transmission System (C++)

## 📌 Overview
This project implements a **real-time audio streaming system** in C++ using sockets and PortAudio. It captures live audio from a microphone, transmits it over a network, and plays it back on a receiver node with measurable latency.

This prototype demonstrates core concepts used in VoIP systems like Zoom or Discord.

---

## 🚀 Features
- 🎤 Live audio capture using PortAudio  
- 🌐 Real-time audio transmission using TCP sockets  
- 📦 Chunk-based streaming (~23 ms per packet)  
- 🔁 Continuous playback with buffering  
- ⏱️ End-to-end delay measurement using timestamps  
- ⚙️ Low-latency design  

---

## 🧠 System Architecture

### 🔴 Sender (Node A)
- Captures audio from microphone  
- Splits into fixed-size chunks  
- Attaches timestamp  
- Sends data over socket  

### 🔵 Receiver (Node B)
- Receives audio packets  
- Computes delay  
- Buffers data  
- Plays audio in real-time  

---

## ⏱️ Delay Model

Total latency consists of:

- Audio frame duration (~23 ms)  
- Buffering delay  
- Network transmission delay  
- Playback delay  

📊 Observed latency: **~80–150 ms**

---

## ⚖️ Design Tradeoffs

| Factor | Choice | Reason |
|------|--------|--------|
| Protocol | TCP | Simpler and reliable |
| Chunk Size | 1024 samples | Balance between latency & stability |
| Buffering | Moderate | Smooth playback |

👉 Note: UDP is better for production real-time systems due to lower latency.

---

## 🛠️ Requirements

- Windows OS  
- Visual Studio Build Tools (C++)  
- PortAudio library  

---

## ⚙️ Setup Instructions

### 1️⃣ Clone Repository

```bash
git clone https://github.com/RocketScienceIsEasy/Real-Time-Audio-Transmission.git
cd Real-Time-Audio-Transmission
