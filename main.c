#include "tetris.h"

int main(int argc, char *argv[]) {
	/*
	TetriminoKind kinds[7] = {
		Tet_I,
		Tet_O,
		Tet_S,
		Tet_Z,
		Tet_J,
		Tet_L,
		Tet_T
	};
	*/

	init_field(field);

	OperateTet opTet;
	opTet.x = 5;
	opTet.y = 5;
	opTet.kind = Tet_T;
	opTet.rotation_id = 1;

	/*
	for(int i=0; i < 7; i++) {
		for(int j=0; j < 4; j++) {
			init_field(field);
			opTet.kind = kinds[i];
			opTet.rotation_id = j;
			put_operate_tet(opTet);
			//put_tetrimino(tetriminos(kinds[i], j)->tet, 5, 5);
			print_field();
		}
	}
	*/

	for(int i=0; i < 8; i++) {
		clear_operated_tetrimino();
		put_operated_tet(opTet);
		print_field();
		opTet.y++;
	}

}
