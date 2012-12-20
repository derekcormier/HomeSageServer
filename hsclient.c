// file: hsclient.c

#include <fcntl.h>
#include <mysql.h>
#include <pthread.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "avrserial.h"
#include "hssql.h"

	int fpavr;		// File pointer for AVR
	MYSQL* conn;		// MYSQL connection

void * getDataThread(void);	

int main()
{
	pthread_t ID;
	char userChoice;
	char receive[2];

// Connect to the AVR with USART serial connection

	if(-1 == (fpavr = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY)))	// connect to AVR
	{
		printf("Failed to open port to AVR. Terminating.\n");	// Quit if connection fails
		return -1;
	}

	fpavr = initSerialAVR(fpavr);		// Initialize settings for the USART connection

	tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers

// Connect to the MYSQL table to store data

	conn = connectTableSQL();		// store MYSQL connection in conn 

	printf("Welcome to the HomeSage Client!\n");
	printf("If you need help, enter 'H' at the prompt.\n\n");

	pthread_create(&ID, NULL, getDataThread, NULL);

	do		// Ask user for input until they would like to quit
	{
		printf("Enter an option: ");	// Ask the user what they would like to do
		scanf("%c", &userChoice);
		
		while(getc(stdin) != '\n');	// Empty stdin in case of extra characters

		printf("\n\n");

		switch(userChoice)
		{
		case 'H':			// Display the help text
			printf("List of Available Options:\n--------------------\n\n");
			printf("O\tturn [O]ff circuit. You will be prompted as to which.\n");
			printf("P\t[P]ower on circuit. You will be prompted as to which.\n");
			printf("R\tgenerate [R]eport. You may specify circuit and dates.\n");
			break;

		case 'O':			// Turn off a circuit
			printf("Turn off which circuit? (0-2) : ");		// Ask user which circuit to turn off
			scanf("%c", &userChoice);

			while(getc(stdin) != '\n');			// Clear stdin

			switch(userChoice)
			{
			case '0':		// Turn off circuit 0 (light circuit)
				tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers
				reqCStateAVR(fpavr, 0);			// Request the state of the selected circuit

				read(fpavr, receive, 1);		// Get the state of the circuit

				if(receive[0] == HS_CIRC0ON)		// If circuit is on
				{
					togCStateAVR(fpavr, 0);		// Toggle the state of the circuit (turn off)
				}
				else if(receive[0] == HS_CIRC0OFF)	// If circuit is already off, don't toggle
				{
					printf("Circuit 0 is already off!\n\n");
				}
				break;

			case '1':		// Turn off circuit 1 (first outlet)
				tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers
				reqCStateAVR(fpavr, 1);			// Request the state of the selected circuit
				
				read(fpavr, receive, 1);		// Get the state of the circuit

				if(receive[0] == HS_CIRC1ON)		// If circuit is on
				{
					togCStateAVR(fpavr, 1);		// Toggle the state of the circuit (turn off)
				}
				else if(receive[0] == HS_CIRC1OFF)	// If circuit is already off, don't toggle
				{
					printf("Circuit 1 is already off!\n\n");
				}
				break;

			case '2':		// Turn of circuit 2 (first
				tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers
				reqCStateAVR(fpavr, 2);			// Request the state of the selected circuit
				
				read(fpavr, receive, 1);		// Get the state of the circuit

				if(receive[0] == HS_CIRC2ON)		// If circuit is on
				{
					togCStateAVR(fpavr, 2);		// Toggle the state of the circuit (turn off)
				}
				else if(receive[0] == HS_CIRC2OFF)	// If circuit is already off, don't toggle
				{
					printf("Circuit 2 is already off!\n\n");
				}
				break;

			default:
				printf("Not a valid circuit number.");
				break;
			}
			break;

		case 'P':
			printf("Turn on which circuit? (0-2) : ");		// Ask user which circuit to turn on
			scanf("%c", &userChoice);

			while(getc(stdin) != '\n');			// Clear stdin

			switch(userChoice)
			{
			case '0':		// Turn on circuit 0 (light circuit)
				tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers
				reqCStateAVR(fpavr, 0);			// Request the state of the selected circuit

				read(fpavr, receive, 1);		// Get the state of the circuit

				if(receive[0] == HS_CIRC0OFF)		// If circuit is off
				{
					togCStateAVR(fpavr, 0);		// Toggle the state of the circuit (turn on)
				}
				else if(receive[0] == HS_CIRC0ON)	// If circuit is already on, don't toggle
				{
					printf("Circuit 0 is already on!\n\n");
				}
				break;

			case '1':		// Turn on circuit 1 (first outlet)
				tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers
				reqCStateAVR(fpavr, 1);			// Request the state of the selected circuit
				
				read(fpavr, receive, 1);		// Get the state of the circuit

				if(receive[0] == HS_CIRC1OFF)		// If circuit is off
				{
					togCStateAVR(fpavr, 1);		// Toggle the state of the circuit (turn on)
				}
				else if(receive[0] == HS_CIRC1ON)	// If circuit is already on, don't toggle
				{
					printf("Circuit 1 is already on!\n\n");
				}
				break;

			case '2':		// Turn of circuit 2 (second outlet)
				tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers
				reqCStateAVR(fpavr, 2);			// Request the state of the selected circuit
				
				read(fpavr, receive, 1);		// Get the state of the circuit

				if(receive[0] == HS_CIRC2OFF)		// If circuit is off
				{
					togCStateAVR(fpavr, 2);		// Toggle the state of the circuit (turn on)
				}
				else if(receive[0] == HS_CIRC2ON)	// If circuit is already on, don't toggle
				{
					printf("Circuit 2 is already on!\n\n");
				}
				break;

			default:
				printf("Not a valid circuit number.");
				break;
			}
			break;

		case 'R':
			printf("Generate Report.\n\n");
			break;

		case 'Q':
			printf("Cleaning up...\n\n");
			pthread_cancel(ID);
			close(fpavr);
			break;

		default:
			printf("Not a valid option.\n\n");
			break;
		}
		
	} while(userChoice != 'Q');
}

void *getDataThread(void)
{
	while(1)
	{	
		for(int i=0; i<3; i++)		// Cycle between each circuit
		{
			tcflush(fpavr, TCIOFLUSH);		// Clear any data that may be in the lines/buffers

			reqMeasAVR(fpavr, i);			// Request a measurement from the circuit
			
			getMeasAVR(conn,fpavr);
			sleep(1880);						// Get a measurement every 3 minutes (9 minutes between each)
		}
	}
}
