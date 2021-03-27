#include "tetris.h"

BlockKind field[HEIGHT][WIDTH] = {};
BlockKind prevField[HEIGHT][WIDTH] = {};

TetriminoKind kinds[7] = {
    Tet_I,
    Tet_O,
    Tet_S,
    Tet_Z,
    Tet_J,
    Tet_L,
    Tet_T
};

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
    {{2, 1},
     {1, 0},
     {1, 1},
     {1, 2}}
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
    holdOpTet.kind = Tet_NULL;
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            if(w == 0 || w == WIDTH-1 || h == HEIGHT-1) {
                field[h][w] = Wall;
            } else {
                field[h][w] = Space;
            }
        }
    }
}

void put_tetrimino(int tetrimino[4][2], int x, int y) {
    for(int th=0; th < 4; th++) {
        int x_ = tetrimino[th][0];
        int y_ = tetrimino[th][1];
        field[y+y_][x+x_] = Operating;
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


bool setable_operated_tet(OperateTet opTet) {
    Tetrimino *tetrimino = tetriminos(opTet.kind, opTet.rotation_id);
    int (*tet)[2] = tetrimino->tet;
    int x = opTet.x;
    int y = opTet.y;

    if((field[y+tet[0][1]][x+tet[0][0]] == Block) ||
       (field[y+tet[1][1]][x+tet[1][0]] == Block) ||
       (field[y+tet[2][1]][x+tet[2][0]] == Block) ||
       (field[y+tet[3][1]][x+tet[3][0]] == Block) ||
       (field[y+tet[0][1]][x+tet[0][0]] == Wall) ||
       (field[y+tet[1][1]][x+tet[1][0]] == Wall) ||
       (field[y+tet[2][1]][x+tet[2][0]] == Wall) ||
       (field[y+tet[3][1]][x+tet[3][0]] == Wall)

       ) {
        return false;
    }

    return true;
}


void change_to_block(OperateTet opTet) {
    Tetrimino *tetrimino = tetriminos(opTet.kind, opTet.rotation_id);
    int (*tet)[2] = tetrimino->tet;
    for(int th = 0; th < 4; th ++) {
        int x_ = tet[th][0];
        int y_ = tet[th][1];

        field[opTet.y+y_][opTet.x+x_] = Block;
    }
}


void move_all_block(int pivot, int step) {
    for(int h = HEIGHT; h > 0; h--) {
        for(int w = 0; w < WIDTH; w++) {
            if(field[h][w] == Block && h < pivot) {
                field[h][w] = Space;
                field[h + step][w] = Block;
            }
        }
    }
}


void delete_line(int line_num) {
    for(int w = 0; w < WIDTH; w++) {
        if(field[line_num][w] == Block) {
            field[line_num][w] = Space;
        }
    }
}


bool is_full_line(int line_num) {
    int ret = 0;
    for(int w = 0; w < WIDTH; w++) {
        if(field[line_num][w] == Block)
            ret++;
    }
    if(ret == WIDTH-2) return true;
    return false;
}


void reset_game() {
    holdOpTet.kind = Tet_NULL;
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            if(field[h][w] != Wall) {
                field[h][w] = Space;
            }
        }
    }
}

void setNextOpTet() {
    int nextOpKindIdx = rand()%7;
    nextOpTet.kind = kinds[nextOpKindIdx];
}

void reset_operated_tetrimino() {
    opTet.x = 5;
    opTet.y = 0;
    opTet.kind = nextOpTet.kind;
    opTet.rotation_id = 0;

    setNextOpTet();

    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 0;

    if(!setable_operated_tet(opTet)) {
        nanosleep(&ts, NULL);
        reset_game();
    }
}


// 左入力処理
void left_proc() {
    opTet.x--;
    if(!setable_operated_tet(opTet)) {
        opTet.x++;
    }
}


// 右入力処理
void right_proc() {
    opTet.x++;
    if(!setable_operated_tet(opTet)) {
        opTet.x--;
    }
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


// 上入力処理
void up_proc() {
    while(setable_operated_tet(opTet)) {
        opTet.y++;
    }
    opTet.y--;
    change_to_block(opTet);
    remove_line_proc();
    reset_operated_tetrimino();
}


// 回転処理
void rotate_proc() {
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


// テトリミノ保持処理
void hold_tet() {
    if (holdOpTet.kind == Tet_NULL) {
        holdOpTet.kind = opTet.kind;
        opTet.kind = nextOpTet.kind;
    } else {
        OperateTet tempTet;
        tempTet.kind = holdOpTet.kind;
        holdOpTet.kind = opTet.kind;
        opTet.kind = tempTet.kind;
    }
}