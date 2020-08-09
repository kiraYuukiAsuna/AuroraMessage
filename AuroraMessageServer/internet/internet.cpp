/************************************************************
*Author:ÍõÈðÁú
*E-mail:daisyskye1425@outlook.com
*FileName:internet.cpp
*Function:socket tcp ·â×°
************************************************************/
#include"internet.h"

Internet::Internet(char* serverIP, int serverPort) {
	this->serverIP = (char*)serverIP;
	this->serverPort = serverPort;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	ZeroMemory(&socketaddr, sizeof(socketaddr));
	socketaddr.sin_family = PF_INET;
	inet_pton(socketaddr.sin_family, serverIP, &socketaddr.sin_addr.s_addr);
	socketaddr.sin_port = htons(serverPort);
}

Internet::~Internet() {
	cleanUp();
}

int Internet::startSocket() {
	bind(serverSocket, (SOCKADDR*)&socketaddr, sizeof(socketaddr));
	listen(serverSocket, 20);
	return 0;
}

Internet::ClientResource* Internet::Accept() {
	ClientResource* clientResource = new ClientResource;
	int size = sizeof(clientResource->clientAddress);
	SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&clientResource->clientAddress, &size);
	clientResource->clientSocket = clientSocket;
	if (clientResource->clientSocket != NULL) {
		clientTable.ClientResource.push_back(*clientResource);
		return clientResource;
	}
	return nullptr;
}

int Internet::Send(SOCKET clientSocket, char* sendBuffer, int bufferSize) {
	send(clientSocket, sendBuffer, bufferSize, 0);
	return 0;
}

int Internet::Recieve(SOCKET clientSocket, char* recvBuffer, int bufferSize) {
	recv(clientSocket, recvBuffer, bufferSize, 0);
	return 0;
}

int Internet::cleanUp() {
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}

DWORD WINAPI heartBeatProcess(LPVOID lpParameter) {
	SOCKET* clientSocket = (SOCKET*)lpParameter;
	return 0;
}

Internet::ClientResource::ClientResource() {
	threadID = 0;
	clientSocket = 0;
	memset(&clientAddress, 0, sizeof(clientAddress));
	memset(sendBuffer, 0, sizeof(sendBuffer));
	memset(recieveBuffer, 0, sizeof(sendBuffer));
	uid = 0;
}

Network::Network(Internet::ClientResource* clientResource) {
	this->clientResource = clientResource;
}

int Network::recieveData() {
	memset(clientResource->recieveBuffer, 0, Internet::BUFFERSIZE);
	return recv(clientResource->clientSocket, clientResource->recieveBuffer, Internet::BUFFERSIZE, 0);
}

int Network::sendData(const char* data) {
	memset(clientResource->sendBuffer, 0, Internet::BUFFERSIZE);
	strcpy(clientResource->sendBuffer, data);
	return send(clientResource->clientSocket, clientResource->sendBuffer, Internet::BUFFERSIZE, 0);
}

char* Network::getRecievedData() {
	return clientResource->recieveBuffer;
}
