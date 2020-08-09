/************************************************************
*Author:王瑞龙
*E-mail:daisyskye1425@outlook.com
*FileName:internet.h
*Function:socket tcp 封装
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
	* Function:类的构造函数
	************************************************************/
	Internet(char* serverIP, int serverPort);

	/************************************************************
	* FunctionName:~Internet
	* Function:类的析构函数
	************************************************************/
	~Internet();

	/************************************************************
	* FunctionName:startSocket()
	* Function:创建一个服务器socket并开始监听
	************************************************************/
	int startSocket();

	/************************************************************
	* FunctionName:Accept
	* Function:尝试接受一次客户端请求
	************************************************************/
	ClientResource* Accept();

	/************************************************************
	* FunctionName:Send
	* Function:发送数据
	************************************************************/
	int Send(SOCKET clientSocket, char* sendBuffer, int bufferSize);

	/************************************************************
	* FunctionName:Recieve
	* Function:接受数据
	************************************************************/
	int Recieve(SOCKET clientSocket, char* recvBuffer, int bufferSize);

	/************************************************************
	* FunctionName:cleanUp
	* Function:清理服务器socket及WSADATA
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
* Function:心跳检测
************************************************************/
DWORD WINAPI heartBeatProcess(LPVOID lpParameter);
