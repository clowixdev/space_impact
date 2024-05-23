#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define PLAYER_SIZE    50
#define BULLET_SIZE    10
#define ASTEROID_SIZE  30
#define WINDOW_CAPTION "Space Impact - 5131001/30002"

struct Player {
    int playerY;
    int playerX;
    int playerLives;
    int playerScore;
} player;

struct Bullet {
    int bulletX;
    int bulletY;
} bullet;

struct Asteroid {
    int asteroidY;
    int asteroidX;
} asteroid;

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
        char game_over[15];
        sprintf(game_over, "Game over!");
        draw_text((WINDOW_WIDTH / 2) - 50, WINDOW_HEIGHT / 2, game_over);
        
        char score[15];
        sprintf(score, "Score: %d", player.playerScore);
        draw_text((WINDOW_WIDTH / 2) - 40, WINDOW_HEIGHT / 2 - 40, score);
        
        char closing[15];
        sprintf(closing, "Game will close in 5 seconds");
        draw_text((WINDOW_WIDTH / 2) - 120, WINDOW_HEIGHT / 2 - 60, closing);
        
        glutSwapBuffers();
        sleep(5);
        exit(0);
    }
    
    //draw player
    glColor3f(0.0, 1.0, 0.0);
    draw_rectangle(player.playerX - PLAYER_SIZE / 2, player.playerY, PLAYER_SIZE, PLAYER_SIZE);
    
    //draw bullet
    if (bullet.bulletY >= 0) {
        glColor3f(1.0, 1.0, 0.0);
        draw_rectangle(bullet.bulletX, bullet.bulletY, BULLET_SIZE, BULLET_SIZE);
    }
    
    //draw asteroid
    glColor3f(1.0, 0.0, 0.0);
    draw_rectangle(asteroid.asteroidX, asteroid.asteroidY, ASTEROID_SIZE, ASTEROID_SIZE);
    
    //draw score
    char score[11];
    sprintf(score, "Score: %d", player.playerScore);
    draw_text(10, WINDOW_HEIGHT - 20, score);

    //draw lives
    char lives[11];
    sprintf(lives, "Lives: %d", player.playerLives);
    draw_text(10, WINDOW_HEIGHT - 40, lives);
    
    glutSwapBuffers();
}

void update(int value) {
    //update bullet position
    if (bullet.bulletX >= 0) {
        bullet.bulletX += 15;
        if (bullet.bulletX >= WINDOW_WIDTH) {
            bullet.bulletY = -BULLET_SIZE;
            bullet.bulletX = -BULLET_SIZE;
        }
    }
    
    //update asteroid position
    asteroid.asteroidX -= 8;
    if (asteroid.asteroidX <= 0 && player.playerLives > 0) {
        asteroid.asteroidY = rand() % (WINDOW_HEIGHT - ASTEROID_SIZE - 150);
        asteroid.asteroidX = WINDOW_WIDTH - ASTEROID_SIZE;
    }
    
    //check bullet collision
    if (bullet.bulletY >= asteroid.asteroidY \
    && bullet.bulletY <= asteroid.asteroidY + ASTEROID_SIZE \
    && bullet.bulletX >= asteroid.asteroidX \
    && bullet.bulletX <= asteroid.asteroidX + ASTEROID_SIZE) {

        player.playerScore += 1;
        bullet.bulletY = -BULLET_SIZE;
        bullet.bulletX = -BULLET_SIZE;
        
        asteroid.asteroidX = rand() % (WINDOW_HEIGHT - ASTEROID_SIZE);
        asteroid.asteroidY = WINDOW_WIDTH - ASTEROID_SIZE;
    }

    //check asteroid collision
    if (asteroid.asteroidY >= player.playerY \
    && asteroid.asteroidY <= player.playerY + PLAYER_SIZE \
    && asteroid.asteroidX >= player.playerX \
    && asteroid.asteroidX <= player.playerX + PLAYER_SIZE) {

        player.playerLives -= 1;
        asteroid.asteroidY = -ASTEROID_SIZE;
        asteroid.asteroidX = -ASTEROID_SIZE;
        
        asteroid.asteroidX = rand() % (WINDOW_HEIGHT - ASTEROID_SIZE);
        asteroid.asteroidY = WINDOW_WIDTH - ASTEROID_SIZE;
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
                bullet.bulletY = player.playerY + PLAYER_SIZE / 2 - BULLET_SIZE / 2;
                bullet.bulletX = player.playerX;
            }
            break;
    }
}

void handle_movement_keys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_DOWN:
            player.playerY -= 10;
            if (player.playerY < 50) {
                player.playerY = 50;
            }
            break;
        case GLUT_KEY_UP:
            player.playerY += 10;
            if (player.playerY + PLAYER_SIZE + 50 > WINDOW_HEIGHT) {
                player.playerY = WINDOW_HEIGHT - PLAYER_SIZE - 50;
            }
            break;
        case GLUT_KEY_RIGHT:
            player.playerX += 10;
            if (player.playerX > PLAYER_SIZE + 200) {
                player.playerX = PLAYER_SIZE + 200;
            }
            break;
        case GLUT_KEY_LEFT:
            player.playerX -= 10;
            if (player.playerX < PLAYER_SIZE) {
                player.playerX = PLAYER_SIZE;
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

    player.playerY = WINDOW_HEIGHT / 2;
    player.playerX = PLAYER_SIZE;
    player.playerScore = 0;
    player.playerLives = 1;

    bullet.bulletX = -BULLET_SIZE;
    bullet.bulletY = -BULLET_SIZE;

    asteroid.asteroidY = -ASTEROID_SIZE;
    asteroid.asteroidX = WINDOW_WIDTH - ASTEROID_SIZE;

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