// filename: hssql.h

#include <mysql.h>

#ifndef HSSQL_H_
#define HSSQL_H_

MYSQL* connectTableSQL(); 
// POST: Connects to the HomeSage SQL table

int insertDataSQL(MYSQL* conn, char device[], char voltage[], char current[]);
// PRE:  Device exists, voltage and current from device
// POST: Returns -1 if write has failed

#endif /* HSSQL_H_ */
