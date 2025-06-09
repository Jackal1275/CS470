CC = gcc
CFLAGS = -Wall -g
OBJS = CS470_Lab4_libFS.o CS470_Lab4_testFS.o
TARGET = CS470_Lab4_testFS

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

CS470_Lab4_libFS.o: CS470_Lab4_libFS.c CS470_Lab4_libFS.h
	$(CC) $(CFLAGS) -c CS470_Lab4_libFS.c

CS470_Lab4_testFS.o: CS470_Lab4_testFS.c CS470_Lab4_libFS.h
	$(CC) $(CFLAGS) -c CS470_Lab4_testFS.c

clean:
	rm -f *.o $(TARGET)
