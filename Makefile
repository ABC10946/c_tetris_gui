CC = gcc
CFLAGS = -Wall -std=c11
PROGRAM = tetris
SRCS = main.c tetris.c
LIBS = -lncurses -lpthread

all: $(PROGRAM)

$(PROGRAM): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SRCS) $(LIBS)

clean:
	rm -f $(PROGRAM)
