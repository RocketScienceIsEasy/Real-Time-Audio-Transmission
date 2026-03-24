#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <portaudio.h>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9999
#define CHUNK 1024

struct Packet {
    long long timestamp;
    int16_t audio[CHUNK];
};

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock;
    sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
    std::cout << "Connected to server\n";

    // PortAudio init
    Pa_Initialize();

    PaStream* stream;
    Pa_OpenDefaultStream(&stream, 1, 0, paInt16, 44100, CHUNK, NULL, NULL);
    Pa_StartStream(stream);

    Packet packet;

    while (true) {
        // Capture audio
        Pa_ReadStream(stream, packet.audio, CHUNK);

        // Timestamp
        packet.timestamp = std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::steady_clock::now().time_since_epoch()
).count();

        // Send
        send(sock, (char*)&packet, sizeof(packet), 0);
    }

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    closesocket(sock);
    WSACleanup();
}