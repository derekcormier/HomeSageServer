// filename: hssql.c

#include <my_global.h>
#include <mysql.h>
#include <stdio.h>
#include <string.h>

MYSQL* connectTableSQL()
	// POST: Connects to the HomeSage SQL table
{
	MYSQL* conn;

	conn = mysql_init(NULL);		//initialize connection

	if(conn == NULL)			// Check for failure
	{
		printf("SQL initialization unsuccessful.\n");
		return -1;
	}

	if(mysql_real_connect(conn,"localhost","homesage","raspberry",
			"hsdata", 3306, NULL, 0)==NULL)		//Connect to Table
	{
		printf("%s\n", mysql_error(conn));
		return -1;
	}

	return conn;
}

int insertDataSQL(MYSQL* conn, char device[], char voltage[], char current[])
	// PRE:  Device exists, voltage and current from device
	// POST: Returns -1 if write has failed
{
	char SQLQuery[120] = "INSERT INTO data VALUES(NOW(), ";

	strcat( SQLQuery, device);
	strcat( SQLQuery, ", ");
	strcat( SQLQuery, voltage);
	strcat( SQLQuery, ", ");
	strcat( SQLQuery, current);
	strcat( SQLQuery, ");");

	mysql_query(conn, SQLQuery);
	return 0;
}
