// file: hsserver.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <mysql.h>
#include "avrserial.h"
#include "hssql.h"

int main()
{
	int fpavr;
	//char buffer[30];

	if(-1 == (fpavr = open("/dev/ttyACM0", O_RDWR | O_NOCTTY)))
	{
		printf("failed to open port to AVR. Terminating.\n");
		//return -1;
	}
	else
	{
		printf("Established connection to AVR\n");
	}

	initSerialAVR(fpavr);

	//read(fpavr,buffer,sizeof(buffer));

	//printf(buffer);

	connectTableSQL();	

	return 0;
}
