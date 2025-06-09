# Makefile for CS470_Lab2

CC = gcc
CFLAGS = -Wall -g
TARGET = CS470_Lab2

all: $(TARGET)

$(TARGET): CS470_Lab2.c
	$(CC) $(CFLAGS) -o $(TARGET) CS470_Lab2.c

clean:
	rm -f $(TARGET)
