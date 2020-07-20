#include"main.h"

int main(int argc, char* argv[])
{
	Internet *internet = new Internet("127.0.0.1", 1425);

	internet->startSocket();

	Config config("config.conf");

	config.setConfigValue("ServerIP", "127.0.0.1");

	char* serverip = config.getConfigName("ServerIP");

	std::cout << serverip << std::endl;

	while (true)
	{
		Internet::ClientResource* clientResource = new Internet::ClientResource;
		clientResource = internet->Accept();
		if (clientResource->clientSocket != NULL)
		{
			std::cout << "conncet successfully" << std::endl;

		}
		else
		{
			delete clientResource;
		}
	}

}
