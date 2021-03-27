#ifndef GUI_H
#define GUI_H
#include <GL/glut.h>
#include "tetris.h"
#define WINDOW_WIDTH 520
#define WINDOW_HEIGHT 560
#define FRAME_FREQ ((1.0/60.0) * 1000)

void display(void);
void reshape(int w, int h);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);
void timer(int);

#endif