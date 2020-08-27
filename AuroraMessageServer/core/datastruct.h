#pragma once

#include<atomic>
#include"../internet/internet.h"

//服务器对客户端请求处理线程传递参数结构体
struct ClientProcessParameter {
	Network* ptr_net;
	std::atomic<bool> destructionStatus;//回收资源状态
	std::atomic<bool> receiveStatus;//接收数据状态
	std::atomic<bool> sendStatus;//发送数据状态
	std::atomic<bool> isReceiveThreadAlive;//发送数据线程是否存活
	std::atomic<bool> isSendThreadAlive;//接收数据线程是否存活
	HANDLE recieveThreadHandle;//接收数据线程句柄
	HANDLE sendThreadHandle;//发送数据线程句柄
	HANDLE receiveSignalHandle;//接收数据信号事件句柄
	HANDLE sendSignalHandle;//发送数据信号事件句柄
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
