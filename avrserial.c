// filename: avrserial.c

#include <termios.h>
#include <fcntl.h>

void initSerialAVR(int fpavr)
{
	struct termios term;

	tcgetattr(fpavr, &term);

	cfsetispeed(&term, B9600);
	cfsetospeed(&term, B9600);

	term.c_cflag = CS8 | CREAD;
}

void sendByteAVR(char data)
{
	// code
}

char getByteAVR()
{
	// code
	return ;
}
