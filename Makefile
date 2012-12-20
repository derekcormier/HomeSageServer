TARGET = hsserver
CC = gcc
CFLAGS = -Wall -I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing -std=c99
SOBJS = hsserver.o avrserial.o hssql.o
COBJS = hsclient.o avrserial.o hssql.o
LIBS = -L/usr/lib/arm-linux-gnueabihf -lmysqlclient -lpthread -lz -lm -lrt -ldl

hsserver: $(SOBJS)
	$(CC) -o hsserver $(CFLAGS) $(SOBJS) $(LIBS)

hsclient: $(COBJS)
	$(CC) -o hsclient $(CFLAGS) $(COBJS) $(LIBS)

clean:
	rm -f *.o $(TARGET) $(TARGET).exe core* 
