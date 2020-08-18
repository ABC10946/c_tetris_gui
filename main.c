#include <stdio.h>
#define WIDTH 12
#define HEIGHT 21

int field[HEIGHT][WIDTH] = {0};

void init_field() {
	for(int h = 0; h < HEIGHT; h++) {
		for(int w = 0; w < WIDTH; w++) {
			if(w == 0 || w == WIDTH-1 || h == HEIGHT-1) {
				field[h][w] = 1;
			}
		}
	}
}


int main(int argc, char *argv[]) {
	init_field(field);
	for(int h = 0; h < HEIGHT; h++) {
		for(int w = 0; w < WIDTH; w++) {
			printf("%d ", field[h][w]);
		}
		printf("\n");
	}
}
