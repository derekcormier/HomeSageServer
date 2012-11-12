// filename: hssql.h

#include <mysql.h>

#ifndef HSSQL_H_
#define HSSQL_H_

MYSQL* connectTableSQL(); 

int insertDataSQL(int device, double voltage, double current);
// PRE:  Device exists, voltage and current from device
// POST: Returns -1 if write has failed

#endif /* HSSQL_H_ */
