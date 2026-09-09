CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O2
TARGET = scheduler
SRCS = main.c parser.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c scheduler.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.out

.PHONY: all clean