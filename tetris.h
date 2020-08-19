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


typedef enum {
	Space,
	Block,
	Operating
} BlockKind;

BlockKind field[HEIGHT][WIDTH];


extern int i_tet[4][4][2];
extern int o_tet[4][4][2];
extern int s_tet[4][4][2];
extern int z_tet[4][4][2];
extern int j_tet[4][4][2];
extern int l_tet[4][4][2];
extern int t_tet[4][4][2];

typedef struct Tetrimino {
	int (*tet)[];
} Tetrimino;


Tetrimino* tetriminos(TetriminoKind, int);

void init_field();

void put_tetrimino();

void print_field();
