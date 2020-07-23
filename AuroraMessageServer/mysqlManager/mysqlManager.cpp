#include"mysqlManager.h"

MYSQLMANAGER::MYSQLMANAGER(const char* ip, const int port, const char* user, const char* password, const char* dbName)
{
	mysql_init(&mysqlHandler);//��ʼ��mysql
	this->info.ip = (char*)ip;
	this->info.port = port;
	this->info.user = (char*)user;
	this->info.password = (char*)password;
	this->info.dbName = (char*)dbName;
	this->result = 0;
	this->resultRowNum = 0;
	this->row = 0;
}

MYSQLMANAGER::~MYSQLMANAGER()
{

}

bool MYSQLMANAGER::connect()
{
	if (mysql_real_connect(&mysqlHandler, info.ip, info.user, info.password, info.dbName, info.port, NULL, 0) == 0)
	{
		return false;
	}
	return true;
}

bool MYSQLMANAGER::query(const char* query, int mode)//����ѯ�ɹ�����0��ʧ�ܷ��������,mode 0 Ϊ���룬1Ϊ
{
	if (mysql_query(&mysqlHandler, query))
	{
		return false;
	}
	if (mode == 1)
	{
		result = mysql_store_result(&mysqlHandler);//�洢��ѯ���
		resultRowNum = mysql_num_fields(result);        //�������������ŵ�num��
	}
	return true;
}

int MYSQLMANAGER::fecthNum()
{
	if (!result)
	{
		return 0;
	}
	return resultRowNum;
}

MYSQL_ROW MYSQLMANAGER::fecthRow()
{
	if (!result)
	{
		return 0;
	}
	if (!(row = mysql_fetch_row(result)))
	{
		return 0;
	}
	return row;
}

bool MYSQLMANAGER::freeResult()
{
	mysql_free_result(result);     //�ͷŽ������ռ�õ��ڴ�
	result = 0;
	return true;
}

bool MYSQLMANAGER::close()
{
	mysql_close(&mysqlHandler);
	return true;
}
