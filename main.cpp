#include <iostream>

#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"

#ifndef _DEBUG
#pragma comment(lib, "mysqlcppconn")
#else
#pragma comment(lib, "debug/mysqlcppconn")
#endif //_DEBUG


int main()
{
	std::string UserID = "junios";
	std::string Password = "1234";
	try
	{
		sql::Driver* MyDriver; //workbench
		sql::Connection* MyConnection; //접속 정보
		sql::Statement* MyStatement; //쿼리 창
		sql::ResultSet* MyResultSet; //결과 창

		MyDriver = get_driver_instance();
		MyConnection = MyDriver->connect("tcp://127.0.0.1", "junios", "qweasd123");

		MyConnection->setSchema("membership");
		MyStatement = MyConnection->createStatement();
		sql::SQLString Query = "select * from user where `user_id` = '";
		Query = Query + UserID + "' and `user_pw` = sha2('";
		Query = Query + Password + "', 512) and is_deleted = 'N';";

		std::cout << Query << std::endl;

		MyResultSet = MyStatement->executeQuery(Query);

		for (; MyResultSet->next();)
		{
			std::cout << MyResultSet->getInt("idx") << std::endl;
			std::cout << MyResultSet->getString("user_id") << std::endl;
			std::cout << MyResultSet->getString("user_pw") << std::endl;
			std::cout << MyResultSet->getString("name") << std::endl;
			std::cout << MyResultSet->getInt("is_deleted") << std::endl;
			std::cout << MyResultSet->getString("created_at") << std::endl;
		}



	}
	catch (sql::SQLException Exception)
	{
		std::cout << Exception.what() << std::endl;
		std::cout << Exception.getSQLState() << std::endl;
	}

	return 0;
}