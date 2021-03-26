CC = gcc
CFLAGS = -Wall -std=c11
PROGRAM = tetris
SRCS = main.c tetris.c gui.c
LIBS = -lncurses -lglut -lGLU -lGL

all: $(PROGRAM)

$(PROGRAM): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SRCS) $(LIBS)

clean:
	rm -f $(PROGRAM)
