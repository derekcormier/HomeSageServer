// filename: hssql.c


#include <my_global.h>
#include <mysql.h>
#include <stdio.h>


MYSQL* connectTableSQL()
{
	MYSQL* conn;

	conn = mysql_init(NULL);

	if(conn == NULL)
	{
		printf("SQL initialization unsuccessful.\n");
	}

	if(mysql_real_connect(conn,"localhost","homesage","raspberry",
			"hsdata", 3306, NULL, 0)==NULL)
	{
		printf("%s\n", mysql_error(conn));
	}

	printf("connected\n");

	mysql_query(conn, "INSERT INTO datatest VALUES(NOW(), 2, 345.4444, 453.0505)");

	mysql_close(conn);

	return conn;
}

int insertDataSQL(int device, double voltage, double current)
{
	return 0;
}
