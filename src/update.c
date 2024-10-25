#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>

#include "constants.h"
#include "extern_pointers.h"

void update(int aux) {
    if (player.playerLives == 0 && player_is_dead == false) {
        PlaySound("..//..//sounds//lose.wav", NULL, SND_FILENAME | SND_ASYNC);
        player_is_dead = true;

        small_asteroid.spawn = false;
        medium_asteroid.spawn = false;
        big_asteroid.spawn = false;
    }

    if (boss.bossLives == 0 && boss_is_dead == false) {
        PlaySound("..//..//sounds//win.wav", NULL, SND_FILENAME | SND_ASYNC);
        boss_is_dead = true;

        small_asteroid.spawn = false;
        medium_asteroid.spawn = false;
        big_asteroid.spawn = false;
    }

    if (player.playerScore == 5 && changed_to_second == false) {
        PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        player.currentLevel = 2;
        small_asteroid.asteroidSpeed = small_asteroid.asteroidSpeed + 3;
        medium_asteroid.asteroidSpeed = medium_asteroid.asteroidSpeed + 3;
        big_asteroid.asteroidSpeed = big_asteroid.asteroidSpeed + 3;

        changed_to_second = true;
    }

    if (player.playerScore == 10 && changed_to_third == false) {
        PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        player.currentLevel = 3;
        small_asteroid.asteroidSpeed = small_asteroid.asteroidSpeed + 3;
        medium_asteroid.asteroidSpeed = medium_asteroid.asteroidSpeed + 3;
        big_asteroid.asteroidSpeed = big_asteroid.asteroidSpeed + 3;

        changed_to_third = true;
    }

    if (player.playerScore == 15 && changed_to_fourth == false) {
        PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        player.currentLevel = 4;
        
        small_asteroid.spawn = false;
        medium_asteroid.spawn = false;
        big_asteroid.spawn = false;

        changed_to_fourth = true;
    }

    //update player bullet position
    if (bullet.bulletX >= 0) {
        bullet.bulletX += bullet.bulletSpeed;
        if (bullet.bulletX >= WINDOW_WIDTH) {
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
        }
    }

    //update heart position
    if (heart.heartX >= 0) {
        heart.heartX -= heart.heartSpeed;
        if (heart.heartX <= 0) {
            heart.heartY = -heart.heartSize;
            heart.heartX = -heart.heartSize;
        }
    }

    //check heart-player collision
    if (heart.heartY >= player.playerY \
    && heart.heartY <= player.playerY + player.playerSize \
    && heart.heartX >= player.playerX \
    && heart.heartX <= player.playerX + player.playerSize) {

        player.playerLives += 1;
        PlaySound("..//..//sounds//heal.wav", NULL, SND_FILENAME | SND_ASYNC);
        heart.heartY = -heart.heartSize;
        heart.heartX = -heart.heartSize;
    }
    
    //!small_asteroid
    //update asteroid position
    if (small_asteroid.spawn == true && player.currentLevel != 4) {
        small_asteroid.asteroidX -= small_asteroid.asteroidSpeed;
        if (small_asteroid.asteroidX <= 0 && player.playerLives > 0) {
            small_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - small_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            small_asteroid.asteroidX = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }

        //check bullet-asteroid collision
        if (bullet.bulletY >= small_asteroid.asteroidY \
        && bullet.bulletY <= small_asteroid.asteroidY + small_asteroid.asteroidSize \
        && bullet.bulletX >= small_asteroid.asteroidX \
        && bullet.bulletX <= small_asteroid.asteroidX + small_asteroid.asteroidSize) {

            player.playerScore += 1;
            PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;

            int rand_int = rand() % 100;
            if (rand_int > 70 && player.playerLives < 3 && heart.heartX < 0) {
                PlaySound("..//..//sounds//heart_spawn.wav", NULL, SND_FILENAME | SND_ASYNC);
                heart.heartX = small_asteroid.asteroidX;
                heart.heartY = small_asteroid.asteroidY;
            }
            
            small_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - small_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            small_asteroid.asteroidX = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (small_asteroid.asteroidY >= player.playerY \
        && small_asteroid.asteroidY <= player.playerY + player.playerSize \
        && small_asteroid.asteroidX >= player.playerX \
        && small_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
            small_asteroid.asteroidY = -small_asteroid.asteroidSize;
            small_asteroid.asteroidX = -small_asteroid.asteroidSize;
            
            small_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - small_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            small_asteroid.asteroidX = WINDOW_WIDTH - small_asteroid.asteroidSize;
        }
    }


    //!medium_asteroid
    //update asteroid position
    if (medium_asteroid.spawn == true && player.currentLevel != 4) {
        medium_asteroid.asteroidX -= medium_asteroid.asteroidSpeed;
        if (medium_asteroid.asteroidX <= 0 && player.playerLives > 0) {

            medium_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - \
            medium_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;

            medium_asteroid.asteroidX = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }
    

        //check bullet-asteroid collision
        if (bullet.bulletY >= medium_asteroid.asteroidY \
        && bullet.bulletY <= medium_asteroid.asteroidY + medium_asteroid.asteroidSize \
        && bullet.bulletX >= medium_asteroid.asteroidX \
        && bullet.bulletX <= medium_asteroid.asteroidX + medium_asteroid.asteroidSize) {
            player.playerScore += 1;
            PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
            
            medium_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - \
            medium_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            
            medium_asteroid.asteroidX = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (medium_asteroid.asteroidY >= player.playerY \
        && medium_asteroid.asteroidY <= player.playerY + player.playerSize \
        && medium_asteroid.asteroidX >= player.playerX \
        && medium_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
            medium_asteroid.asteroidY = -medium_asteroid.asteroidSize;
            medium_asteroid.asteroidX = -medium_asteroid.asteroidSize;
            
            medium_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - medium_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            medium_asteroid.asteroidX = WINDOW_WIDTH - medium_asteroid.asteroidSize;
        }
    }

    //!big_asteroid
    //update asteroid position
    if (big_asteroid.spawn == true && player.currentLevel != 4) {
        big_asteroid.asteroidX -= big_asteroid.asteroidSpeed;
        if (big_asteroid.asteroidX <= 0 && player.playerLives > 0) {
            big_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - big_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            big_asteroid.asteroidX = WINDOW_WIDTH - big_asteroid.asteroidSize;
        }

        //check bullet-asteroid collision
        if (bullet.bulletY >= big_asteroid.asteroidY \
        && bullet.bulletY <= big_asteroid.asteroidY + big_asteroid.asteroidSize \
        && bullet.bulletX >= big_asteroid.asteroidX \
        && bullet.bulletX <= big_asteroid.asteroidX + big_asteroid.asteroidSize) {

            player.playerScore += 1;
            PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
            
            //random acceptable position on screen
            big_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - big_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            big_asteroid.asteroidX = WINDOW_WIDTH - big_asteroid.asteroidSize;
        }

        //check asteroid-player collision
        if (big_asteroid.asteroidY >= player.playerY \
        && big_asteroid.asteroidY <= player.playerY + player.playerSize \
        && big_asteroid.asteroidX >= player.playerX \
        && big_asteroid.asteroidX <= player.playerX + player.playerSize) {

            player.playerLives -= 1;
            PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
            big_asteroid.asteroidY = -big_asteroid.asteroidSize;
            big_asteroid.asteroidX = -big_asteroid.asteroidSize;
            
            big_asteroid.asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - big_asteroid.asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
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
            PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
            boss_bullet.bulletY = -boss_bullet.bulletSize;
            boss_bullet.bulletX = -boss_bullet.bulletSize;
        }

        //bullet - boss collision
        if (bullet.bulletY >= boss.bossY \
        && bullet.bulletY <= boss.bossY + boss.bossSize \
        && bullet.bulletX >= boss.bossX \
        && bullet.bulletX <= boss.bossX + boss.bossSize) {

            boss.bossLives -= 1;
            PlaySound("..//..//sounds//hit_boss.wav", NULL, SND_FILENAME | SND_ASYNC);
            bullet.bulletY = -bullet.bulletSize;
            bullet.bulletX = -bullet.bulletSize;
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}