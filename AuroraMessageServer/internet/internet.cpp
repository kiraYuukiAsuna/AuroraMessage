/************************************************************
*Author:ÍõÈðÁú
*E-mail:daisyskye1425@outlook.com
*FileName:internet.cpp
*Function:socket tcp ·â×°
************************************************************/
#include"internet.h"

Internet::Internet(const char* serverIP,const int serverPort)
{
	this->serverIP = (char*)serverIP;
	this->serverPort = serverPort;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	ZeroMemory(&socketaddr, sizeof(socketaddr));
	socketaddr.sin_family = PF_INET;
	inet_pton(socketaddr.sin_family, serverIP, &socketaddr.sin_addr.s_addr);
	socketaddr.sin_port = htons(serverPort);
}

Internet::~Internet()
{
	cleanUp();
}

int Internet::startSocket()
{
	bind(serverSocket, (sockaddr*)&socketaddr, sizeof(socketaddr));
	listen(serverSocket, 20);
	return 0;
}

Internet::ClientResource* Internet::Accept()
{
	ClientResource* clientResource = new ClientResource;
	DWORD threadId;
	int size = sizeof(clientResource->clientaddr);
	SOCKET clientsocket = accept(serverSocket, (SOCKADDR*)&clientResource->clientaddr, &size);
	return clientResource;
}

int Internet::Send(SOCKET clientSocket, char* sendBuffer, int bufferSize)
{
	send(clientSocket, sendBuffer, bufferSize, 0);
	return 0;
}

int Internet::Recieve(SOCKET clientSocket, char* recvBuffer,int bufferSize)
{
	recv(clientSocket, recvBuffer, bufferSize, 0);
	return 0;
}

int Internet::cleanUp()
{
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}

DWORD WINAPI heartBeatProcess(LPVOID lpParameter)
{
	SOCKET *clientSocket = (SOCKET*)lpParameter;
	return 0;
}
