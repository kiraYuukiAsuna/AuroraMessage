#include"main.h"

/************************************************************
* FunctionName:main
* Function:程序入口函数
************************************************************/
int main(int argc, char* argv[])
{
	Internet* internet = new Internet("127.0.0.1", 1425);

	internet->startSocket();

	Config config("config.conf");

	config.setConfigValue("ServerIP", "127.0.0.1");

	char* serverip = config.getConfigName("ServerIP");

	std::cout << serverip << std::endl;

	while (true)//客户端连接接受
	{
		Internet::ClientResource* clientResource = nullptr;
		clientResource = internet->Accept();
		if (clientResource != nullptr)
		{
			char ptr[INET_ADDRSTRLEN];
			memset(ptr, 0, sizeof(ptr));
			std::cout << "Accept OK!" << std::endl;
			std::cout << "clientSocket:"<<clientResource->clientSocket << std::endl;
			inet_ntop(AF_INET, &clientResource->clientAddress.sin_addr, ptr, INET_ADDRSTRLEN);
			std::cout << "port:" << clientResource->clientAddress.sin_port << std::endl;
			std::cout << "clientAddress:" << ptr << std::endl;
			std::cout << "sendBuffer:" << clientResource->sendBuffer << std::endl;
			std::cout << "recieveBuffer:" << clientResource->recieveBuffer << std::endl;
			std::cout << "threadID:" << clientResource->threadID << std::endl;
			std::cout << "uid:" << clientResource->uid << std::endl;
		}
		else
		{
			std::cout << "Accept error!" << std::endl;
		}
	}

}
