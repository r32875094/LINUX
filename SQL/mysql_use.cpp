#ifndef MY_SQL_H
#define MY_SQL_H
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
class mysql_use
{

public:
	mysql_use(
			const char * server="localhost",
			const char * user = "run",
			const char * password = "32875094",
			const char * database = "db1"
			)
	{
		conn =mysql_init(NULL);
		if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
			exit(1);
		}
	}

	~mysql_use()
	{
		mysql_close(conn);
		mysql_free_result(res);
	}

	bool IsRight(const char * id,const char * pass)
	{
		char  sql_md[128]={0};
		sprintf(sql_md,"select * from user where id=%s and password=%s",id,pass);	
		mysql_query(conn,sql_md);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		/*while(row !=NULL)
		{
			printf("%s\t %s",row[0],row[1]);
			row = mysql_fetch_row(res);
		}*/
		if(row != NULL)
			return true;
		else
			return false;
	}

	bool Add_user(const char * id,const char * pass)
	{
		if(id ==NULL||pass ==NULL) return false;
		char  sql_md[128]={0};
		sprintf(sql_md,"select * from user where id=%s",id);	
		mysql_query(conn,sql_md);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if(row != NULL)
			return false;
		memset(sql_md,0,128);
		sprintf(sql_md,"insert into user (id,password) values('%s','%s');",id,pass);
		puts(sql_md);
		if( mysql_query(conn,sql_md)==0)
			return true;
		else
			return false;
	}
private:
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
};
static int main3()
{
	mysql_use p;

cout<<p.Add_user("32875094","123456")<<endl;


}
#endif
