#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>
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
	Operating,
	Wall
} BlockKind;


typedef enum {
	Up,
	Down,
	Left,
	Right
} Direction;

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

typedef struct OperateTet {
	int x;
	int y;
	TetriminoKind kind;
	int rotation_id;
} OperateTet;

Tetrimino* tetriminos(TetriminoKind, int);

void init_field();

void put_tetrimino(int (*)[2], int, int);

void print_field();

void clear_operated_tetrimino();

bool setable_operated_tet(OperateTet);

void change_to_block(OperateTet);

void move_all_block(int, int);

void delete_line(int);

bool is_full_line(int);

void reset_game();