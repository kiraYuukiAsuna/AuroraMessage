#include "main.h"

//��������
DWORD WINAPI clientProcess(LPVOID lpParameter);

/************************************************************
 * FunctionName:main
 * Function:������ں���
 ************************************************************/
int main(int argc, char* argv[]) {

	//������־�ļ�
	char* logFileDirectory = (char*)"./";
	char* logFileName = (char*)"log.txt";
	LOG* log = new LOG(logFileDirectory, logFileName);
	log->printToFile("Server start.");
	log->printToFile("Server log module OK.");
	//��ȡ�����������ļ�
	Config config("config.conf");
	char* serverIP = config.getConfigName("ServerIP");
	char* serverPort = config.getConfigName("ServerPort");
	log->printToFile("Server config module OK.");
	//������װ���������
	Internet* internet = new Internet(serverIP, atoi(serverPort));
	internet->startSocket();
	log->printToFile("Server network module OK.");
	//������ѭ�������տͻ�������
	while (true) {
		Internet::ClientResource* clientResource = nullptr;
		clientResource = internet->Accept();
		if (clientResource != nullptr) {
			char clientAddress[INET_ADDRSTRLEN];
			memset(clientAddress, 0, sizeof(clientAddress));
			log->print("Accept OK!");
			log->print("clientSocket:" + std::to_string(clientResource->clientSocket));
			inet_ntop(AF_INET, &clientResource->clientAddress.sin_addr, clientAddress, INET_ADDRSTRLEN);
			log->print("port:" + std::to_string(clientResource->clientAddress.sin_port));
			log->print("clientAddress:", false);
			log->print(clientAddress);
			log->print("sendBuffer:" + *clientResource->sendBuffer);
			log->print("recieveBuffer:" + *clientResource->recieveBuffer);

			CreateThread(NULL, 0, &clientProcess, clientResource, 0, NULL);

			log->print("threadID:" + std::to_string(clientResource->threadID));
			log->print("uid:" + std::to_string(clientResource->uid));
		} else {
			log->print("Accept error!");
		}
	}
}

DWORD WINAPI clientProcess(LPVOID lpParameter) {
	Network net((Internet::ClientResource*)lpParameter);

	char* logFileDirectory = (char*)"./";
	char* logFileName = (char*)"clientProcess.txt";
	LOG* log = new LOG(logFileDirectory, logFileName);

	net.recieveData();
	char* str=net.getRecievedData();
	log->printToFile(str);

	net.sendData("Hello world!");

	return 0;
}