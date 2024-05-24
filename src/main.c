#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define DRAW_TEXT_LENGHT 15
#define WINDOW_CAPTION "Space Impact - 5131001/30002"

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

void draw_rectangle(int x, int y, int width, int height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
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
        glColor3f(0.0, 1.0, 0.0);
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize);

        //draw player_bullet
        glColor3f(1.0, 1.0, 0.0);
        draw_rectangle(bullet.bulletX, bullet.bulletY, bullet.bulletSize, bullet.bulletSize);

        //draw boss
        glColor3f(1.0, 0.0, 0.0);
        draw_rectangle(boss.bossX, boss.bossY, boss.bossSize, boss.bossSize);

        //draw boss_bullet
        glColor3f(1.0, 0.0, 0.0);
        draw_rectangle(boss_bullet.bulletX, boss_bullet.bulletY, boss_bullet.bulletSize, boss_bullet.bulletSize);

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
        glColor3f(0.0, 1.0, 0.0);
        draw_rectangle(player.playerX - player.playerSize / 2, player.playerY, player.playerSize, player.playerSize);
        
        //draw bullet
        glColor3f(1.0, 1.0, 0.0);
        draw_rectangle(bullet.bulletX, bullet.bulletY, bullet.bulletSize, bullet.bulletSize);
        
        //draw small_asteroid
        glColor3f(1.0, 0.0, 0.0);
        draw_rectangle(small_asteroid.asteroidX, small_asteroid.asteroidY, small_asteroid.asteroidSize, small_asteroid.asteroidSize);

        //draw medium_asteroid
        glColor3f(1.0, 0.0, 0.0);
        draw_rectangle(medium_asteroid.asteroidX, medium_asteroid.asteroidY, medium_asteroid.asteroidSize, medium_asteroid.asteroidSize);
        
        //draw big_asteroid
        glColor3f(1.0, 0.0, 0.0);
        draw_rectangle(big_asteroid.asteroidX, big_asteroid.asteroidY, big_asteroid.asteroidSize, big_asteroid.asteroidSize);
        
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
            small_asteroid.asteroidY = rand() % (WINDOW_HEIGHT - small_asteroid.asteroidSize - 250);
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
            
            small_asteroid.asteroidX = rand() % (WINDOW_HEIGHT - small_asteroid.asteroidSize);
            small_asteroid.asteroidY = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (small_asteroid.asteroidY >= player.playerY \
        && small_asteroid.asteroidY <= player.playerY + player.playerSize \
        && small_asteroid.asteroidX >= player.playerX \
        && small_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            small_asteroid.asteroidY = -small_asteroid.asteroidSize;
            small_asteroid.asteroidX = -small_asteroid.asteroidSize;
            
            small_asteroid.asteroidX = rand() % (WINDOW_HEIGHT - small_asteroid.asteroidSize);
            small_asteroid.asteroidY = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }
    }


    //!medium_asteroid
    //update asteroid position
    if (medium_asteroid.spawn == true && player.currentLevel != 4) {
        medium_asteroid.asteroidX -= medium_asteroid.asteroidSpeed;
        if (medium_asteroid.asteroidX <= 0 && player.playerLives > 0) {
            medium_asteroid.asteroidY = rand() % (WINDOW_HEIGHT - medium_asteroid.asteroidSize - 250);
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
            
            medium_asteroid.asteroidX = rand() % (WINDOW_HEIGHT - medium_asteroid.asteroidSize);
            medium_asteroid.asteroidY = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (medium_asteroid.asteroidY >= player.playerY \
        && medium_asteroid.asteroidY <= player.playerY + player.playerSize \
        && medium_asteroid.asteroidX >= player.playerX \
        && medium_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            medium_asteroid.asteroidY = -medium_asteroid.asteroidSize;
            medium_asteroid.asteroidX = -medium_asteroid.asteroidSize;
            
            medium_asteroid.asteroidX = rand() % (WINDOW_HEIGHT - medium_asteroid.asteroidSize);
            medium_asteroid.asteroidY = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }
    }

    //!big_asteroid
    //update asteroid position
    if (big_asteroid.spawn == true && player.currentLevel != 4) {
        big_asteroid.asteroidX -= big_asteroid.asteroidSpeed;
        if (big_asteroid.asteroidX <= 0 && player.playerLives > 0) {
            big_asteroid.asteroidY = rand() % (WINDOW_HEIGHT - big_asteroid.asteroidSize - 250);
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
            
            big_asteroid.asteroidX = rand() % (WINDOW_HEIGHT - big_asteroid.asteroidSize);
            big_asteroid.asteroidY = WINDOW_WIDTH - big_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (big_asteroid.asteroidY >= player.playerY \
        && big_asteroid.asteroidY <= player.playerY + player.playerSize \
        && big_asteroid.asteroidX >= player.playerX \
        && big_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            big_asteroid.asteroidY = -big_asteroid.asteroidSize;
            big_asteroid.asteroidX = -big_asteroid.asteroidSize;
            
            big_asteroid.asteroidX = rand() % (WINDOW_HEIGHT - big_asteroid.asteroidSize);
            big_asteroid.asteroidY = WINDOW_WIDTH - big_asteroid.asteroidSize;
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
            if (player.playerY < 0) {
                player.playerY = 0;
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
}

int main(int argc, char** argv) {

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
    bullet.bulletSpeed = 20;
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

    glutInit(&argc, argv);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutCreateWindow(WINDOW_CAPTION);
    
    init_game();

    glutDisplayFunc(draw_scene);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_movement_keys);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    
    return 0;
}