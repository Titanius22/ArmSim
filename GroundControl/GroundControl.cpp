// GroundControl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <cassert>
#include "GroundControl.h"
#include "../ArmSim/Command_Platform.h"


#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

GroundControl::GroundControl()
{
    const char ipAdress[] = "localhost";
    this->ConnectSocket = INVALID_SOCKET;
    
    this->SetUpClient(ipAdress);
}

GroundControl::~GroundControl()
{
    this->ShutDownClient();
}

void GroundControl::Start()
{
    //char port[] = "27015";
    char sendBuffer[500];
    int remainingChars = 0;
    std::string tmpStr;
    std::vector<std::string> tmpVtr;
    std::string const delimiter = ",";

    Command_Platform newCmd = Command_Platform(Command_Platform::CommanndType::DO_NOTHING);
    
    while (true) {

        // cause system to wait
        std::cout << "Enter comma separated command parameters...\n"; // Type a number and press enter
        std::cin >> sendBuffer; // Get user input from the keyboard

        tmpVtr.clear();
        tmpStr = sendBuffer;
        
        remainingChars = strlen(sendBuffer);

        //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        size_t pos = 0;
        while ((pos = tmpStr.find(delimiter)) != std::string::npos) {
            tmpVtr.push_back(tmpStr.substr(0, pos));
            tmpStr.erase(0, pos + delimiter.length());
        }
        if (!tmpStr.empty())
        {
            tmpVtr.push_back(tmpStr);
        }

        // TODO: made smarter
        if (tmpVtr.size() == 1)
        {
            // Command_Platform::CommanndType::DO_NOTHING
            newCmd = Command_Platform(Command_Platform::CommanndType::DO_NOTHING);
        }
        else if (tmpVtr.size() == 3)
        {
            Command_Platform::CommanndType tempCmdType = (Command_Platform::CommanndType)std::stoi(tmpVtr.at(0));
            uint8_t accNum = (uint8_t)std::stoi(tmpVtr.at(1));
            float accValue = std::stof(tmpVtr.at(2));
            
            
            // Command_Platform::CommanndType::CHANGE_ACTUATOR_VALUE;
            newCmd = Command_Platform(
                tempCmdType,
                accNum,
                accValue);
        }
        else 
        {
            assert(false); // TODO: need to handle
        }
        
        this->UserCmdSending(&newCmd);
    }
}

int GroundControl::SetUpClient(const char* ipAdress)
{
    WSADATA wsaData;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    int iResult;

    //printf("usage: %s server-name\n", ipAdress);

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(ipAdress, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        this->ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (this->ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(this->ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(this->ConnectSocket);
            this->ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    if (this->ConnectSocket == INVALID_SOCKET)
    {
        // TODO: resolve problem
        assert(false);
    }


    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (this->ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

	return 0;
}

int GroundControl::UserCmdSending(Command_Platform* pCmd)
{
    int iResult;
    
    // Send an initial buffer
    iResult = send(this->ConnectSocket, (const char *)pCmd->GetCommandBits(), Command_Platform::COMMAND_SIZE_BYTES, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(this->ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    return 0;
}

int GroundControl::ShutDownClient()
{
    int iResult;
    
    // shutdown the connection since no more data will be sent
    iResult = shutdown(this->ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(this->ConnectSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(this->ConnectSocket);
    WSACleanup();

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
