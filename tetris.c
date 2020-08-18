#include "tetris.h"

int field[21][12] = {0};

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
	memset(field, 0, sizeof(field));
	for(int h = 0; h < HEIGHT; h++) {
		for(int w = 0; w < WIDTH; w++) {
			if(w == 0 || w == WIDTH-1 || h == HEIGHT-1) {
				field[h][w] = 1;
			}
		}
	}
}


void put_tetrimino(int tetrimino[4][2], int x, int y) {
	for(int th = 0; th < 4; th ++) {
		int x_ = tetrimino[th][0];
		int y_ = tetrimino[th][1];
		field[y+y_][x+x_] = 1;
	}
}


void print_field() {
	for(int h = 0; h < HEIGHT; h++) {
		for(int w = 0; w < WIDTH; w++) {
			if(field[h][w] == 1) {
				printf("■ ");
			} else {
				printf("□ ");
			}
		}
		printf("\n");
	}
}