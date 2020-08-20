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
	opTet.y = 0;
	int i = rand()%7;
	opTet.kind = kinds[i];
	opTet.rotation_id = 0;
}

int main(int argc, char *argv[]) {
	initscr();
	init_field(field);

	reset_operated_tetrimino();
	while(true) {
		put_tetrimino(tetriminos(opTet.kind, opTet.rotation_id)->tet, opTet.x, opTet.y);

		opTet.y++;
		if(!setable_operated_tet(opTet)) {
			opTet.y--;
			change_to_block(opTet);
			reset_operated_tetrimino();
		}

		print_field();
		int ch = getch();
		if (ch == 'q') {
			break;
		} else if (ch == 'h') {
			opTet.x--;
			if(!setable_operated_tet(opTet)) {
				opTet.x++;
			}
		} else if (ch =='l') {
			opTet.x++;
			if(!setable_operated_tet(opTet)) {
				opTet.x--;
			}
		} else if (ch == 'r') {
			if(opTet.rotation_id < 3) {
				opTet.rotation_id++;
				if(!setable_operated_tet(opTet)) {
					opTet.rotation_id--;
				}
			} else {
				opTet.rotation_id = 0;
				if(!setable_operated_tet(opTet)) {
					opTet.rotation_id = 3;
				}
			}
		}
		clear_operated_tetrimino();
	}


	endwin();
}
