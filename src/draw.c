#include <GL/glut.h>
#include <stdio.h>

#include "constants.h"
#include "extern_pointers.h"

void draw_rectangle(int x, int y, int width, int height, int texture_id) {
    glBindTexture(GL_TEXTURE_2D, textures[texture_id]);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void draw_text(int x, int y, char* string) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; string[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}

void draw_main_menu() {
    glClear(GL_COLOR_BUFFER_BIT);

    //draw main menu
    glColor3f(1.0, 1.0, 1.0);
    if (main_menu.option == 1) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 11);
    } else if (main_menu.option == 0) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 12);
    }

    glutSwapBuffers();
}

void draw_scene() {
    glClear(GL_COLOR_BUFFER_BIT);

    //draw background
    if (player.playerLives == 3) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 9);
    } else if (player.playerLives == 2) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 8);
    } else if (player.playerLives == 1) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 7);
    }

    if (player.playerLives == 0) {
        //draw background
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 10);

        char game_over[DRAW_TEXT_LENGHT];
        sprintf(game_over, "Game over!");
        draw_text((WINDOW_WIDTH / 2) - 50, WINDOW_HEIGHT / 2, game_over);
        
        char score[DRAW_TEXT_LENGHT];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text((WINDOW_WIDTH / 2) - 45, WINDOW_HEIGHT / 2 - 40, score);
        
        char level[DRAW_TEXT_LENGHT];
        sprintf(level, "Level: %d", player.currentLevel);
        draw_text((WINDOW_WIDTH / 2) - 40, WINDOW_HEIGHT / 2 - 60, level);
        
        char closing[DRAW_TEXT_LENGHT];
        sprintf(closing, "To close game press ESC");
        draw_text((WINDOW_WIDTH / 2) - 120, WINDOW_HEIGHT / 2 - 80, closing);

    } else if (boss.bossLives == 0) {
        //draw background
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 10);

        char game_end[DRAW_TEXT_LENGHT];
        sprintf(game_end, "You won!");
        draw_text((WINDOW_WIDTH / 2) - 50, WINDOW_HEIGHT / 2, game_end);
        
        char score[DRAW_TEXT_LENGHT];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text((WINDOW_WIDTH / 2) - 45, WINDOW_HEIGHT / 2 - 40, score);
        
        char level[DRAW_TEXT_LENGHT];
        sprintf(level, "Level: %d", player.currentLevel);
        draw_text((WINDOW_WIDTH / 2) - 40, WINDOW_HEIGHT / 2 - 60, level);
        
        char closing[DRAW_TEXT_LENGHT];
        sprintf(closing, "To close game press ESC");
        draw_text((WINDOW_WIDTH / 2) - 120, WINDOW_HEIGHT / 2 - 80, closing);
        
    } else if (player.currentLevel == 4) {
        //draw player
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize, 0);

        //draw player_bullet
        draw_rectangle(bullet.bulletX, bullet.bulletY, bullet.bulletSize, bullet.bulletSize, 1);

        //draw boss
        draw_rectangle(boss.bossX, boss.bossY, boss.bossSize, boss.bossSize, 6);

        //...

        //draw boss_bullet
        draw_rectangle(boss_bullet.bulletX, boss_bullet.bulletY, boss_bullet.bulletSize, boss_bullet.bulletSize, 2);

        //draw level
        char level[DRAW_TEXT_LENGHT];
        sprintf(level, "Level: Boss");
        draw_text(10, WINDOW_HEIGHT - 30, level);

        //draw boss_lives
        char boss_lives[DRAW_TEXT_LENGHT];
        sprintf(boss_lives, "Boss lives: %d", boss.bossLives);
        draw_text(10, WINDOW_HEIGHT - 50, boss_lives);

    } else {
        //draw player
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize, 0);

        //draw heart
        draw_rectangle(heart.heartX, heart.heartY, heart.heartSize, heart.heartSize, 13);
        
        //draw bullet
        draw_rectangle(bullet.bulletX, bullet.bulletY, bullet.bulletSize, bullet.bulletSize, 1);
        
        //draw small_asteroid
        draw_rectangle(small_asteroid.asteroidX, small_asteroid.asteroidY, small_asteroid.asteroidSize, small_asteroid.asteroidSize, 3);

        //draw medium_asteroid
        draw_rectangle(medium_asteroid.asteroidX, medium_asteroid.asteroidY, medium_asteroid.asteroidSize, medium_asteroid.asteroidSize, 4);
        
        //draw big_asteroid
        draw_rectangle(big_asteroid.asteroidX, big_asteroid.asteroidY, big_asteroid.asteroidSize, big_asteroid.asteroidSize, 5);
        
        //draw level
        char level[DRAW_TEXT_LENGHT];
        sprintf(level, "Level: %d", player.currentLevel);
        draw_text(10, WINDOW_HEIGHT - 30, level);

        //draw score
        char score[DRAW_TEXT_LENGHT];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text(10, WINDOW_HEIGHT - 50, score);
    }

    glutSwapBuffers();
}