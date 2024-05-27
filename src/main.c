#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define DRAW_TEXT_LENGHT 15
#define WINDOW_CAPTION "Space Impact - 5131001/30002"

#define PT_FILENAME "../../themes/player.bmp"
#define BT_FILENAME "../../themes/bullet.bmp"
#define BBT_FILENAME "../../themes/boss_bullet.bmp"
#define SAT_FILENAME "../../themes/small_asteroid.bmp"
#define MAT_FILENAME "../../themes/medium_asteroid.bmp"
#define BAT_FILENAME "../../themes/big_asteroid.bmp"
#define BOSST_FILENAME "../../themes/boss.bmp"

struct Player {
    int currentLevel;
    int playerSize;
    int playerY;
    int playerX;
    int playerLives;
    int playerScore;
} player;

struct Boss {
    int bossSize;
    int bossY;
    int bossX;
    int bossLives;
    bool reached_top;
    bool reached_bot;
} boss;

struct Bullet {
    int bulletSize;
    int bulletX;
    int bulletY;
    int bulletSpeed;
} bullet, boss_bullet;

struct Asteroid {
    bool spawn;
    int asteroidSize;
    int asteroidY;
    int asteroidX;
    int asteroidSpeed;
} small_asteroid, medium_asteroid, big_asteroid;

GLuint textures[7] = { 0 }; 

void draw_rectangle(int x, int y, int width, int height, int texture_id) {
    glBindTexture(GL_TEXTURE_2D, textures[texture_id]);
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
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

void draw_scene() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (player.playerLives == 0) {
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT);
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
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT);

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
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize, 0);

        //draw player_bullet
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(bullet.bulletX, bullet.bulletY, bullet.bulletSize, bullet.bulletSize, 1);

        //draw boss
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(boss.bossX, boss.bossY, boss.bossSize, boss.bossSize, 6);

        //draw boss_bullet
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(boss_bullet.bulletX, boss_bullet.bulletY, boss_bullet.bulletSize, boss_bullet.bulletSize, 2);

        //draw level
        char level[DRAW_TEXT_LENGHT];
        sprintf(level, "Level: Boss");
        draw_text(10, WINDOW_HEIGHT - 20, level);

        //draw lives
        char lives[DRAW_TEXT_LENGHT];
        sprintf(lives, "Your lives: %d", player.playerLives);
        draw_text(10, WINDOW_HEIGHT - 40, lives);

        //draw boss_lives
        char boss_lives[DRAW_TEXT_LENGHT];
        sprintf(boss_lives, "Boss lives: %d", boss.bossLives);
        draw_text(WINDOW_WIDTH - 150, WINDOW_HEIGHT - 20, boss_lives);

    } else {
        //draw player
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize, 0);
        
        //draw bullet
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(bullet.bulletX, bullet.bulletY, bullet.bulletSize, bullet.bulletSize, 1);
        
        //draw small_asteroid
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(small_asteroid.asteroidX, small_asteroid.asteroidY, small_asteroid.asteroidSize, small_asteroid.asteroidSize, 3);

        //draw medium_asteroid
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(medium_asteroid.asteroidX, medium_asteroid.asteroidY, medium_asteroid.asteroidSize, medium_asteroid.asteroidSize, 4);
        
        //draw big_asteroid
        glColor3f(1.0, 1.0, 1.0);
        draw_rectangle(big_asteroid.asteroidX, big_asteroid.asteroidY, big_asteroid.asteroidSize, big_asteroid.asteroidSize, 5);
        
        //draw level
        char level[DRAW_TEXT_LENGHT];
        sprintf(level, "Level: %d", player.currentLevel);
        draw_text(10, WINDOW_HEIGHT - 20, level);

        //draw score
        char score[DRAW_TEXT_LENGHT];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text(10, WINDOW_HEIGHT - 40, score);

        //draw lives
        char lives[DRAW_TEXT_LENGHT];
        sprintf(lives, "Your lives: %d", player.playerLives);
        draw_text(10, WINDOW_HEIGHT - 60, lives);
    }

    glutSwapBuffers();
}

void update() {

    if (player.playerScore == 5) {
        player.currentLevel = 2;
        small_asteroid.asteroidSpeed = 6;
        medium_asteroid.asteroidSpeed = 5;
        big_asteroid.asteroidSpeed = 4;
    }

    if (player.playerScore == 10) {
        player.currentLevel = 3;
        small_asteroid.asteroidSpeed = 8;
        medium_asteroid.asteroidSpeed = 7;
        big_asteroid.asteroidSpeed = 6;
    }

    if (player.playerScore == 15) {
        player.currentLevel = 4;
        
        small_asteroid.spawn = false;
        medium_asteroid.spawn = false;
        big_asteroid.spawn = false;
    }

    //update player bullet position
    if (bullet.bulletX >= 0) {
        bullet.bulletX += bullet.bulletSpeed;
        if (bullet.bulletX >= WINDOW_WIDTH) {
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
        }
    }
    
    //!small_asteroid
    //update asteroid position
    if (small_asteroid.spawn == true && player.currentLevel != 4) {
        small_asteroid.asteroidX -= small_asteroid.asteroidSpeed;
        if (small_asteroid.asteroidX <= 0 && player.playerLives > 0) {
            small_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - small_asteroid.asteroidSize) - 70 + 1) + 70;
            small_asteroid.asteroidX = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }

        //check bullet-asteroid collision
        if (bullet.bulletY >= small_asteroid.asteroidY \
        && bullet.bulletY <= small_asteroid.asteroidY + small_asteroid.asteroidSize \
        && bullet.bulletX >= small_asteroid.asteroidX \
        && bullet.bulletX <= small_asteroid.asteroidX + small_asteroid.asteroidSize) {

            player.playerScore += 1;
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
            
            small_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - small_asteroid.asteroidSize) - 70 + 1) + 70;
            small_asteroid.asteroidX = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (small_asteroid.asteroidY >= player.playerY \
        && small_asteroid.asteroidY <= player.playerY + player.playerSize \
        && small_asteroid.asteroidX >= player.playerX \
        && small_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            small_asteroid.asteroidY = -small_asteroid.asteroidSize;
            small_asteroid.asteroidX = -small_asteroid.asteroidSize;
            
            small_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - small_asteroid.asteroidSize) - 70 + 1) + 70;
            small_asteroid.asteroidX = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }
    }


    //!medium_asteroid
    //update asteroid position
    if (medium_asteroid.spawn == true && player.currentLevel != 4) {
        medium_asteroid.asteroidX -= medium_asteroid.asteroidSpeed;
        if (medium_asteroid.asteroidX <= 0 && player.playerLives > 0) {
            medium_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - medium_asteroid.asteroidSize) - 70 + 1) + 70;
            medium_asteroid.asteroidX = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }
    

        //check bullet-asteroid collision
        if (bullet.bulletY >= medium_asteroid.asteroidY \
        && bullet.bulletY <= medium_asteroid.asteroidY + medium_asteroid.asteroidSize \
        && bullet.bulletX >= medium_asteroid.asteroidX \
        && bullet.bulletX <= medium_asteroid.asteroidX + medium_asteroid.asteroidSize) {

            player.playerScore += 1;
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
            
            medium_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - medium_asteroid.asteroidSize) - 70 + 1) + 70;
            medium_asteroid.asteroidX = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (medium_asteroid.asteroidY >= player.playerY \
        && medium_asteroid.asteroidY <= player.playerY + player.playerSize \
        && medium_asteroid.asteroidX >= player.playerX \
        && medium_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            medium_asteroid.asteroidY = -medium_asteroid.asteroidSize;
            medium_asteroid.asteroidX = -medium_asteroid.asteroidSize;
            
            medium_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - medium_asteroid.asteroidSize) - 70 + 1) + 70;
            medium_asteroid.asteroidX = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }
    }

    //!big_asteroid
    //update asteroid position
    if (big_asteroid.spawn == true && player.currentLevel != 4) {
        big_asteroid.asteroidX -= big_asteroid.asteroidSpeed;
        if (big_asteroid.asteroidX <= 0 && player.playerLives > 0) {
            big_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - big_asteroid.asteroidSize) - 70 + 1) + 70;
            big_asteroid.asteroidX = WINDOW_WIDTH - big_asteroid.asteroidSize;
        }

        //check bullet-asteroid collision
        if (bullet.bulletY >= big_asteroid.asteroidY \
        && bullet.bulletY <= big_asteroid.asteroidY + big_asteroid.asteroidSize \
        && bullet.bulletX >= big_asteroid.asteroidX \
        && bullet.bulletX <= big_asteroid.asteroidX + big_asteroid.asteroidSize) {

            player.playerScore += 1;
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
            
            big_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - big_asteroid.asteroidSize) - 70 + 1) + 70;
            big_asteroid.asteroidX = WINDOW_WIDTH - big_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (big_asteroid.asteroidY >= player.playerY \
        && big_asteroid.asteroidY <= player.playerY + player.playerSize \
        && big_asteroid.asteroidX >= player.playerX \
        && big_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            big_asteroid.asteroidY = -big_asteroid.asteroidSize;
            big_asteroid.asteroidX = -big_asteroid.asteroidSize;
            
            big_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - 70 - big_asteroid.asteroidSize) - 70 + 1) + 70;
            big_asteroid.asteroidX = WINDOW_WIDTH - big_asteroid.asteroidSize;
        }
    }

    //! update boss
    if (player.currentLevel == 4) {
        //boss movement
        if (boss.bossY >= boss.bossSize && boss.reached_top == true) {
            boss.bossY -= 3;

            if (boss.bossY < boss.bossSize) {
                boss.bossY = boss.bossSize;
                boss.reached_bot = true;
                boss.reached_top = false;
            }
        } 
        
        if (boss.bossY <= WINDOW_HEIGHT - boss.bossSize - 40 && boss.reached_bot == true) {
            boss.bossY += 3;

            if (boss.bossY > WINDOW_HEIGHT - boss.bossSize - 40) {
                boss.bossY = WINDOW_HEIGHT - boss.bossSize - 40;
                boss.reached_top = true;
                boss.reached_bot = false;
            }
        }

        //boss shooting
        if (boss_bullet.bulletX < 0) {
            boss_bullet.bulletY = boss.bossY + boss.bossSize / 2 - boss_bullet.bulletSize / 2;
            boss_bullet.bulletX = boss.bossX;
        }

        //update boss_bullet position
        if (boss_bullet.bulletX >= 0) {
            boss_bullet.bulletX -= boss_bullet.bulletSpeed;

            if (boss_bullet.bulletX <= 0) {
                boss_bullet.bulletY = -boss_bullet.bulletSize;
                boss_bullet.bulletX = -boss_bullet.bulletSize;
            }
        }

        //boss_bullet - player collision
        if (boss_bullet.bulletY >= player.playerY \
        && boss_bullet.bulletY <= player.playerY + player.playerSize \
        && boss_bullet.bulletX >= player.playerX \
        && boss_bullet.bulletX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            boss_bullet.bulletY = -boss_bullet.bulletSize;
            boss_bullet.bulletX = -boss_bullet.bulletSize;
        }

        //bullet - boss collision
        if (bullet.bulletY >= boss.bossY \
        && bullet.bulletY <= boss.bossY + boss.bossSize \
        && bullet.bulletX >= boss.bossX \
        && bullet.bulletX <= boss.bossX + boss.bossSize) {

            boss.bossLives -= 1;
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

void handle_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //ESC
            exit(0);
            break;
        case 32: //SPACE
            if (bullet.bulletX < 0 && player.playerLives > 0) {
                bullet.bulletY = player.playerY + player.playerSize / 2 - bullet.bulletSize / 2;
                bullet.bulletX = player.playerX;
            }
            break;
    }
}

void handle_movement_keys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_DOWN:
            player.playerY -= 10;
            if (player.playerY < 70) {
                player.playerY = 70;
            }
            break;
        case GLUT_KEY_UP:
            player.playerY += 10;
            if (player.playerY + player.playerSize + 70 > WINDOW_HEIGHT) {
                player.playerY = WINDOW_HEIGHT - player.playerSize - 70;
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

void init_game() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    //?player -> bullet -> boss_bullet, s_asteroid, m_asteroid, b_asteroid, boss
    glGenTextures(7, textures);

    //!player texture - start
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int pt_width = 0, pt_height = 0, pt_channels = 0;
    unsigned char *player_texture_img = stbi_load(PT_FILENAME, &pt_width, &pt_height, &pt_channels, 0);
    if(player_texture_img == NULL) {
        printf("error in loading player_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", PT_FILENAME, pt_width, pt_height, pt_channels);
    if (pt_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pt_width, pt_height, 0, GL_RGB, GL_UNSIGNED_BYTE, player_texture_img);
    } else if (pt_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pt_width, pt_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, player_texture_img);
    }
    stbi_image_free(player_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!player texture - end

    //!bullet texture - start
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int bt_width = 0, bt_height = 0, bt_channels = 0;
    unsigned char *bullet_texture_img = stbi_load(BT_FILENAME, &bt_width, &bt_height, &bt_channels, 0);
    if(bullet_texture_img == NULL) {
        printf("error in loading bullet_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BT_FILENAME, bt_width, bt_height, bt_channels);
    if (bt_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bt_width, bt_height, 0, GL_RGB, GL_UNSIGNED_BYTE, bullet_texture_img);
    } else if (bt_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bt_width, bt_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bullet_texture_img);
    }
    stbi_image_free(bullet_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!bullet texture - end

    //!boss_bullet texture - start
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int bbt_width = 0, bbt_height = 0, bbt_channels = 0;
    unsigned char *boss_bullet_texture_img = stbi_load(BBT_FILENAME, &bbt_width, &bbt_height, &bbt_channels, 0);
    if(boss_bullet_texture_img == NULL) {
        printf("error in loading boss_bullet_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BBT_FILENAME, bbt_width, bbt_height, bbt_channels);
    if (bbt_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bbt_width, bbt_height, 0, GL_RGB, GL_UNSIGNED_BYTE, boss_bullet_texture_img);
    } else if (bbt_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bbt_width, bbt_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, boss_bullet_texture_img);
    }
    stbi_image_free(boss_bullet_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!boss_bullet texture - end

    //!small_asteroid_texture - start
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int sat_width = 0, sat_height = 0, sat_channels = 0;
    unsigned char *small_asteroid_texture_img = stbi_load(SAT_FILENAME, &sat_width, &sat_height, &sat_channels, 0);  
    if(small_asteroid_texture_img == NULL) {
        printf("error in loading small_asteroid_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", SAT_FILENAME, sat_width, sat_height, sat_channels);
    if (sat_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sat_width, sat_height, 0, GL_RGB, GL_UNSIGNED_BYTE, small_asteroid_texture_img);
    } else if (sat_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sat_width, sat_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, small_asteroid_texture_img);
    }
    stbi_image_free(small_asteroid_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!small_asteroid_texture - end

    //!medium_asteroid_texture - start
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int mat_width = 0, mat_height = 0, mat_channels = 0;
    unsigned char *medium_asteroid_texture_img = stbi_load(MAT_FILENAME, &mat_width, &mat_height, &mat_channels, 0);
    if(medium_asteroid_texture_img == NULL) {
        printf("error in loading medium_asteroid_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", MAT_FILENAME, mat_width, mat_height, mat_channels);
    if (mat_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mat_width, mat_height, 0, GL_RGB, GL_UNSIGNED_BYTE, medium_asteroid_texture_img);
    } else if (mat_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mat_width, mat_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, medium_asteroid_texture_img);
    }
    stbi_image_free(medium_asteroid_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!medium_asteroid_texture - start

    //!big_asteroid_texture - start
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int bat_width = 0, bat_height = 0, bat_channels = 0;
    unsigned char *big_asteroid_texture_img = stbi_load(BAT_FILENAME, &bat_width, &bat_height, &bat_channels, 0);
    if(big_asteroid_texture_img == NULL) {
        printf("error in loading big_asteroid_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BAT_FILENAME, bat_width, bat_height, bat_channels);
    if (bat_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bat_width, bat_height, 0, GL_RGB, GL_UNSIGNED_BYTE, big_asteroid_texture_img);
    } else if (bat_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bat_width, bat_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, big_asteroid_texture_img);
    }
    stbi_image_free(big_asteroid_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!big_asteroid_texture - end

    //!boss_texture - start
    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int bosst_width = 0, bosst_height = 0, bosst_channels = 0;
    unsigned char *boss_texture_img = stbi_load(BOSST_FILENAME, &bosst_width, &bosst_height, &bosst_channels, 0);
    if(boss_texture_img == NULL) {
        printf("error in loading boss_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BOSST_FILENAME, bosst_width, bosst_height, bosst_channels);
    if (bosst_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bosst_width, bosst_height, 0, GL_RGB, GL_UNSIGNED_BYTE, boss_texture_img);
    } else if (bosst_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bosst_width, bosst_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, boss_texture_img);
    }
    stbi_image_free(boss_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!boss_texture - end


    //!objects initialization
    player.currentLevel = 1;
    player.playerSize = 50;
    player.playerY = WINDOW_HEIGHT / 2;
    player.playerX = player.playerSize;
    player.playerScore = 0;
    player.playerLives = 3;

    boss.bossLives = 3;
    boss.bossSize = 70;
    boss.bossY = WINDOW_HEIGHT / 2;
    boss.bossX = WINDOW_WIDTH - boss.bossSize * 2;

    boss_bullet.bulletSize = 25;
    boss_bullet.bulletSpeed = 10;
    boss_bullet.bulletX = -boss_bullet.bulletSize;
    boss_bullet.bulletY = -boss_bullet.bulletSize;
    boss.reached_top = true;
    boss.reached_bot = false;

    bullet.bulletSize = 10;
    bullet.bulletSpeed = 5;
    bullet.bulletX = -bullet.bulletSize;
    bullet.bulletY = -bullet.bulletSize;

    small_asteroid.asteroidSize = 30;
    small_asteroid.spawn = true;
    small_asteroid.asteroidSpeed = 4;
    small_asteroid.asteroidY = -small_asteroid.asteroidSize;
    small_asteroid.asteroidX = WINDOW_WIDTH - small_asteroid.asteroidSize;

    medium_asteroid.asteroidSize = 40;
    medium_asteroid.spawn = true;
    medium_asteroid.asteroidSpeed = 3;
    medium_asteroid.asteroidY = -medium_asteroid.asteroidSize;
    medium_asteroid.asteroidX = WINDOW_WIDTH - medium_asteroid.asteroidSize;

    big_asteroid.asteroidSize = 50;
    big_asteroid.spawn = true;
    big_asteroid.asteroidSpeed = 2;
    big_asteroid.asteroidY = -big_asteroid.asteroidSize;
    big_asteroid.asteroidX = WINDOW_WIDTH - big_asteroid.asteroidSize;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutCreateWindow(WINDOW_CAPTION);
    
    init_game();

    //TODO add main menu with 1 button -> change all funcs from menu to game

    glutDisplayFunc(draw_scene);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_movement_keys);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    
    return 0;
}