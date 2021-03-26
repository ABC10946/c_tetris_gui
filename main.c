#include "tetris.h"

//ミリ秒からナノ秒に変換する関数
long milisec_to_nanosec(double milisec) {
	return 1000000 * milisec;
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


void draw() {
	put_tetrimino(tetriminos(opTet.kind, opTet.rotation_id)->tet, opTet.x, opTet.y);
	printTetrimino(tetriminos(nextOpTet.kind, 0)->tet, 15, 2);
	print_field();
	clear_operated_tetrimino();
}


int main(int argc, char *argv[]) {
	nextOpTet.kind = kinds[rand()%7];
	nextOpTet.rotation_id = 0;

	// 毎秒60フレームで実行
	double frame_freq = (1.0/60.0) * 1000;
	int frame_count = 0;

	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = milisec_to_nanosec(frame_freq);

	initscr();
	keypad(stdscr, true);
	timeout(0);
	init_field(field);

	reset_operated_tetrimino();
	while(true) {
		// 60フレームごとに落下処理
		if(frame_count % 60 == 0) {
			fall_proc();
			frame_count = 0;
		}
		draw();

		int ch = getch();
		if (ch == 'q') {
			break;
		} else if (ch == KEY_LEFT) {
			left_proc();
		} else if (ch == KEY_RIGHT) {
			right_proc();
		} else if (ch == KEY_DOWN) {
			fall_proc();
		} else if (ch == KEY_UP) {
			up_proc();
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

		frame_count++;
		nanosleep(&ts, NULL);
	}

	endwin();
}