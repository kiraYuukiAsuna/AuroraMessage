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
	* Function:类的构造函数
	************************************************************/
	MYSQLMANAGER(const char* ip, const int port, const char* user, const char* password, const char* dbName);


	/************************************************************
	* FunctionName:MYSQLMANAGER
	* Function:类的构造函数
	************************************************************/
	~MYSQLMANAGER();

	/************************************************************
	* FunctionName:connect
	* Function:连接
	************************************************************/
	bool connect();

	/************************************************************
	* FunctionName:query
	* Function:执行mysql语句
	************************************************************/
	bool query(const char* query, int mode);
	//若查询成功返回0，失败返回随机数,mode 0 为插入，1为查询

	/************************************************************
	* FunctionName:fecthNum
	* Function:获取执行语句后的返回结果的数目
	************************************************************/
	int fecthNum();

	/************************************************************
	* FunctionName:fecthRow
	* Function:获取执行语句后的返回结果-记录集
	************************************************************/
	MYSQL_ROW fecthRow();

	/************************************************************
	* FunctionName:freeResult
	* Function:释放记录集
	************************************************************/
	bool freeResult();

	/************************************************************
	* FunctionName:close
	* Function:断开连接
	************************************************************/
	bool close();

};
