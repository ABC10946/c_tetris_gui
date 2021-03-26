#include "tetris.h"
#include "gui.h"


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


//ミリ秒からナノ秒に変換する関数
long milisec_to_nanosec(double milisec) {
	return 1000000 * milisec;
}


void remove_line_proc() {
	for(int h = 0; h < HEIGHT; h++) {
		if(is_full_line(h)) {
			delete_line(h);
			move_all_block(h, 1);
		}
	}
}

// テトリミノの落下処理と床当たり判定処理
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


void draw() {
	put_tetrimino(tetriminos(opTet.kind, opTet.rotation_id)->tet, opTet.x, opTet.y);
	printTetrimino(tetriminos(nextOpTet.kind, 0)->tet, 15, 2);
	print_field();
	clear_operated_tetrimino();
}


int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMainLoop();

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

		frame_count++;
		nanosleep(&ts, NULL);
	}

	endwin();
}