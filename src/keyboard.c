#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

#include "constants.h"
#include "extern_pointers.h"
#include "update.h"
#include "draw.h"
#include "init.h"

void handle_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 32: //SPACE
            if (player.playerLives > 0) {
                add_bullet(bullets);
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//shot.wav", NULL, SND_FILENAME | SND_ASYNC);
                }
            }
            break;
        case 27: //ESC
            PlaySound("..//..//sounds//exit.wav", NULL, SND_FILENAME | SND_ASYNC);
            sleep(1);
            exit(0);
            break;
        case 97: //a
            megalovania_is_playing = true;
            player.godMode = true;
            player.playerScore = -9999;
            PlaySound("..//..//sounds//megalovania.wav", NULL, SND_FILENAME | SND_ASYNC);

            for (int amt = 0; amt < MAX_ASTEROIDS_IN_BENCH_MODE/3; amt++) {
                add_asteroid(small_asteroids);
                add_asteroid(medium_asteroids);
                add_asteroid(big_asteroids);
            }

            break;
        case 105: //i
            //TODO infinity mode)))
            break;
    }
}

void handle_movement_keys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_DOWN:
            player.playerY -= 10;
            if (player.playerY < BORDERS_SIZE) {
                player.playerY = BORDERS_SIZE;
            }
            break;
        case GLUT_KEY_UP:
            player.playerY += 10;
            if (player.playerY + player.playerSize + BORDERS_SIZE > WINDOW_HEIGHT) {
                player.playerY = WINDOW_HEIGHT - player.playerSize - BORDERS_SIZE;
            }
            break;
        case GLUT_KEY_RIGHT:
            player.playerX += 10;
            if (player.playerX > player.playerSize + 200) {
                player.playerX = player.playerSize + 200;
            }
            break;
        case GLUT_KEY_LEFT:
            player.playerX -= 10;
            if (player.playerX < player.playerSize) {
                player.playerX = player.playerSize;
            }
            break;
    }
}

void handle_menu_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //ESC
            PlaySound("..//..//sounds//exit.wav", NULL, SND_FILENAME | SND_ASYNC);
            sleep(1);
            exit(0);
            break;
        case 13: //ENTER
            if (main_menu.option == 1) {
                printf("Player started the game, initializing rest of things...\n");
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//start.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                init_game();
                glutDisplayFunc(draw_scene);
                glutKeyboardFunc(handle_keyboard);
                glutSpecialFunc(handle_movement_keys);
                glutTimerFunc(25, update, 0);
                break;
            } else if (main_menu.option == 0) {
                PlaySound("..//..//sounds//exit.wav", NULL, SND_FILENAME | SND_ASYNC);
                sleep(1);
                exit(0);
                break;
            }
    }
}

void handle_menu_special_keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_DOWN:
            // PlaySound("..//..//sounds//select.wav", NULL, SND_FILENAME | SND_ASYNC);
            main_menu.option = 0;
            break;
        case GLUT_KEY_UP:
            // PlaySound("..//..//sounds//select.wav", NULL, SND_FILENAME | SND_ASYNC);
            main_menu.option = 1;
            break;
    }

    glutPostRedisplay();
}