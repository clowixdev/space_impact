#include <GL/glut.h>
#include <stdio.h>

#include "constants.h"
#include "extern_pointers.h"
#include "update.h"

 static int last_texture_id = -1;


void frame_counter () {
    frameCount++;
    double currentTime = (double)glutGet(GLUT_ELAPSED_TIME) / 1000.0; 
    if (currentTime - previousTime >= 1.0) { //per sec
        frameCountPerSecond = frameCount;
        frameCount = 0;
        previousTime = currentTime;
    }
}

void draw_rectangle(int x, int y, int width, int height, int texture_id) {
    if (texture_id != last_texture_id) {
        glBindTexture(GL_TEXTURE_2D, textures[texture_id]);
        last_texture_id = texture_id;
    }


    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glEnd();

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

    glEnable(GL_TEXTURE_2D);

    //draw main menu
    glColor3f(1.0, 1.0, 1.0);
    if (main_menu.option == 1) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 11);
    } else if (main_menu.option == 0) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 12);
    }
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void draw_scene() {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    //draw background
    if (player.playerLives == 3) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 9);
    } else if (player.playerLives == 2) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 8);
    } else if (player.playerLives == 1) {
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 7);
    }
    glDisable(GL_TEXTURE_2D);

    if (player.playerLives == 0) {
        glEnable(GL_TEXTURE_2D);
        //draw background
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 10);

        glDisable(GL_TEXTURE_2D);

        char game_over[DRAW_TEXT_LENGTH];
        sprintf(game_over, "Game over!");
        draw_text((WINDOW_WIDTH / 2) - 50, WINDOW_HEIGHT / 2, game_over);
        
        char score[DRAW_TEXT_LENGTH];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text((WINDOW_WIDTH / 2) - 45, WINDOW_HEIGHT / 2 - 40, score);
        
        char level[DRAW_TEXT_LENGTH];
        sprintf(level, "Level: %d", player.currentLevel);
        draw_text((WINDOW_WIDTH / 2) - 40, WINDOW_HEIGHT / 2 - 60, level);
        
        char closing[DRAW_TEXT_LENGTH];
        sprintf(closing, "To close game press ESC");
        draw_text((WINDOW_WIDTH / 2) - 120, WINDOW_HEIGHT / 2 - 80, closing);

    } else if (boss.bossLives == 0) {
        glEnable(GL_TEXTURE_2D);
        //draw background
        draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 10);

        glDisable(GL_TEXTURE_2D);
        char game_end[DRAW_TEXT_LENGTH];
        sprintf(game_end, "You won!");
        draw_text((WINDOW_WIDTH / 2) - 50, WINDOW_HEIGHT / 2, game_end);
        
        char score[DRAW_TEXT_LENGTH];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text((WINDOW_WIDTH / 2) - 45, WINDOW_HEIGHT / 2 - 40, score);
        
        char level[DRAW_TEXT_LENGTH];
        sprintf(level, "Level: %d", player.currentLevel);
        draw_text((WINDOW_WIDTH / 2) - 40, WINDOW_HEIGHT / 2 - 60, level);
        
        char closing[DRAW_TEXT_LENGTH];
        sprintf(closing, "To close game press ESC");
        draw_text((WINDOW_WIDTH / 2) - 120, WINDOW_HEIGHT / 2 - 80, closing);
        
    } else if (player.currentLevel == 4) {
        glEnable(GL_TEXTURE_2D);

        //draw player
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize, 0);

        //draw player_bullet
        for (int i=0; i < LINE_COUNT; i++){
            struct Bullet_list *bullet_elem = bullet_array[i];
            while (bullet_elem != NULL) {
                if (is_bullet_on_screen(bullet_elem->bullet)) {
                    if (!bullet_elem->bullet->between || (bullet_elem->bullet->between && i % 2 == 0)){
                    draw_rectangle(bullet_elem->bullet->bulletX, bullet_elem->bullet->bulletY, bullet_elem->bullet->bulletSize, bullet_elem->bullet->bulletSize, 1);
                    }
                }
                bullet_elem = bullet_elem->next;
            }
        }

        //draw boss
        draw_rectangle(boss.bossX, boss.bossY, boss.bossSize, boss.bossSize, 6);

        //...

        //draw boss_bullet
        /*//!!!!
        for (int i=0; i < LINE_COUNT; i++){
            struct Bullet_list *boss_bullet_elem = boss_bullet_array[i];
            while (boss_bullet_elem != NULL) {
                if (is_bullet_on_screen(boss_bullet_elem->bullet)) {
                    draw_rectangle(boss_bullet_elem->bullet->bulletX, boss_bullet_elem->bullet->bulletY, boss_bullet_elem->bullet->bulletSize, boss_bullet_elem->bullet->bulletSize, 2);
                }
                boss_bullet_elem = boss_bullet_elem->next;
            }
        }*/
        
        glDisable(GL_TEXTURE_2D);

        //draw level
        char level[DRAW_TEXT_LENGTH];
        sprintf(level, "Level: Boss");
        draw_text(10, WINDOW_HEIGHT - 30, level);

        //draw boss_lives
        char boss_lives[DRAW_TEXT_LENGTH];
        sprintf(boss_lives, "Boss lives: %d", boss.bossLives);
        draw_text(10, WINDOW_HEIGHT - 50, boss_lives);

    } else {
        glEnable(GL_TEXTURE_2D);

        //draw player
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize, 0);

        //draw heart
        draw_rectangle(heart.heartX, heart.heartY, heart.heartSize, heart.heartSize, 13);
        
        //draw bullet
       for (int i=0; i < LINE_COUNT; i++){
            struct Bullet_list *bullet_elem = bullet_array[i];
            while (bullet_elem != NULL) {
                if (is_bullet_on_screen(bullet_elem->bullet)) {
                    if (!bullet_elem->bullet->between){
                    draw_rectangle(bullet_elem->bullet->bulletX, bullet_elem->bullet->bulletY, bullet_elem->bullet->bulletSize, bullet_elem->bullet->bulletSize, 1);
                    }
                    else if (i % 2 == 0){
                        draw_rectangle(bullet_elem->bullet->bulletX, bullet_elem->bullet->bulletY, bullet_elem->bullet->bulletSize, bullet_elem->bullet->bulletSize, 1);
                    }
                }
                
                bullet_elem = bullet_elem->next;
            }
        }
        
        //draw small_asteroid
        for (int i=0; i < LINE_COUNT; i++){
            struct Asteroid_list *sa_elem = small_asteroids_array[i]->next;
            while (sa_elem != NULL) {
                if (is_asteroid_on_screen(sa_elem->asteroid)) {
                    draw_rectangle(sa_elem->asteroid->asteroidX, sa_elem->asteroid->asteroidY, sa_elem->asteroid->asteroidSize, sa_elem->asteroid->asteroidSize, 3);
                }
                sa_elem = sa_elem->next;
            }
        }

        //draw medium_asteroid
        for (int i=0; i < LINE_COUNT; i++){
            struct Asteroid_list *ma_elem = medium_asteroids_array[i]->next;
            while (ma_elem != NULL) {
                if (is_asteroid_on_screen(ma_elem->asteroid)) {
                    draw_rectangle(ma_elem->asteroid->asteroidX, ma_elem->asteroid->asteroidY, ma_elem->asteroid->asteroidSize, ma_elem->asteroid->asteroidSize, 4);
                }
                ma_elem = ma_elem->next;
            }
        }

        //draw big_asteroid
        for (int i=0; i < LINE_COUNT; i++){
                struct Asteroid_list *ba_elem = big_asteroids_array[i]->next;
                while (ba_elem != NULL) {
                    if (is_asteroid_on_screen(ba_elem->asteroid)) {
                        draw_rectangle(ba_elem->asteroid->asteroidX, ba_elem->asteroid->asteroidY, ba_elem->asteroid->asteroidSize, ba_elem->asteroid->asteroidSize, 5);
                    }
                    ba_elem = ba_elem->next;
                }
        }

        glDisable(GL_TEXTURE_2D);
        
        //draw level
        char level[DRAW_TEXT_LENGTH];
        sprintf(level, "Level: %d", player.currentLevel);
        draw_text(10, WINDOW_HEIGHT - 30, level);
        
        //draw score
        char score[DRAW_TEXT_LENGTH];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text(10, WINDOW_HEIGHT - 50, score);

        //draw fps
        char fps[DRAW_TEXT_LENGTH];
        sprintf(fps, "fps: %d", frameCountPerSecond);
        draw_text(10, 30, fps);
        
    }

    
    frame_counter();

    glutSwapBuffers();
}