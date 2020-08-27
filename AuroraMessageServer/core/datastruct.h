#pragma once

#include<atomic>
#include"../internet/internet.h"

//�������Կͻ����������̴߳��ݲ����ṹ��
struct ClientProcessParameter {
	Network* ptr_net;
	std::atomic<bool> destructionStatus;//������Դ״̬
	std::atomic<bool> receiveStatus;//��������״̬
	std::atomic<bool> sendStatus;//��������״̬
	std::atomic<bool> isReceiveThreadAlive;//���������߳��Ƿ���
	std::atomic<bool> isSendThreadAlive;//���������߳��Ƿ���
	HANDLE recieveThreadHandle;//���������߳̾��
	HANDLE sendThreadHandle;//���������߳̾��
	HANDLE receiveSignalHandle;//���������ź��¼����
	HANDLE sendSignalHandle;//���������ź��¼����
	ClientProcessParameter() {
		ptr_net = nullptr;
		destructionStatus = false;
		receiveStatus = true;
		sendStatus = false;
		isReceiveThreadAlive = true;
		isSendThreadAlive = true;
		recieveThreadHandle = nullptr;
		sendThreadHandle = nullptr;
		receiveSignalHandle = nullptr;
		sendSignalHandle = nullptr;
	}
};
