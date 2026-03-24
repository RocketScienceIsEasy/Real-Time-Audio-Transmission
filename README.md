# Real-Time Audio Transmission System

## Overview
This project implements a real-time audio streaming system in C++ using sockets and PortAudio. The system captures live audio, transmits it over a network, and plays it back on a receiver node with measurable latency.

## Features
- Real-time audio streaming over TCP
- Chunk-based transmission (~23 ms per packet)
- Multithreaded architecture
- End-to-end delay measurement using timestamps
- Continuous playback with buffering

## System Architecture
Sender:
- Captures audio using PortAudio
- Divides into chunks
- Attaches timestamp
- Sends via socket

Receiver:
- Receives packets
- Calculates delay
- Buffers and plays audio

## Delay Model
Total delay consists of:
- Audio frame duration
- Buffering delay
- Network transmission delay
- Playback delay

## Results
Observed latency: ~80–150 ms depending on system conditions

## How to Run
1. Compile using Visual Studio Build Tools
2. Run receiver:
   receiver.exe
3. Run sender:
   sender.exe
4. Speak into microphone and observe output + delay

## Future Improvements
- UDP-based transmission
- Jitter buffer
- Packet loss handling
- Audio compression
