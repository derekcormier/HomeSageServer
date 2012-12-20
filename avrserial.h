// filename: avrserial.h

#ifndef AVRSERIAL_H_
#define AVRSERIAL_H_

#include <mysql.h>

#define HS_GETMEAS0					0xA0
#define HS_GETMEAS1					0xA1
#define HS_GETMEAS2					0xA2
#define HS_GETCSTATE0				0xB0
#define HS_GETCSTATE1				0xB1
#define HS_GETCSTATE2				0xB2
#define HS_TOGCSTATE0				0xC0
#define HS_TOGCSTATE1				0xC1
#define HS_TOGCSTATE2				0xC2
#define HS_CIRC0ON					0xD0
#define HS_CIRC1ON					0xD1
#define HS_CIRC2ON					0xD2
#define HS_CIRC0OFF					0xD8
#define HS_CIRC1OFF					0xD9
#define HS_CIRC2OFF					0xDA

int initSerialAVR(int device);
// POST: Initializes serial communication to and from the AVR

void sendByteAVR(int fpavr, char* data);
// POST: Send byte of data to AVR serial

void* getByteAVR(int fpavr);
// POST: Get byte of data from AVR serial

void reqMeasAVR(int fpavr, char device);
// POST: Request measurement from device

void reqCStateAVR(int fpavr, char device);
// POST: Request circuit state

void togCStateAVR(int fpavr, char device);
// POST: Toggle circuit state

void getMeasAVR(MYSQL* conn, int fpavr);
// POST: Gets measurements from the AVR

#endif /* AVRSERIAL_H_ */
