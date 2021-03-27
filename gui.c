#include "gui.h"
#include "tetris.h"

float rect_width = 0.1;
float rect_height = 0.1;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glLoadIdentity();

    glOrtho(-(float)w/480.0, (float)w/480.0, -(float)h/480.0, (float)h/480.0, -1.0, 1.0);
}

void strokeRectangle(float x, float y) {
    glBegin(GL_LINE_LOOP);
    x = x - (WIDTH * rect_width)/2;
    y = y - (HEIGHT * rect_height)/2;
    glVertex2d(x, y);
    glVertex2d(x+rect_width, y);
    glVertex2d(x+rect_width, y+rect_height);
    glVertex2d(x, y+rect_height);
    glEnd();
}

void polygonRectangle(float x, float y) {
    glBegin(GL_POLYGON);
    x = x - (WIDTH * rect_width)/2;
    y = y - (HEIGHT * rect_height)/2;
    glVertex2d(x, y);
    glVertex2d(x+rect_width, y);
    glVertex2d(x+rect_width, y+rect_height);
    glVertex2d(x, y+rect_height);
    glEnd();
}

void displayTetrimino(TetriminoKind kind, int rotation_id, int x, int y) {
    if(kind != Tet_NULL) {
        int tetrimino[4][2];
        memcpy(tetrimino, tetriminos(kind, rotation_id)->tet, sizeof(tetrimino));
        for(int th=0; th < 4; th++) {
            int x_ = tetrimino[th][0];
            int y_ = tetrimino[th][1];
            glColor3d(1.0, 1.0, 1.0);
            polygonRectangle((x+x_) * rect_width, (y+y_) * rect_height);
            glColor3d(0.0, 0.0, 0.0);
            strokeRectangle((x+x_) * rect_width, (y+y_) * rect_height);
        }
    }
}

void display_field() {
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            if(field[h][w] == Block) {
                glColor3d(1.0, 1.0, 1.0);
                polygonRectangle(w * rect_width, (HEIGHT-h) * rect_height);
                glColor3d(0.0, 0.0, 0.0);
                strokeRectangle(w * rect_width, (HEIGHT-h) * rect_height);
            } else if (field[h][w] == Wall) {
                glColor3d(1.0, 1.0, 1.0);
                polygonRectangle(w * rect_width, (HEIGHT-h) * rect_height);
                glColor3d(0.0, 0.0, 0.0);
                strokeRectangle(w * rect_width, (HEIGHT-h) * rect_height);
            } else if (field[h][w] == Operating) {
                glColor3d(1.0, 1.0, 1.0);
                strokeRectangle(w * rect_width, (HEIGHT-h) * rect_height);
            }
        }
    }
}

void display(void) {
    put_tetrimino(tetriminos(opTet.kind, opTet.rotation_id)->tet, opTet.x, opTet.y);

    glClear(GL_COLOR_BUFFER_BIT);
    // 次テトリミノを表示
    displayTetrimino(nextOpTet.kind, 0, 14, (HEIGHT-2));

    // ホールドテトリミノを表示
    displayTetrimino(holdOpTet.kind, 0, -5, (HEIGHT-2));
    display_field();
    glFlush();

    clear_operated_tetrimino();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'q':
            exit(0);
        case 'r':
            rotate_proc();
            break;
        case 's':
            hold_tet();
            break;
    }
}

int frame_count = 0;

void timer(int value) {
    if(frame_count % 60 == 0) {
        fall_proc();
        frame_count = 0;
    }

    glutPostRedisplay();
    glutTimerFunc((int)FRAME_FREQ, timer, 0);
    frame_count++;
}

void specialKeyboard(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:
            left_proc();
            break;
        case GLUT_KEY_RIGHT:
            right_proc();
            break;
        case GLUT_KEY_DOWN:
            fall_proc();
            break;
        case GLUT_KEY_UP:
            up_proc();
            break;
        default:
            break;
    }
}