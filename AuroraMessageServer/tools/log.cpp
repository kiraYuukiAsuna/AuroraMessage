#include"log.h"

LOG::LOG(char* logFileDirectory, char* logFileName) {
	this->logFileDirectory = logFileDirectory;
	this->logFileName = logFileName;
	memset(this->outputPath, 0, sizeof(this->outputPath));
	strcat(this->outputPath, this->logFileDirectory);
	strcat(this->outputPath, "/");
	strcat(this->outputPath, this->logFileName);
}

int LOG::print(std::string str, bool newLine) {
	time_t curtime = time(0);
	tm time = *localtime(&curtime);

	std::string timeString = "[" + std::to_string(time.tm_year + 1900) + "." + std::to_string(time.tm_mon + 1) + "."
		+ std::to_string(time.tm_mday) + " " + std::to_string(time.tm_hour) + ":"
		+ std::to_string(time.tm_min) + ":" + std::to_string(time.tm_sec) + "]";

	if (newLine == true) {
		std::cout << timeString << str << std::endl;
	} else {
		std::cout << timeString << str;
	}
	return 0;
}

int LOG::printToFile(std::string str, bool newLine) {
	time_t curtime = time(0);
	tm time = *localtime(&curtime);

	std::string timeString = "[" + std::to_string(time.tm_year + 1900) + "." + std::to_string(time.tm_mon + 1) + "."
		+ std::to_string(time.tm_mday) + " " + std::to_string(time.tm_hour) + ":"
		+ std::to_string(time.tm_min) + ":" + std::to_string(time.tm_sec) + "]";

	if (newLine == true) {
		std::cout << timeString << str << std::endl;
		std::fstream logFile;
		logFile.open(outputPath, std::ios::out | std::ios::app);
		logFile << timeString << str << std::endl;
	} else {
		std::cout << timeString << str;
		std::fstream logFile;
		logFile.open(outputPath, std::ios::out | std::ios::app);
		logFile << timeString << str;
	}
	return 0;
}
