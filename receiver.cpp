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

    SOCKET server_fd, client_socket;
    sockaddr_in address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);

    std::cout << "Waiting for connection...\n";
    client_socket = accept(server_fd, NULL, NULL);
    std::cout << "Connected!\n";

    // PortAudio init
    Pa_Initialize();

    PaStream* stream;
    Pa_OpenDefaultStream(&stream, 0, 1, paInt16, 44100, CHUNK, NULL, NULL);
    Pa_StartStream(stream);

    Packet packet;

    // Delay tracking
    static int counter = 0;
    static long long totalDelay = 0;

    while (true) {
        int bytesReceived = recv(client_socket, (char*)&packet, sizeof(packet), 0);
        if (bytesReceived <= 0) break;

        // Current time
        long long now = std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::steady_clock::now().time_since_epoch()
).count();

        long long delay = now - packet.timestamp;

        // Accumulate delay
        totalDelay += delay;
        counter++;

        // Print every ~1 second
        if (counter % 50 == 0) {
            std::cout << "Avg Delay: " << (totalDelay / counter) << " ms" << std::endl;
        }

        // Play audio
        Pa_WriteStream(stream, packet.audio, CHUNK);
    }

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    closesocket(client_socket);
    WSACleanup();
}