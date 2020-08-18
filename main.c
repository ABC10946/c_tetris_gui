#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WIDTH 12
#define HEIGHT 21

typedef enum {
	Tet_I,
	Tet_O,
	Tet_S,
	Tet_Z,
	Tet_J,
	Tet_L,
	Tet_T
} TetriminoKind;

int field[HEIGHT][WIDTH];

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

typedef struct Tetrimino {
	int (*tet)[];
} Tetrimino;

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
