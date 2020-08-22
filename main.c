#include "tetris.h"

OperateTet opTet;
OperateTet nextOpTet;

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
	opTet.kind = nextOpTet.kind;
	opTet.rotation_id = 0;

	int nextOpKindIdx = rand()%7;
	nextOpTet.kind = kinds[nextOpKindIdx];

	struct timespec ts;
	ts.tv_sec = 1;
	ts.tv_nsec = 0;

	if(!setable_operated_tet(opTet)) {
		mvprintw(10, 40, "gameover!!");
		nanosleep(&ts, NULL);
		reset_game();
	}
}

long milisec_to_nanosec(int microsec) {
	return 1000000 * microsec;
}

void fall();
void draw();

void remove_line_proc() {
	for(int h = 0; h < HEIGHT; h++) {
		if(is_full_line(h)) {
			delete_line(h);
			move_all_block(h, 1);
		}
	}
}

void fall_proc() {
	opTet.y ++;
	if(!setable_operated_tet(opTet)) {
		opTet.y--;
		change_to_block(opTet);
		remove_line_proc();
		reset_operated_tetrimino();
	}
}

// フィールド外にもテトリミノを描画する関数
void printTetrimino(int tetrimino[4][2], int x, int y) {
	for(int i=0; i < 4; i++) {
		for(int j=0; j < 4; j++) {
			mvprintw(y+i, x+j, " ");
		}
	}

	for(int th=0; th < 4; th++) {
		int x_ = tetrimino[th][0];
		int y_ = tetrimino[th][1];
		mvprintw(y+y_, x+x_, "#");
	}
}

int main(int argc, char *argv[]) {
	nextOpTet.kind = kinds[rand()%7];
	nextOpTet.rotation_id = 0;

	pthread_t fall_thread;
	pthread_t draw_thread;

	int fall_thread_ret = pthread_create(&fall_thread, NULL, (void *)fall, NULL);
	int draw_thread_ret = pthread_create(&draw_thread, NULL, (void *)draw, NULL);

	if(fall_thread_ret != 0 && draw_thread_ret != 0) {
		fprintf(stderr, "thread error");
		exit(1);
	}

	initscr();
	keypad(stdscr, true);
	timeout(0);
	init_field(field);

	reset_operated_tetrimino();
	while(true) {
		int ch = getch();
		if (ch == 'q') {
			pthread_cancel(fall_thread);
			pthread_cancel(draw_thread);
			break;
		} else if (ch == KEY_LEFT) {
			opTet.x--;
			if(!setable_operated_tet(opTet)) {
				opTet.x++;
			}
		} else if (ch == KEY_RIGHT) {
			opTet.x++;
			if(!setable_operated_tet(opTet)) {
				opTet.x--;
			}
		} else if (ch == KEY_DOWN) {
			fall_proc();
		} else if (ch == KEY_UP) {
			while(setable_operated_tet(opTet)) {
				opTet.y++;
			}
			opTet.y--;
			change_to_block(opTet);
			remove_line_proc();
			reset_operated_tetrimino();
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
	}

	endwin();
}

void draw() {
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = milisec_to_nanosec(50);
	while(true) {
		put_tetrimino(tetriminos(opTet.kind, opTet.rotation_id)->tet, opTet.x, opTet.y);
		printTetrimino(tetriminos(nextOpTet.kind, 0)->tet, 15, 2);
		print_field();
		clear_operated_tetrimino();
		nanosleep(&ts, NULL);
	}
}

void fall() {
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = milisec_to_nanosec(700);

	while(true) {
		fall_proc();

		getch();
		nanosleep(&ts, NULL);
	}
}