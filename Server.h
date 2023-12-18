#pragma once
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27016"
using namespace System::Threading;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::IO;
ref class Server {
private:
	SOCKET ListenSocket;


public:
	List<SOCKET>^ ClientSockets;
	Server() {
		ListenSocket = INVALID_SOCKET;
		ClientSockets = gcnew List<SOCKET>();
	}

	void StartServer() {
		WSADATA wsaData;
		int iResult;

		struct addrinfo* result = NULL;
		struct addrinfo hints;

		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return;
		}

		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}

		freeaddrinfo(result);

		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}
		Thread^ serverThread = gcnew Thread(gcnew ThreadStart(this, &Server::AcceptConnections));
		serverThread->IsBackground = true; // Щоб при закритті форми припинити роботу сервера
		serverThread->Start();
	}

	void DisconnectServer() {
		// Проходимо по всіх клієнтських сокетах і виконуємо розрив з'єднання та очищення ресурсів для кожного з них
		for each (SOCKET clientSocket in ClientSockets) {
			shutdown(clientSocket, SD_SEND);
			closesocket(clientSocket);
		}
		closesocket(ListenSocket);
		WSACleanup();
	}

	void AcceptConnections() {
		while (true) {
			SOCKET newClientSocket = accept(ListenSocket, NULL, NULL);
			if (newClientSocket != INVALID_SOCKET) {
				ClientSockets->Add(newClientSocket);

				// Ось тут можна запустити окремий обробник для нового клієнта,
				// або працювати з цим клієнтом в циклі, обмінюючись даними
				// Важливо обробляти помилки, закривати з'єднання при необхідності та чистити ресурси
			}
		}
	}

	void OnClientDisconnect(SOCKET disconnectedClient) {
		
		for (int i = 0; i < ClientSockets->Count; ++i) {
			if (ClientSockets[i] == disconnectedClient) {
				
				ClientSockets->RemoveAt(i);
				break;
			}
		}
		
		// Додаткові дії після від'єднання клієнта...
	}

	String^ ReceiveData(SOCKET clientSocket) {
		char recvbuf[DEFAULT_BUFLEN];
		int iResult;

#ifdef _WIN32
		u_long mode = 1; // Увімкнення неблокуючого режиму для Windows
		ioctlsocket(clientSocket, FIONBIO, &mode);
#else
		int flags = fcntl(clientSocket, F_GETFL, 0);
		fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK); // Увімкнення неблокуючого режиму для Unix-подібних систем
#endif

		iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
		printf("%d", iResult);
		if (iResult > 0) {
			recvbuf[iResult] = '\0';
			// Конвертація масиву символів у рядок
			System::Text::Encoding^ enc = System::Text::Encoding::UTF8; // Використовуйте відповідний кодувальник
			return gcnew String(recvbuf, 0, iResult, enc);
		}
		else if (iResult == 0) {
			OnClientDisconnect(clientSocket);
			return "disconnect";
		}

		else {
#ifdef _WIN32
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				return ""; // Якщо немає даних для отримання
			}
#else
			if (errno == EWOULDBLOCK) {
				return ""; // Якщо немає даних для отримання
			}
#endif
			printf("recv failed with error: %d\n", WSAGetLastError());
			return "";
		}
	}

	List<SOCKET>^ GetClientSockets() {
		List<SOCKET>^ clientSockets = gcnew List<SOCKET>();
		for each (SOCKET clientSocket in ClientSockets) {
			clientSockets->Add(clientSocket);
		}
		return clientSockets;
	}

	void SendData(SOCKET clientSocket, const char* data) {
		int iResult = send(clientSocket, data, (int)strlen(data), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
		}
		else {
			printf("Bytes sent: %d\n", iResult);
		}
	}
};