#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<fstream>
#include<time.h>

class LOG {
private:

	char* logFileDirectory;
	char* logFileName;
	char outputPath[255];

public:

	LOG(char* logFileDirectory, char* logFileName);

	int print(std::string str, bool newLine = true);

	int printToFile(std::string str, bool newLine = true);

};
