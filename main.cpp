#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>
#include <cstdio>
#include<synchapi.h>
#include<iostream>
#include<sstream>
#include "cars.h"
using namespace std;
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")



void InitGraphics(int argc, char* argv[]);
void SetTransformations();
void Display();
float tile1_movement = -140;
float tile2_movement = -40;
float tile3_movement = 80;
float speed_move = 10;
float speed_tiles = 2;
float car1_movment = 300;
float car2_movment = 700;
float car3_movment = 600;
boolean crashed = false;
boolean gap = false;
char identity;
cars car_m(0, -195, 0.7, 0, 0, 'm');
cars car_o(0, car1_movment, 0, 1, 0, 'o');
cars car_o1(40, car2_movment, 0, 0, 1, 'o');
cars car_o2(-40, car3_movment, 1, 1, 1, 'o');
void timer(int value)
{
    const int desiredFPS = 125;
    glutTimerFunc(1000 / desiredFPS, timer, ++value);
    glutPostRedisplay();
}

void OnKeyPress(unsigned char key, int x, int y) {
    switch (key) {
    case 'a'://		a key
    case 'A':
        if (!crashed) {
            if (car_m.x - speed_move > -55) {
                car_m.x -= speed_move;

                break;
            }

        }
        break;
    case 'd'://		d key
    case 'D':
        if (!crashed) {
            if (car_m.x + speed_move < 55) {
                car_m.x += speed_move;
                break;
            }
        }
        break;

    case 'w'://		d key
    case 'W':
        if (!crashed) {
            if (car_m.y + speed_move < 200) {
                car_m.y += speed_move;

                break;
            }

        }
        break;
    case 's':
    case 'S':
        if (!crashed) {
            if (car_m.y - speed_move > -195) {
                car_m.y -= speed_move;

                break;
            }
        }
        break;

    }

}


int main(int argc, char* argv[]) {
    InitGraphics(argc, argv);
    srand(time(NULL));
    return 0;
}



void InitGraphics(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GL_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1020, 720);
    glutCreateWindow("Bouncing car");
    glutTimerFunc(0, timer, 0);
    glutDisplayFunc(Display);
    glutKeyboardFunc(OnKeyPress);
    SetTransformations();
    glutMainLoop();

}

void SetTransformations() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

void crash_check() {

    if (((abs(car_m.x - car_o.x) < 25) & (abs(car_o.y + 100) < 15) | //  main car 
        (abs(car_m.x - car_o1.x) < 25) & (abs(car_o1.y + 100) < 15) |
        (abs(car_m.x - car_o2.x) < 25) & (abs(car_o2.y + 100) < 15))) {// car 2

        speed_tiles = 0;
        car_o.speed = 0;
        car_o1.speed = 0;
        car_o2.speed = 0;
        crashed = true;


    }

}

void draw_street() {
    glBegin(GL_QUADS);
    glColor4f(0.1, 0.1, 0.1, 0.60);
    glVertex2i(-75, 200);
    glVertex2i(75, 200);
    glVertex2i(75, -200);
    glVertex2i(-75, -200);
    glEnd();
}

void draw_tiles() {
    glPushMatrix();
    glTranslatef(0, tile1_movement, 0);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(-25, -200);
    glVertex2i(-30, -200);
    glVertex2i(-30, -120);
    glVertex2i(-25, -120);

    glVertex2i(25, -200);
    glVertex2i(30, -200);
    glVertex2i(30, -120);
    glVertex2i(25, -120);
    glEnd();

    tile1_movement -= speed_tiles;
    if (tile1_movement <= -280) {
        glLoadIdentity();
        tile1_movement = 400;
        glTranslatef(0, tile1_movement, 0);
    }
    glPopMatrix();
    // --------------------------------------------------------------
    //first row tile 2
    //--------------------------------------------------------------
    glPushMatrix();
    glTranslatef(0, tile2_movement, 0);
    glBegin(GL_QUADS);

    glColor3f(1, 1, 1);//cyan
    glVertex2i(-25, -100);
    glVertex2i(-30, -100);
    glVertex2i(-30, -20);
    glVertex2i(-25, -20);

    glVertex2i(25, -100);
    glVertex2i(30, -100);
    glVertex2i(30, -20);
    glVertex2i(25, -20);

    glEnd();
    tile2_movement -= speed_tiles;
    if (tile2_movement <= -280) {
        glLoadIdentity();
        tile2_movement = 400;
        glTranslatef(0, tile2_movement, 0);
    }
    glPopMatrix();
    // --------------------------------------------------------------
    //first row tile 3
    //--------------------------------------------------------------
    glPushMatrix();
    glTranslatef(0, tile3_movement, 0);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);//cyan
    glVertex2i(-25, 0);
    glVertex2i(-30, 0);
    glVertex2i(-30, 80);
    glVertex2i(-25, 80);

    glVertex2i(25, 0);
    glVertex2i(30, 0);
    glVertex2i(30, 80);
    glVertex2i(25, 80);
    glEnd();
    tile3_movement -= speed_tiles;
    if (tile3_movement <= -280) {
        glLoadIdentity();
        tile3_movement = 400;
        glTranslatef(0, tile3_movement, 0);
    }

    glPopMatrix();
}
//void randomlogic() {
//    //while (!gap) {
//        
//        car_o.counter = rand() % 301 + 300;
//        //srand(time(NULL));
//        car_o1.counter = rand() % 901 + 100;
//        //srand(time(NULL));
//        car_o2.counter = rand() % 301 + 300;
//       //cout << car_o.y << "," << car_o1.y << "," << car_o2.y << endl;
//        if (((abs(car1_movment - car2_movment) > 200) & (abs(car1_movment - car3_movment) > 200)) |
//            (abs(car2_movment - car3_movment) > 200)) {
//            cout << "true" << endl;
//            gap = true;
//
//        }
//    //}
//         
//        
//}
void Display() {

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_street();
    draw_tiles();
    glPushMatrix();
    car_m.draw_car_m();
    glPopMatrix();

    glPushMatrix();
    crash_check();
    car_o.draw_car_o();
    car_o1.draw_car_o();
    car_o2.draw_car_o();
    //cout << car_o.y << "," << car_o1.y << "," << car_o2.y << endl;
   // randomlogic();
   /* car_o.y--;
    car_o1.y--;
    car_o2.y --;
     glPushMatrix();
    if (car_o.y <= -290) {
        glLoadIdentity();
        randomlogic();
        cout << car_o.y <<"car1"<< endl;
        glTranslatef(car_o.x, car1_movment, 0);
        glPopMatrix();
    }
        glPushMatrix();
    if (car_o1.y <= -290) {
        glLoadIdentity();
        randomlogic();
        cout << car_o1.y << "car2" << endl;
        glTranslatef(car_o1.x, car2_movment, 0);
        glPopMatrix();

    }

        glPushMatrix();
    if (car_o2.y <= -290) {
        glLoadIdentity();
        randomlogic();
        cout << car_o2.y << "car3" << endl;
        glTranslatef(car_o2.x, car3_movment, 0);
        glPopMatrix();
    }*/
    glPopMatrix();

    glutSwapBuffers();
}



