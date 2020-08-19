#include "tetris.h"

OperateTet opTet;

TetriminoKind kinds[7] = {
	Tet_I,
	Tet_O,
	Tet_S,
	Tet_Z,
	Tet_J,
	Tet_L,
	Tet_T
};

void reset_operated_tetrimino() {
	opTet.x = 5;
	opTet.y = 5;
	int i = rand()%7;
	opTet.kind = kinds[i];
	opTet.rotation_id = 0;
}

int main(int argc, char *argv[]) {
	initscr();
	init_field(field);

	reset_operated_tetrimino();
	int dx = 0;
	while(true) {
		opTet.y++;
		if(!setable_operated_tet(opTet)) {
			opTet.y--;
			change_to_block(opTet);
			reset_operated_tetrimino();
		}

		int ch = getch();
		if (ch == 'q') {
			break;
		} else if (ch == 'h') {
			dx--;
		} else if (ch =='l') {
			dx++;
		} else if (ch == 'r') {
			if(opTet.rotation_id < 4) {
				opTet.rotation_id++;
			} else {
				opTet.rotation_id = 0;
			}
		}
		print_field();
		clear_operated_tetrimino();
	}


	endwin();
}
