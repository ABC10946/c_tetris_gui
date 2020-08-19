CC = gcc
CFLAGS = -Wall -std=c11
PROGRAM = tetris
SRCS = main.c tetris.c

all: $(PROGRAM)

$(PROGRAM): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SRCS)

clean:
	rm -f $(PROGRAM)
