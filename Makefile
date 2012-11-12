TARGET = hsserver
CC = gcc
CFLAGS = -Wall -I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing
OBJS = hsserver.o avrserial.o hssql.o
LIBS = -L/usr/lib/arm-linux-gnueabihf -lmysqlclient -lpthread -lz -lm -lrt -ldl

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS) $(LIBS)

clean:
	rm -f *.o $(TARGET) $(TARGET).exe core* 
