#include "tetris.h"

int main(int argc, char *argv[]) {
	TetriminoKind kinds[7] = {
		Tet_I,
		Tet_O,
		Tet_S,
		Tet_Z,
		Tet_J,
		Tet_L,
		Tet_T
	};
	init_field(field);
	for(int i=0; i < 7; i++) {
		for(int j=0; j < 4; j++) {
			init_field(field);
			put_tetrimino(tetriminos(kinds[i], j)->tet, 5, 5);
			print_field();
		}
	}
}
