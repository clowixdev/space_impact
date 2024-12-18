#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "constants.h"
#include "lists.h"
#include "extern_pointers.h"

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

            temp->next->asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - temp->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
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
        asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
    }
}

void update(int aux) {
    if (megalovania_is_playing) {
        add_bullet(bullets);
    }

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

    //update player bullet position
    for_bullet_list(bullets, update_bullet_position);

    //update heart position
    if (heart.heartX >= 0) {
        heart.heartX -= heart.heartSpeed;
        if (heart.heartX <= 0) {
            heart.heartY = -heart.heartSize;
            heart.heartX = -heart.heartSize;
        }
    }

    //check heart-player collision
    if (is_colliding_hp(heart, player)) {
        player.playerLives += 1;
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//heal.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        heart.heartY = -heart.heartSize;
        heart.heartX = -heart.heartSize;
    }
    
    //!small_asteroid
    //update asteroid position
    if (spawn_asteroids == true && player.currentLevel != 4) {
        for_asteroid_list(small_asteroids, update_asteroid_position);

        //check bullet-asteroid collision
        struct Asteroid_list *check_bsa_a = small_asteroids;
        struct Bullet_list *check_bsa_b = bullets;

        while (check_bsa_b != NULL) {
            check_bsa_a = small_asteroids;
            while (check_bsa_a != NULL) {
                if (is_colliding_ba(check_bsa_b->bullet, check_bsa_a->asteroid) \
                && (is_bullet_on_screen(check_bsa_b->bullet) && is_asteroid_on_screen(check_bsa_a->asteroid))) {
                    player.playerScore += 1;
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                    
                    remove_from_blist(bullets, check_bsa_b->bullet);

                    int rand_int = rand() % 100;
                    if (rand_int > 70 && player.playerLives < 3 && heart.heartX < 0) {
                        if (!megalovania_is_playing) {
                            PlaySound("..//..//sounds//heart_spawn.wav", NULL, SND_FILENAME | SND_ASYNC);
                        }
                        
                        heart.heartX = check_bsa_a->asteroid->asteroidX;
                        heart.heartY = check_bsa_a->asteroid->asteroidY;
                    }

                    check_bsa_a->asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bsa_a->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                    check_bsa_a->asteroid->asteroidX = WINDOW_WIDTH - check_bsa_a->asteroid->asteroidSize;

                    break;
                }
                check_bsa_a = check_bsa_a->next;
            }
            check_bsa_b = check_bsa_b->next;
        }

        //check asteroid-player collision
        struct Asteroid_list *check_sap = small_asteroids;
        while (check_sap != NULL) {
            if (is_colliding_ap(check_sap->asteroid, player) \
            && is_asteroid_on_screen(check_sap->asteroid)) {
                if (!player.godMode) {
                    player.playerLives -= 1;
                }
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                check_sap->asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_sap->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                check_sap->asteroid->asteroidX = WINDOW_WIDTH - check_sap->asteroid->asteroidSize;

                break;
            }
            check_sap = check_sap->next;
        }
    }


    //!medium_asteroid
    //update asteroid position
    if (spawn_asteroids == true && player.currentLevel != 4) {
        for_asteroid_list(medium_asteroids, update_asteroid_position);

        //check bullet-asteroid collision
        struct Asteroid_list *check_bma_a = medium_asteroids;
        struct Bullet_list *check_bma_b = bullets;

        while (check_bma_b != NULL) {
            check_bma_a = medium_asteroids;
            while (check_bma_a != NULL) {
                if (is_colliding_ba(check_bma_b->bullet, check_bma_a->asteroid) \
                && (is_bullet_on_screen(check_bma_b->bullet) && is_asteroid_on_screen(check_bma_a->asteroid))) {
                    player.playerScore += 1;
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                    remove_from_blist(bullets, check_bma_b->bullet);

                    check_bma_a->asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bma_a->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                    check_bma_a->asteroid->asteroidX = WINDOW_WIDTH - check_bma_a->asteroid->asteroidSize;

                    break;
                }
                check_bma_a = check_bma_a->next;
            }
            check_bma_b = check_bma_b->next;
        }

        //check asteroid-player collision
        struct Asteroid_list *check_map = medium_asteroids;
        while (check_map != NULL) {
            if (is_colliding_ap(check_map->asteroid, player) \
            && is_asteroid_on_screen(check_map->asteroid)) {
                if (!player.godMode) {
                    player.playerLives -= 1;
                }

                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                check_map->asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_map->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                check_map->asteroid->asteroidX = WINDOW_WIDTH - check_map->asteroid->asteroidSize;

                break;
            }
            check_map = check_map->next;
        }
    }

    //!big_asteroid
    //update asteroid position
    if (spawn_asteroids == true && player.currentLevel != 4) {
        for_asteroid_list(big_asteroids, update_asteroid_position);

        //check bullet-asteroid collision
        struct Asteroid_list *check_bba_a = big_asteroids;
        struct Bullet_list *check_bba_b = bullets;

        while (check_bba_b != NULL) {
            check_bba_a = big_asteroids;
            while (check_bba_a != NULL) {
                if (is_colliding_ba(check_bba_b->bullet, check_bba_a->asteroid) \
                && (is_bullet_on_screen(check_bba_b->bullet) && is_asteroid_on_screen(check_bba_a->asteroid))) {
                    player.playerScore += 1;
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                    
                    remove_from_blist(bullets, check_bba_b->bullet);

                    check_bba_a->asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bba_a->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                    check_bba_a->asteroid->asteroidX = WINDOW_WIDTH - check_bba_a->asteroid->asteroidSize;

                    break;
                }
                check_bba_a = check_bba_a->next;
            }
            check_bba_b = check_bba_b->next;
        }

        //check asteroid-player collision
        struct Asteroid_list *check_bap = big_asteroids;
        while (check_bap != NULL) {
            if (is_colliding_ap(check_bap->asteroid, player) \
            && is_asteroid_on_screen(check_bap->asteroid)) {
                if (!player.godMode) {
                    player.playerLives -= 1;
                }

                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                check_bap->asteroid->asteroidY = rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bap->asteroid->asteroidSize) - BORDERS_SIZE + 1) + BORDERS_SIZE;
                check_bap->asteroid->asteroidX = WINDOW_WIDTH - check_bap->asteroid->asteroidSize;

                break;
            }
            check_bap = check_bap->next;
        }
    }

    //! update boss
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
    
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}