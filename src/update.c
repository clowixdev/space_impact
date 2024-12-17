#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include <stdio.h>

#include "constants.h"
#include "lists.h"
#include "extern_pointers.h"
#include "rand.h"

bool is_bullet_on_screen(struct Bullet *b) {
    if (b->bulletX >= 0 && b->bulletX <= WINDOW_WIDTH) {
        return true;
    } else {
        return false;
    }
}

bool is_asteroid_on_screen(struct Asteroid *a) {
    if (a->asteroidX >= 0 && a->asteroidX <= WINDOW_WIDTH) {
        return true;
    } else {
        return false;
    }
}

void add_bullet(struct Bullet_list *bl_head) {
    struct Bullet_list *temp = bl_head;
    
    while (true) {
        if (is_bullet_on_screen(temp->bullet) && temp->next == NULL) {
            struct Bullet_list *bl_elem = init_bullet_list_elem();
            temp->next = bl_elem;
        } else if (is_bullet_on_screen(temp->bullet) && temp->next != NULL) {
            temp = temp->next;
        } else if (!is_bullet_on_screen(temp->bullet)) {
            temp->bullet->bulletY = player.playerY + player.playerSize / 2 - temp->bullet->bulletSize / 2;
            temp->bullet->bulletX = player.playerX;

            break;
        }
    }
}

void add_boss_bullet(struct Bullet_list *bl_head) {
    struct Bullet_list *temp = bl_head;
    
    while (true) {
        if (is_bullet_on_screen(temp->bullet) && temp->next == NULL) {
            struct Bullet_list *bl_elem = init_bullet_list_elem();
            temp->next = bl_elem;
        } else if (is_bullet_on_screen(temp->bullet) && temp->next != NULL) {
            temp = temp->next;
        } else if (!is_bullet_on_screen(temp->bullet)) {
            temp->bullet->bulletY = boss.bossY + boss.bossSize / 2 - temp->bullet->bulletSize / 2;
            temp->bullet->bulletX = boss.bossX;

            break;
        }
    }
}

void add_asteroid(struct Asteroid_list *al_head) {
    char asteroid_type = 'o';
    if (al_head == small_asteroids) {
        asteroid_type = 's';
    } else if (al_head == medium_asteroids) {
        asteroid_type = 'm';
    } else if (al_head == big_asteroids) {
        asteroid_type = 'b';
    }

    struct Asteroid_list *temp = al_head;
    
    while (temp != NULL) {
        if (temp->next == NULL) {
            struct Asteroid_list *al_elem = init_asteroid_list_elem(asteroid_type);
            temp->next = al_elem;

            temp->next->asteroid->asteroidY = get_random_number() % ((WINDOW_HEIGHT - BORDERS_SIZE - temp->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
            temp->next->asteroid->asteroidX = WINDOW_WIDTH - temp->asteroid->asteroidSize;

            break;
        }

        temp = temp->next;
    }
}

bool is_colliding_ap(struct Asteroid *a, struct Player p) {
    if (
        (a->asteroidY >= p.playerY && a->asteroidY <= p.playerY + p.playerSize \
        && a->asteroidX >= p.playerX && a->asteroidX <= p.playerX + p.playerSize)
        ||
        (a->asteroidY+a->asteroidSize >= p.playerY && a->asteroidY+a->asteroidSize <= p.playerY + p.playerSize \
        && a->asteroidX+a->asteroidSize >= p.playerX && a->asteroidX+a->asteroidSize <= p.playerX + p.playerSize)
        )
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_hp(struct Heart h, struct Player p) {
    if (
        (h.heartY >= p.playerY && h.heartY <= p.playerY + p.playerSize \
        && h.heartX >= p.playerX && h.heartX <= p.playerX + p.playerSize)
        ||
        (h.heartY+h.heartSize >= p.playerY && h.heartY+h.heartSize <= p.playerY + p.playerSize \
        && h.heartX+h.heartSize >= p.playerX && h.heartX+h.heartSize <= p.playerX + p.playerSize)
        )
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_ba(struct Bullet *b, struct Asteroid *a) {
    if (
        (b->bulletY >= a->asteroidY && b->bulletY <= a->asteroidY + a->asteroidSize \
        && b->bulletX >= a->asteroidX && b->bulletX <= a->asteroidX + a->asteroidSize)
        ||
        (b->bulletY+b->bulletSize >= a->asteroidY && b->bulletY+b->bulletSize <= a->asteroidY + a->asteroidSize \
        && b->bulletX+b->bulletSize >= a->asteroidX && b->bulletX+b->bulletSize <= a->asteroidX + a->asteroidSize)
        ) 
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_bp(struct Bullet *b, struct Player p) {
    if (
        (b->bulletY >= p.playerY && b->bulletY <= p.playerY + p.playerSize \
        && b->bulletX >= p.playerX && b->bulletX <= p.playerX + p.playerSize)
        ||
        (b->bulletY+b->bulletSize >= p.playerY && b->bulletY+b->bulletSize <= p.playerY + p.playerSize \
        && b->bulletX+b->bulletSize >= p.playerX && b->bulletX+b->bulletSize <= p.playerX + p.playerSize)
        )
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_bbs(struct Bullet *b, struct Boss bs) {
    if (
        (b->bulletY >= bs.bossY && b->bulletY <= bs.bossY + bs.bossSize \
        && b->bulletX >= bs.bossX && b->bulletX <= bs.bossX + bs.bossSize)
        ||
        (b->bulletY+b->bulletSize >= bs.bossY && b->bulletY+b->bulletSize <= bs.bossY + bs.bossSize \
        && b->bulletX+b->bulletSize >= bs.bossX && b->bulletX+b->bulletSize <= bs.bossX + bs.bossSize)
        )
    {
        return true;
    } else {
        return false;
    }
}

void update_boss_bullet_position(struct Bullet *bullet) {
    if (is_bullet_on_screen(bullet)) {
        bullet->bulletX -= bullet->bulletSpeed;

        if (!is_bullet_on_screen(bullet)) {
            remove_from_blist(boss_bullets, bullet);
        }
    }
}

void update_bullet_position(struct Bullet *bullet) {
    if (is_bullet_on_screen(bullet)) {
        bullet->bulletX += bullet->bulletSpeed;

        if (!is_bullet_on_screen(bullet)) {
            remove_from_blist(bullets, bullet);
        }
    }
}

void update_asteroid_position(struct Asteroid *asteroid) {
    if (is_asteroid_on_screen(asteroid)) {
        asteroid->asteroidX -= asteroid->asteroidSpeed + (3 * (player.currentLevel - 1));
    } else if (!is_asteroid_on_screen(asteroid) && player.playerLives > 0) {
        asteroid->asteroidY = get_random_number() % ((WINDOW_HEIGHT - BORDERS_SIZE - asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
    }
}

void update_player_state() {
    if (player.playerLives == 0 && player_is_dead == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//lose.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        player_is_dead = true;
        spawn_asteroids = false;
    }

    if (boss.bossLives == 0 && boss_is_dead == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//win.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        boss_is_dead = true;
        spawn_asteroids = false;
    }

    if (player.playerScore == FOR_SECOND_LEVEL && changed_to_second == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        add_asteroid(small_asteroids);
        add_asteroid(medium_asteroids);
        add_asteroid(big_asteroids);

        player.currentLevel = 2;
        changed_to_second = true;
    }

    if (player.playerScore == FOR_THIRD_LEVEL && changed_to_third == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        add_asteroid(small_asteroids);
        add_asteroid(medium_asteroids);
        add_asteroid(big_asteroids);

        player.currentLevel = 3;
        changed_to_third = true;
    }

    if (player.playerScore == FOR_BOSS_LEVEL && changed_to_fourth == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        player.currentLevel = 4;
        
        spawn_asteroids = false;
        changed_to_fourth = true;
    }

}

void update_boss_state(){

    if (player.currentLevel == 4 && boss_is_dead == false) {
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
        if (boss_delay < BOSS_DELAY_VALUE) {
            boss_delay++;
        } else if (boss_delay == BOSS_DELAY_VALUE){
            add_boss_bullet(boss_bullets);
            boss_delay = 0;
        }

        //update boss_bullet position
        for_bullet_list(boss_bullets, update_boss_bullet_position);

        //boss_bullet - player collision
        struct Bullet_list *check_bsp = boss_bullets;
        while (check_bsp != NULL) {
            if (is_colliding_bp(check_bsp->bullet, player)) {
                if (!player.godMode) {
                    player.playerLives -= 1;
                }
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }
                
                remove_from_blist(boss_bullets, check_bsp->bullet);

                break;
            }
            check_bsp = check_bsp->next;
        }

        //bullet - boss collision
        struct Bullet_list *check_bbs = bullets;
        while (check_bbs != NULL) {
            if (is_colliding_bbs(check_bbs->bullet, boss)) {
                boss.bossLives -= 1;
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_boss.wav", NULL, SND_FILENAME | SND_ASYNC);
                }
                
                remove_from_blist(bullets, check_bbs->bullet);

                break;
            }
            check_bbs = check_bbs->next;
        }
    }
}

void maybe_spawn_heart(struct Asteroid_list *a){
    int rand_int = get_random_number() % 100;
    if (rand_int > 70 && player.playerLives < 3 && heart.heartX < 0) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//heart_spawn.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        heart.heartX = a->asteroid->asteroidX;
        heart.heartY = a->asteroid->asteroidY;
    }
}

void check_bullet_asteroid_collisions(struct Asteroid_list *asteroids) {
    struct Asteroid_list *current_asteroid = asteroids;
    struct Bullet_list *current_bullet = bullets;

    while (current_bullet != NULL) {
        current_asteroid = asteroids;
        while (current_asteroid != NULL) {
            if (is_colliding_ba(current_bullet->bullet, current_asteroid->asteroid) &&
                is_bullet_on_screen(current_bullet->bullet) &&
                is_asteroid_on_screen(current_asteroid->asteroid)) {

                player.playerScore++;
                if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                
                remove_from_blist(bullets, current_bullet->bullet);
                
                maybe_spawn_heart(current_asteroid);

                current_asteroid->asteroid->asteroidY = get_random_number() % ((WINDOW_HEIGHT - BORDERS_SIZE - current_asteroid->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                current_asteroid->asteroid->asteroidX = WINDOW_WIDTH - current_asteroid->asteroid->asteroidSize;
             

                break;
            }
            current_asteroid = current_asteroid->next;
        }
        current_bullet = current_bullet->next;
    }
}

void check_asteroid_player_collisions(struct Asteroid_list *current_asteroid)
{
    while(current_asteroid != NULL) {
            if (is_colliding_ap(current_asteroid->asteroid, player) \
            && is_asteroid_on_screen(current_asteroid->asteroid)) {
                if (!player.godMode) {
                    player.playerLives -= 1;
                }
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                current_asteroid->asteroid->asteroidY = get_random_number() % ((WINDOW_HEIGHT - BORDERS_SIZE - current_asteroid->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                current_asteroid->asteroid->asteroidX = WINDOW_WIDTH - current_asteroid->asteroid->asteroidSize;

                break;
            }
            current_asteroid = current_asteroid->next;
        }
}

void update(int aux) {

    if (!player.godMode && update_count %16==0 ){
        update_player_state();
    }

     if (!player.godMode && player.currentLevel == 4){
        update_boss_state();
    }
    //update player bullet position
    for_bullet_list(bullets, update_bullet_position);

    if (!player.godMode)
    {
        //update heart position
        if (heart.heartX >= 0) {
            heart.heartX -= heart.heartSpeed;
            if (heart.heartX <= 0) {
                heart.heartY = -heart.heartSize;
                heart.heartX = -heart.heartSize;
            }
        }

        //check heart-player collision
        if (update_count %4==0 && is_colliding_hp(heart, player)) {
            player.playerLives += 1;
            if (!megalovania_is_playing) {
                PlaySound("..//..//sounds//heal.wav", NULL, SND_FILENAME | SND_ASYNC);
            }

            heart.heartY = -heart.heartSize;
            heart.heartX = -heart.heartSize;
        }
    }

    //collisions
    if (spawn_asteroids == true && player.currentLevel != 4) {
        for_asteroid_list(small_asteroids, update_asteroid_position);
        for_asteroid_list(medium_asteroids, update_asteroid_position);
        for_asteroid_list(big_asteroids, update_asteroid_position);

        if (update_count%2==0){
            check_bullet_asteroid_collisions(small_asteroids);
            check_bullet_asteroid_collisions(medium_asteroids);
            check_bullet_asteroid_collisions(big_asteroids);

            check_asteroid_player_collisions(small_asteroids);
            check_asteroid_player_collisions(medium_asteroids);
            check_asteroid_player_collisions(big_asteroids);
        }
    }
  
    update_count++;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}