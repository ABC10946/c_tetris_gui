#include "tetris.h"
#include "gui.h"

int main(int argc, char *argv[]) {
	init_field(field);
	reset_operated_tetrimino();

	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutReshapeFunc(reshape);
	glutTimerFunc((int)FRAME_FREQ, timer, 0);

	glutMainLoop();
}