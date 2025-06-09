# Makefile for process_simulator

CC = gcc
CFLAGS = -Wall -g
TARGET = process_simulator

all: $(TARGET)

$(TARGET): process_simulator.c
	$(CC) $(CFLAGS) -o $(TARGET) process_simulator.c

clean:
	rm -f $(TARGET)
