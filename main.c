#include "tetris.h"

int main(int argc, char *argv[]) {
	init_field(field);

	OperateTet opTet;
	opTet.x = 5;
	opTet.y = 15;
	opTet.kind = Tet_T;
	opTet.rotation_id = 1;


	for(int i=0; i < 6; i++) {
		opTet.y++;
		if(!setable_operated_tet(opTet)) {
			opTet.y--;
			change_to_block(opTet);
		}
		print_field();
		clear_operated_tetrimino();
	}
	
	opTet.kind = Tet_J;
	opTet.rotation_id = 0;
	opTet.y = 10;
	for(int i=0; i < 10; i++) {
		opTet.y++;
		if(!setable_operated_tet(opTet)) {
			opTet.y--;
			change_to_block(opTet);
		}
		print_field();
		clear_operated_tetrimino(opTet);
	}
}
