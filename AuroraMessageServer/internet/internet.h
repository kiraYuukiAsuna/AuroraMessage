/************************************************************
*Author:������
*E-mail:daisyskye1425@outlook.com
*FileName:internet.h
*Function:socket tcp ��װ
************************************************************/
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<WinSock2.h>
#include<Windows.h>
#include<WS2tcpip.h>
#include<vector>
#include"../tools/json.hpp"

#pragma comment(lib,"ws2_32.lib")

class Internet {
private:

	char* serverIP;
	int serverPort;

	WSADATA wsadata;
	SOCKET serverSocket = NULL;
	sockaddr_in socketaddr;

public:

	static const int BUFFERSIZE = 512;

	enum ERRORCODE {
		BINDERROR,
		LISTENERROR,
		ACCEPTERROR,
		SENDERROR,
		RECVERROR,

	};

	struct ClientResource {
		int threadID;
		SOCKET clientSocket;
		sockaddr_in clientAddress;
		char sendBuffer[BUFFERSIZE];
		char recieveBuffer[BUFFERSIZE];
		int uid;

		ClientResource();
	};

	struct ClientTable {
		std::vector<ClientResource>ClientResource;

	};

	ClientTable clientTable;

	/************************************************************
	* FunctionName:Internet
	* Function:��Ĺ��캯��
	************************************************************/
	Internet(char* serverIP, int serverPort);

	/************************************************************
	* FunctionName:~Internet
	* Function:�����������
	************************************************************/
	~Internet();

	/************************************************************
	* FunctionName:startSocket()
	* Function:����һ��������socket����ʼ����
	************************************************************/
	int startSocket();

	/************************************************************
	* FunctionName:Accept
	* Function:���Խ���һ�οͻ�������
	************************************************************/
	ClientResource* Accept();

	/************************************************************
	* FunctionName:Send
	* Function:��������
	************************************************************/
	int Send(SOCKET clientSocket, char* sendBuffer, int bufferSize);

	/************************************************************
	* FunctionName:Recieve
	* Function:��������
	************************************************************/
	int Recieve(SOCKET clientSocket, char* recvBuffer, int bufferSize);

	/************************************************************
	* FunctionName:cleanUp
	* Function:���������socket��WSADATA
	************************************************************/
	int cleanUp();
};

class Network {

private:

	Internet::ClientResource* clientResource;

public:

	Network(Internet::ClientResource* clientResource);

	int recieveData();

	int sendData(const char* data);

	char* getRecievedData();
};

/************************************************************
* FunctionName:heartBeatProcess
* Function:�������
************************************************************/
DWORD WINAPI heartBeatProcess(LPVOID lpParameter);
