#include"mysql8.0.19/include/mysql.h"

class MYSQLMANAGER {
private:

	struct connectInfo
	{
		char* ip;
		int port;
		char* user;
		char* password;
		char* dbName;
	};

	MYSQL mysqlHandler;
	connectInfo info;
	MYSQL_RES* result;
	int resultRowNum;
	MYSQL_ROW row;

public:

	/************************************************************
	* FunctionName:MYSQLMANAGER
	* Function:��Ĺ��캯��
	************************************************************/
	MYSQLMANAGER(const char* ip, const int port, const char* user, const char* password, const char* dbName);


	/************************************************************
	* FunctionName:MYSQLMANAGER
	* Function:��Ĺ��캯��
	************************************************************/
	~MYSQLMANAGER();

	/************************************************************
	* FunctionName:connect
	* Function:����
	************************************************************/
	bool connect();

	/************************************************************
	* FunctionName:query
	* Function:ִ��mysql���
	************************************************************/
	bool query(const char* query, int mode);
	//����ѯ�ɹ�����0��ʧ�ܷ��������,mode 0 Ϊ���룬1Ϊ��ѯ

	/************************************************************
	* FunctionName:fecthNum
	* Function:��ȡִ������ķ��ؽ������Ŀ
	************************************************************/
	int fecthNum();

	/************************************************************
	* FunctionName:fecthRow
	* Function:��ȡִ������ķ��ؽ��-��¼��
	************************************************************/
	MYSQL_ROW fecthRow();

	/************************************************************
	* FunctionName:freeResult
	* Function:�ͷż�¼��
	************************************************************/
	bool freeResult();

	/************************************************************
	* FunctionName:close
	* Function:�Ͽ�����
	************************************************************/
	bool close();

};
