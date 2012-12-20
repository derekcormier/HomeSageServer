// file: hsserver.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <mysql.h>
#include "avrserial.h"
#include "hssql.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <termios.h>
#include <mysql.h>

int main()
{
//	int sockdes;
//	struct sockaddr_in sockaddr;

	MYSQL* conn;

	int fpavr;
	char buffer[10] = "";

/*	if(-1 == (sockdes = socket(AF_INET, SOCK_STREAM, 0)))
	{
		printf("Could not create a socket.");
		return -1;
	}

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(5000);

	bind(sockdes, (struct sockaddr*) &sockaddr, sizeof(sockaddr));
*/

	if(-1 == (fpavr = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY)))
	{
		printf("failed to open port to AVR. Terminating.\n");
		//return -1;
	}
	else
	{
		printf("Established connection to AVR\n");
	}

	fpavr = initSerialAVR(fpavr);

	tcflush(fpavr, TCIOFLUSH);

	reqMeasAVR(fpavr, 0);

	conn = connectTableSQL();

	getMeasAVR(conn, fpavr);

	tcflush(fpavr, TCIOFLUSH);
	
	close(fpavr);
	
	return 0;
}
