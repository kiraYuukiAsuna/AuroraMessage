/************************************************************
*Author:王瑞龙
*E-mail:daisyskye1425@outlook.com
*FileName:config.cpp
*Function:配置文件读取
************************************************************/
#include "config.h"

Config::Config(const char* fileName) {
	m_config_file.clear();
	m_config_file.append(fileName);
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, fileName, "r");
	if (!fp) {
		err = fopen_s(&fp, fileName, "w");
		return;
	}

	char buf[256];
	for (;;) {
		char* p = fgets(buf, 256, fp);
		if (!p)
			break;

		size_t len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = 0;			// remove \n at the end

		char* ch = strchr(buf, '#');	// remove string start with #
		if (ch)
			*ch = 0;

		if (strlen(buf) == 0)
			continue;

		parseLine(buf);
	}

	fclose(fp);
	m_load_ok = true;
}

char* Config::getConfigName(const char* name) {
	if (!m_load_ok)
		return NULL;

	char* value = NULL;
	std::map<std::string, std::string>::iterator it = m_config_map.find(name);
	if (it != m_config_map.end()) {
		value = (char*)it->second.c_str();
	}

	return value;
}

int Config::setConfigValue(const char* name, const char* value) {
	if (!m_load_ok)
		return -1;

	std::map<std::string, std::string>::iterator it = m_config_map.find(name);
	if (it != m_config_map.end()) {
		it->second = value;
	} else {
		m_config_map.insert(std::make_pair(name, value));
	}

	return writeFile();
}

int Config::writeFile(const char* filename) {
	FILE* fp = NULL;
	errno_t err;
	if (filename == NULL) {
		err = fopen_s(&fp, m_config_file.c_str(), "w");
	} else {
		err = fopen_s(&fp, filename, "w");
	}
	if (fp == NULL) {
		return -1;
	}

	char szPaire[128];
	std::map<std::string, std::string>::iterator it = m_config_map.begin();
	for (; it != m_config_map.end(); it++) {
		memset(szPaire, 0, sizeof(szPaire));
		snprintf(szPaire, sizeof(szPaire), "%s=%s\n", it->first.c_str(), it->second.c_str());
		size_t ret = fwrite(szPaire, strlen(szPaire), 1, fp);
		if (ret != 1) {
			fclose(fp);
			return -1;
		}
	}
	fclose(fp);
	return 0;
}

void Config::parseLine(char* line) {
	char* p = strchr(line, '=');
	if (p == NULL)
		return;

	*p = 0;
	char* key = trimSpace(line);
	char* value = trimSpace(p + 1);
	if (key && value) {
		m_config_map.insert(std::make_pair(key, value));
	}
}

char* Config::trimSpace(char* name) {
	// remove starting space or tab
	char* start_pos = name;
	while ((*start_pos == ' ') || (*start_pos == '\t') || (*start_pos == '\r')) {
		start_pos++;
	}

	if (strlen(start_pos) == 0)
		return NULL;

	// remove ending space or tab
	char* end_pos = name + strlen(name) - 1;
	while ((*end_pos == ' ') || (*end_pos == '\t') || (*end_pos == '\r')) {
		*end_pos = 0;
		end_pos--;
	}

	int len = (int)(end_pos - start_pos) + 1;
	if (len <= 0)
		return NULL;

	return start_pos;
}
