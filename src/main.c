#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>

#include "constants.h"
#include "structures.h"
#include "lists.h"
#include "keyboard.h"
#include "draw.h"
#include "init.h"

struct Player player;
struct Boss boss;
struct Heart heart;
struct Menu main_menu;

bool changed_to_second = false;
bool changed_to_third = false;
bool changed_to_fourth = false;
bool player_is_dead = false;
bool boss_is_dead = false;
bool megalovania_is_playing = false;

int boss_delay = 0;

bool spawn_asteroids = true;

GLuint textures[TEXTURES_AMT+1] = { 0 };

struct Bullet_list *bullets;
struct Bullet_list *boss_bullets;
struct Asteroid_list *small_asteroids;
struct Asteroid_list *medium_asteroids;
struct Asteroid_list *big_asteroids;

int update_count;

int frameCountPerSecond; 
int frameCount;         
double previousTime;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-WINDOW_WIDTH)/2,
                            (glutGet(GLUT_SCREEN_HEIGHT)-WINDOW_HEIGHT)/2);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(WINDOW_CAPTION);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    bullets = init_bullet_list_elem();
    boss_bullets = init_bullet_list_elem();
    small_asteroids = init_asteroid_list_elem('s');
    medium_asteroids = init_asteroid_list_elem('m');
    big_asteroids = init_asteroid_list_elem('b');

    main_menu_init();
    glutDisplayFunc(draw_main_menu);
    glutKeyboardFunc(handle_menu_keyboard);
    glutSpecialFunc(handle_menu_special_keyboard);

    if (!megalovania_is_playing) {
        PlaySound("..//..//sounds//menu.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    
    glutMainLoop();
    
    return 0;
}