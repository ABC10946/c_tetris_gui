#include "tetris.h"

OperateTet opTet;

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
	int i = rand()%7;
	opTet.kind = kinds[i];
	opTet.rotation_id = 0;
}

long milisec_to_nanosec(int microsec) {
	return 1000000 * microsec;
}

void fall();
void draw();

int main(int argc, char *argv[]) {
	pthread_t fall_thread;
	pthread_t draw_thread;

	int fall_thread_ret = pthread_create(&fall_thread, NULL, (void *)fall, NULL);
	int draw_thread_ret = pthread_create(&draw_thread, NULL, (void *)draw, NULL);

	if(fall_thread_ret != 0 && draw_thread_ret != 0) {
		fprintf(stderr, "thread error");
		exit(1);
	}

	initscr();
	timeout(0);
	init_field(field);

	reset_operated_tetrimino();
	while(true) {
		int ch = getch();
		if (ch == 'q') {
			pthread_cancel(fall_thread);
			pthread_cancel(draw_thread);
			break;
		} else if (ch == 'h') {
			opTet.x--;
			if(!setable_operated_tet(opTet)) {
				opTet.x++;
			}
		} else if (ch =='l') {
			opTet.x++;
			if(!setable_operated_tet(opTet)) {
				opTet.x--;
			}
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
		opTet.y ++;
		if(!setable_operated_tet(opTet)) {
			opTet.y--;
			change_to_block(opTet);
			reset_operated_tetrimino();
		}

		getch();
		nanosleep(&ts, NULL);
	}
}