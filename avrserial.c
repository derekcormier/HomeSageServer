// filename: avrserial.c

#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <mysql.h>
#include "avrserial.h"
#include "hssql.h"

int initSerialAVR(int fpavr)
	// POST: Initializes serial communication to and from the AVR
{
	struct termios term;		// create termios struct for serial

	tcgetattr(fpavr, &term);

	cfsetispeed(&term, B9600);	// set read and write baud to 9600
	cfsetospeed(&term, B9600);

	term.c_cflag |= (CS8 | CREAD);	// data is 8 bits, enable reciever
	term.c_lflag |= ICANON;
	tcsetattr(fpavr, TCSANOW, &term);	// apply attributes of fpavr to term

	return fpavr;
}

void sendByteAVR(int fpavr, char * data)
	// POST: Send byte of data to AVR serial
{
	write(fpavr, (const void *) data, 1);		// send byte to the AVR
}

void* getByteAVR(int fpavr)	
	// POST: Get byte of data from AVR serial
{
	char* data = NULL;					// char to store byte from AVR

	read(fpavr,(void *) data, 1);			// get byte from AVR
	return (char*) data;				// return recieved byte
}

void reqMeasAVR(int fpavr, char device)
	// POST: Request measurement from device
{
	device += 0xA0;
	char* command = &device;
	sendByteAVR(fpavr, command);
}

void reqCStateAVR(int fpavr, char device)
	// POST: Request circuit state
{
	device += 0xB0;
	char* command = &device;
	sendByteAVR(fpavr, command);
}

void togCStateAVR(int fpavr, char device)
	// POST: Toggle circuit state
{
	device += 0xC0;
	char* command = &device;
	sendByteAVR(fpavr, command);
}

void getMeasAVR(MYSQL* conn, int fpavr)
	// POST: Gets measurements from the AVR
{
	char device[2];
	char voltage[6];
	char current[8];

	read(fpavr, device, 1);
	device[1] = '\0';
	read(fpavr, voltage, 5);
	voltage[5] = '\0';
	read(fpavr, current, 7);
	current[7] = '\0';

	insertDataSQL(conn, &device, &voltage, &current);	
}

void displayCir(int fpavr, int device)
	// POST: Tells the LCD which measurements to display
{
	device += 0xE0;
	char* command = &device;
	sendByteAVR(fpavr, command);
}
