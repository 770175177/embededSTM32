CC             = gcc
CFLAGS         = -Wall -g -O2 -std=c99 -DRING_BUFFER_TEST

all: simple

simple: ../ring_buffer.c simple.c
	$(CC) $(CFLAGS) -o simple simple.c ../ring_buffer.c

clean:
	rm -f simple
