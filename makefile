CC=gcc
CFLAGS=#-Wall
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

main: main.c
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: clean

clean:
	rm -f main
