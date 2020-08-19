#include "tetris.h"

BlockKind field[21][12] = {};

int i_tet[4][4][2] = {
	{{0, 0}, 
	 {1, 0}, 
	 {2, 0}, 
	 {3, 0}},
	{{0, 0},
	 {0, 1},
	 {0, 2},
	 {0, 3}},
	{{0, 0}, 
	 {1, 0}, 
	 {2, 0}, 
	 {3, 0}},
	{{0, 0},
	 {0, 1},
	 {0, 2},
	 {0, 3}},
};

int o_tet[4][4][2] = {
	{{0, 0},
	 {1, 0},
	 {0, 1},
	 {1, 1}},
	{{0, 0},
	 {1, 0},
	 {0, 1},
	 {1, 1}},
	{{0, 0},
	 {1, 0},
	 {0, 1},
	 {1, 1}},
	{{0, 0},
	 {1, 0},
	 {0, 1},
	 {1, 1}}
};

int s_tet[4][4][2] = {
	{{1, 0},
	 {2, 0},
	 {0, 1},
	 {1, 1}},
	{{0, 0},
	 {0, 1},
	 {1, 1},
	 {1, 2}},
	{{1, 0},
	 {2, 0},
	 {0, 1},
	 {1, 1}},
	{{0, 0},
	 {0, 1},
	 {1, 1},
	 {1, 2}}
};

int z_tet[4][4][2] = {
	{{0, 0},
	 {1, 0},
	 {1, 1},
	 {2, 1}},
	{{1, 0},
	 {0, 1},
	 {1, 1},
	 {0, 2}},
	{{0, 0},
	 {1, 0},
	 {1, 1},
	 {2, 1}},
	{{1, 0},
	 {0, 1},
	 {1, 1},
	 {0, 2}}
};

int j_tet[4][4][2] = {
	{{0, 0},
	 {1, 0},
	 {2, 0},
	 {2, 1}},
	{{1, 0},
	 {1, 1},
	 {1, 2},
	 {0, 2}},
	{{0, 0},
	 {0, 1},
	 {1, 1},
	 {2, 1}},
	{{0, 0},
	 {1, 0},
	 {0, 1},
	 {0, 2}}
};

int l_tet[4][4][2] = {
	{{0, 0},
	 {1, 0},
	 {2, 0},
	 {0, 1}},
	{{0, 0},
	 {1, 0},
	 {1, 1},
	 {1, 2}},
	{{2, 0},
	 {0, 1},
	 {1, 1},
	 {2, 1}},
	{{0, 0},
	 {0, 1},
	 {0, 2},
	 {1, 2}}
};

int t_tet[4][4][2] = {
	{{0, 0},
	 {1, 0},
	 {2, 0},
	 {1, 1}},
	{{1, 0},
	 {0, 1},
	 {1, 1},
	 {1, 2}},
	{{1, 1},
	 {0, 2},
	 {1, 2},
	 {2, 2}},
	{{1, 1},
	 {2, 0},
	 {2, 1},
	 {2, 2}}
};


Tetrimino* tetriminos(TetriminoKind kind, int rotation_id) {
	Tetrimino *tetrimino = calloc(1, sizeof(Tetrimino));

	switch(kind) {
		case Tet_I:
			tetrimino->tet = i_tet[rotation_id];
			return tetrimino;
		case Tet_O:
			tetrimino->tet = o_tet[rotation_id];
			return tetrimino;
		case Tet_S:
			tetrimino->tet = s_tet[rotation_id];
			return tetrimino;
		case Tet_Z:
			tetrimino->tet = z_tet[rotation_id];
			return tetrimino;
		case Tet_J:
			tetrimino->tet = j_tet[rotation_id];
			return tetrimino;
		case Tet_L:
			tetrimino->tet = l_tet[rotation_id];
			return tetrimino;
		case Tet_T:
			tetrimino->tet = t_tet[rotation_id];
			return tetrimino;
		default:
			return tetrimino;
	}
}


void init_field() {
	for(int h = 0; h < HEIGHT; h++) {
		for(int w = 0; w < WIDTH; w++) {
			if(w == 0 || w == WIDTH-1 || h == HEIGHT-1) {
				field[h][w] = Block;
			} else {
				field[h][w] = Space;
			}
		}
	}
}

bool put_tetrimino(int tetrimino[4][2], int x, int y) {
	for(int th = 0; th < 4; th ++) {
		int x_ = tetrimino[th][0];
		int y_ = tetrimino[th][1];
		if(field[y+y_][x+x_] == Block)
			return false;

		field[y+y_][x+x_] = Operating;
	}
	return true;
}



void print_field() {
	for(int h = 0; h < HEIGHT; h++) {
		for(int w = 0; w < WIDTH; w++) {
			if(field[h][w] == Block) {
				printf("■ ");
			}
			else if (field[h][w] == Operating) {
				printf("◆ ");
			} else {
				printf("□ ");
			}
		}
		printf("\n");
	}
}

void clear_operated_tetrimino() {
	for(int h = 0; h < HEIGHT; h++) {
		for(int w = 0; w < WIDTH; w++) {
			if(field[h][w] == Operating) {
				field[h][w] = Space;
			}
		}
	}
}


void put_operated_tet(OperateTet opTet) {
	BlockKind prevField[HEIGHT][WIDTH];
	memcpy(prevField, field, sizeof(field));

	Tetrimino *tetrimino = tetriminos(opTet.kind, opTet.rotation_id);

	if(put_tetrimino(tetrimino->tet, opTet.x, opTet.y)) {
		printf("move!\n");
	} else {
		printf("cannot move!\n");
		memcpy(field, prevField, sizeof(field));
	}
}