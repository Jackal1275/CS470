CC = gcc
CFLAGS = -Wall -g
TARGET = CS470_Lab3

all: $(TARGET)

$(TARGET): CS470_Lab3.c
	$(CC) $(CFLAGS) -o $(TARGET) CS470_Lab3.c

clean:
	rm -f $(TARGET)
