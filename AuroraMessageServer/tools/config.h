/************************************************************
*Author:王瑞龙
*E-mail:daisyskye1425@outlook.com
*FileName:config.h
*Function:配置文件读取
************************************************************/
#include <stdio.h>  //for snprintf
#include <string.h>
#include <map>
#include<string>

class Config {
private:

	int   writeFile(const char* filename = NULL);
	void  parseLine(char* line);
	char* trimSpace(char* name);

	bool                                m_load_ok;
	std::map<std::string, std::string>  m_config_map;
	std::string                         m_config_file;

public:

	Config(const char* fileName);

	char* getConfigName(const char* name);
	int setConfigValue(const char* name, const char* value);
};
