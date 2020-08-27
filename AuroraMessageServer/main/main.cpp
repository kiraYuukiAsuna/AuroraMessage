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
	ClientProcessParameter clientProcessParameter;
	Network net((Internet::ClientResource*)lpParameter);
	ClientProcessParameter* clientProcessParameter_ptr = &clientProcessParameter;

	clientProcessParameter.ptr_net = &net;

	clientProcessParameter.sendSignalHandle = CreateEvent(NULL, TRUE, false, NULL);//��λ��ʽΪ�ֶ��ָ������ź�״̬���ҳ�ʼ״̬Ϊ���ź�

	clientProcessParameter.recieveThreadHandle = CreateThread(NULL, 0, clientDataRecieveThread, clientProcessParameter_ptr, 0, NULL);
	clientProcessParameter.sendThreadHandle = CreateThread(NULL, 0, clientDataSendThread, clientProcessParameter_ptr, 0, NULL);

	//�ȴ����������߳̽������˳����߳�
	if (clientProcessParameter.recieveThreadHandle != 0 && clientProcessParameter.sendThreadHandle != 0) {
		while (true) {
			if (WaitForSingleObject(clientProcessParameter.recieveThreadHandle, INFINITE) == WAIT_OBJECT_0 || WaitForSingleObject(clientProcessParameter.sendThreadHandle, INFINITE) == WAIT_OBJECT_0) {
				clientProcessParameter.isReceiveThreadAlive = false;
				clientProcessParameter.isSendThreadAlive = false;
				if ((WaitForSingleObject(clientProcessParameter.recieveThreadHandle, INFINITE) == WAIT_OBJECT_0) && (WaitForSingleObject(clientProcessParameter.sendThreadHandle, INFINITE) == WAIT_OBJECT_0)) {
					break;
				}
			}
		}
	}

	return 0;
}

//���ܿͻ������ݴ����߳�
DWORD WINAPI clientDataRecieveThread(LPVOID lpParameter) {
	ClientProcessParameter* ptr_parameter = (ClientProcessParameter*)lpParameter;
	while (ptr_parameter->destructionStatus==false) {
		if (ptr_parameter->ptr_net->recieveData() > 0) {//���յ�����
			std::cout << "on recv" << std::endl;
			SetEvent(ptr_parameter->sendSignalHandle);
			char* logFileDirectory = (char*)"./";
			char* logFileName = (char*)"clientProcess.txt";
			LOG log(logFileDirectory, logFileName);
			char* str = ptr_parameter->ptr_net->getRecievedData();
			log.print(str);
		} else if (ptr_parameter->ptr_net->recieveData() == 0) {//�ͻ��˶Ͽ�����
			ptr_parameter->destructionStatus = true;
			break;
		} else if (ptr_parameter->ptr_net->recieveData() < 0) {//�����쳣
			ptr_parameter->destructionStatus = true;
			break;
		}
	}
	return 0;
}

//��ͻ��˷������ݴ����߳�
DWORD WINAPI clientDataSendThread(LPVOID lpParameter) {
	ClientProcessParameter* ptr_parameter = (ClientProcessParameter*)lpParameter;
	while (ptr_parameter->destructionStatus==false) {
		if (ptr_parameter->sendSignalHandle != nullptr) {
			if (WaitForSingleObject(ptr_parameter->sendSignalHandle, INFINITE) == WAIT_OBJECT_0) {
				ptr_parameter->ptr_net->sendData("Hello world!");
				ResetEvent(ptr_parameter->sendSignalHandle);
			}
		}
	}
	return 0;
}
