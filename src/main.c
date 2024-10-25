#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>

#include "constants.h"
#include "structures.h"
#include "keyboard.h"
#include "draw.h"
#include "init.h"

struct Player player;
struct Boss boss;
struct Bullet bullet;
struct Bullet boss_bullet;
struct Heart heart;
struct Menu main_menu;
struct Asteroid small_asteroid;
struct Asteroid medium_asteroid;
struct Asteroid big_asteroid;

bool changed_to_second = false;
bool changed_to_third = false;
bool changed_to_fourth = false;
bool player_is_dead = false;
bool boss_is_dead = false;

GLuint textures[TEXTURES_AMT+1] = { 0 };

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-WINDOW_WIDTH)/2,
                            (glutGet(GLUT_SCREEN_HEIGHT)-WINDOW_HEIGHT)/2);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(WINDOW_CAPTION);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    main_menu_init();
    glutDisplayFunc(draw_main_menu);
    glutKeyboardFunc(handle_menu_keyboard);
    glutSpecialFunc(handle_menu_special_keyboard);

    PlaySound("..//..//sounds//menu.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    glutMainLoop();
    
    return 0;
}