// filename: avrserial.h


#ifndef AVRSERIAL_H_
#define AVRSERIAL_H_

#define HS_RETRIEVEMEASUREMENTS		0xAA
#define HS_GETCIRCUITSTATE0			0xB0
#define HS_GETCIRCUITSTATE1			0xB1
#define HS_GETCIRCUITSTATE2			0xB2
#define HS_TOGGLECIRCUITSTATE0		0xC0
#define HS_TOGGLECIRCUITSTATE1		0xC1
#define HS_TOGGLECIRCUITSTATE2		0xC2

void initSerialAVR(int device);
// POST: Initializes serial communication to and from the AVR

void sendByteAVR(char data);
// POST: Send byte of data to AVR serial

char getByteAVR();
// POST: Get byte of data from AVR serial

#endif /* AVRSERIAL_H_ */
