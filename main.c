#include "tetris.h"

int main(int argc, char *argv[]) {
	init_field(field);

	OperateTet opTet;
	opTet.x = 5;
	opTet.y = 15;
	opTet.kind = Tet_T;
	opTet.rotation_id = 1;


	for(int i=0; i < 6; i++) {
		clear_operated_tetrimino();
		put_operated_tet(opTet);
		print_field();
		opTet.y++;
	}
	
	opTet.y = 15;
	for(int i=0; i < 6; i++) {
		clear_operated_tetrimino();
		put_operated_tet(opTet);
		print_field();
		opTet.x++;
	}
}
