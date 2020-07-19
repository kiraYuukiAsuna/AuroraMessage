/************************************************************
*Author:������
*E-mail:daisyskye1425@outlook.com
*FileName:internet.h
*Function:socket tcp ��װ
************************************************************/
#include<WinSock2.h>
#include<Windows.h>
#include<WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

class Internet {
private:

	static const int BUFFERSIZE = 512;

	char* serverIP;
	int serverPort;

	WSADATA wsadata;
	SOCKET serverSocket = NULL;
	sockaddr_in socketaddr;

	struct ClientTable
	{

	};

public:

	enum ERRORCODE
	{
		BINDERROR,
		LISTENERROR,
		ACCEPTERROR,
		SENDERROR,
		RECVERROR,

	};

	struct ClientResource
	{
		int threadID;
		SOCKET clientSocket;
		SOCKADDR clientaddr;
		int userID;
		char sendBuffer[BUFFERSIZE];
		char receiveBuffer[BUFFERSIZE];
	};

	/************************************************************
	* FunctionName:Internet
	* Function:��Ĺ��캯��
	************************************************************/
	Internet(const char* serverIP, const int serverPort);

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

/************************************************************
* FunctionName:heartBeatProcess
* Function:�������
************************************************************/
DWORD WINAPI heartBeatProcess(LPVOID lpParameter);
