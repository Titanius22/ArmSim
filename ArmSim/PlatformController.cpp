/*
	The Winsock2.h header file internally includes core elements from the Windows.h 
	header file, so there is not usually an #include line for the Windows.h header 
	file in Winsock applications.If an #include line is needed for the Windows.h header 
	file, this should be preceded with the #define WIN32_LEAN_AND_MEAN macro. For historical 
	reasons, the Windows.h header defaults to including the Winsock.h header file for 
	Windows Sockets 1.1. The declarations in the Winsock.h header file will conflict with 
	the declarations in the Winsock2.h header file required by Windows Sockets 2.0. The 
	WIN32_LEAN_AND_MEAN macro prevents the Winsock.h from being included by the Windows.h header.
*/
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif

//#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#include "PlatformController.h"
#include "Command_Platform.h"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"

PlatformController::PlatformController(Platform* _ptrPlatform)
{
	this->ptrPlatform = _ptrPlatform;
	this->ClientSocket = INVALID_SOCKET;

	this->StartServer();
}

PlatformController::~PlatformController()
{
	this->ShutdownServer();
}

void PlatformController::ReceiveCommand(Command_Platform* command)
{
	Command_Platform::CommanndType commandType = command->GetCommandType();
	if (commandType == Command_Platform::CommanndType::DO_NOTHING)
	{
		// ... do nothing
	}
	else if(commandType == Command_Platform::CommanndType::CHANGE_ACTUATOR_VALUE)
	{
		uint8_t actuatorID = command->GetActuatorID();
		Actuator* pActuator = this->ptrPlatform->GetPtrToActuator(actuatorID);

		pActuator->setCommandedActuationValue(command->GetActuatorValue());

	}
	else
	{
		assert(false);
	}
}

// https://learn.microsoft.com/en-us/windows/win32/winsock/complete-server-code
int PlatformController::StartServer()
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for the server to listen for client connections.
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	// listens for a client request
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	printf("Waiting for a client...\n");
	
	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		printf("Connect to a client...\n");
	}

	// Set Socket into non-blocking mode so that recv() can be called and 
	// it returns if no data is available
	unsigned long ul = 1;
	iResult = ioctlsocket(ClientSocket, FIONBIO, (unsigned long*)&ul);
	if (iResult == SOCKET_ERROR)
	{
		printf("Failed to put the socket into non-blocking mode\n");
		assert(false);
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);

	return 0;
}

int PlatformController::HandleCommands()
{
	int iResult;

	char recvbuf[Command_Platform::COMMAND_SIZE_BYTES]; // char and uint8_t is the same data size
	int recvbuflen = Command_Platform::COMMAND_SIZE_BYTES;
	
	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {

			printf("Received Command...\n");

			Command_Platform receivedCmd(recvbuf); // constructor

			this->ReceiveCommand(&receivedCmd);

			//// Echo the buffer back to the sender
			//iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			//if (iSendResult == SOCKET_ERROR) {
			//	printf("send failed: %d\n", WSAGetLastError());
			//	closesocket(ClientSocket);
			//	WSACleanup();
			//	return 1;
			//}
			//printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
		{
			// this should never occur. recv() doesn't return 0
			assert(false);
		}
		else
		{
			int errorCode = WSAGetLastError();
			if (errorCode == WSAEWOULDBLOCK)
			{
				printf("~~~No commands to receive~~~\n\n");
			}			
			else {
				printf("recv failed: %d\n", errorCode);
				closesocket(ClientSocket);
				WSACleanup();
				assert(false); //TODO: How should this be handled
				return 1;
			}
		}

	} while (iResult > 0);

	return 0;
}

int PlatformController::ShutdownServer()
{
	int iResult;
	
	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}



// --- End of File ---