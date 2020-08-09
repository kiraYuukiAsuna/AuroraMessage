#include "main.h"

//��������
DWORD WINAPI clientProcess(LPVOID lpParameter);
DWORD WINAPI clientDataRecieveThread(LPVOID lpParameter);
DWORD WINAPI clientDataSendThread(LPVOID lpParameter);

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

			CreateThread(NULL, 0, clientProcess, clientResource, 0, NULL);

			log->print("threadID:" + std::to_string(clientResource->threadID));
			log->print("uid:" + std::to_string(clientResource->uid));

			clientResource = nullptr;
		} else {
			log->print("Accept error!");
		}
		Sleep(1);
	}
}

DWORD WINAPI clientProcess(LPVOID lpParameter) {
	Network net((Internet::ClientResource*)lpParameter);
	Network* ptr_net = &net;

	//�߳��Ƿ����ԭ�ӱ���
	std::atomic<bool>clientDataRecieveThreadRunningState(false);
	std::atomic<bool>clientDataSendThreadRunningState(false);

	//�����̵߳Ĳ���
	Parameter parameterRecieve;
	Parameter* parameterRecieve_ptr = &parameterRecieve;
	parameterRecieve.ptr_net = &net;
	parameterRecieve.state = &clientDataRecieveThreadRunningState;

	Parameter parameterSend;
	Parameter* parameterSend_ptr = &parameterSend;
	parameterSend.ptr_net = &net;
	parameterSend.state = &clientDataSendThreadRunningState;

	//�����߳�
	HANDLE handleForRecieveThread = nullptr;
	HANDLE handleForSendThread = nullptr;

	handleForRecieveThread=CreateThread(NULL, 0, clientDataRecieveThread, parameterRecieve_ptr, 0, NULL);
	clientDataRecieveThreadRunningState = true;
	handleForSendThread=CreateThread(NULL, 0, clientDataSendThread, parameterSend_ptr, 0, NULL);
	clientDataSendThreadRunningState = true;

	//�ȴ����������߳̽������˳����߳�
	if (handleForRecieveThread != 0 && handleForSendThread != 0) {
		while (true) {
			if (WaitForSingleObject(handleForRecieveThread, INFINITE) == WAIT_OBJECT_0 || WaitForSingleObject(handleForSendThread, INFINITE) == WAIT_OBJECT_0) {
				clientDataRecieveThreadRunningState = false;
				clientDataSendThreadRunningState = false;
				if ((WaitForSingleObject(handleForRecieveThread, INFINITE) == WAIT_OBJECT_0) && (WaitForSingleObject(handleForSendThread, INFINITE) == WAIT_OBJECT_0)) {
					break;
				}
			}
		}
	}

	return 0;
}

//���ܿͻ������ݴ����߳�
DWORD WINAPI clientDataRecieveThread(LPVOID lpParameter) {
	Parameter* ptr_parameter = (Parameter*)lpParameter;
	while (*ptr_parameter->state) {
		if (ptr_parameter->ptr_net->recieveData() > 0) {//���յ�����
			std::cout << "on recv" << std::endl;
			char* logFileDirectory = (char*)"./";
			char* logFileName = (char*)"clientProcess.txt";
			LOG log(logFileDirectory, logFileName);
			char* str = ptr_parameter->ptr_net->getRecievedData();
			log.print(str);

		} else if (ptr_parameter->ptr_net->recieveData() == 0) {//�ͻ��˶Ͽ�����
			*ptr_parameter->state = false;
		} else if (ptr_parameter->ptr_net->recieveData() < 0) {//�����쳣
			*ptr_parameter->state = false;
		}
	}
	return 0;
}

//��ͻ��˷������ݴ����߳�
DWORD WINAPI clientDataSendThread(LPVOID lpParameter) {
	Parameter* ptr_parameter = (Parameter*)lpParameter;
	while (*ptr_parameter->state) {

		HANDLE eventHandle = nullptr;
		CreateEvent(NULL, TRUE, TRUE, NULL);//��λ��ʽΪ�ֶ��ָ������ź�״̬���ҳ�ʼ״̬Ϊ���ź�.

		//SetEvent()
		//ResetEvent()

		//TODO
		/*
		if () {
			ptr_parameter->ptr_net->sendData("Hello world!");
		}
		*/
	}
	return 0;
}
