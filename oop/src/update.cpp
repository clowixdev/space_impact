#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "constants.h"
#include "lists.h"
#include "extern_pointers.h"

bool is_bullet_on_screen(BulletClass *b) {
    if (b->getPosX() >= 0 && b->getPosX() <= WINDOW_WIDTH) {
        return true;
    } else {
        return false;
    }
}

bool is_asteroid_on_screen(AsteroidClass *a) {
    if (a->getPosX() >= 0 && a->getPosX() <= WINDOW_WIDTH) {
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
            temp->bullet->setPosY(player_clw.getPosY() + player_clw.getSize() / 2 - temp->bullet->getSize() / 2);
            temp->bullet->setPosX(player_clw.getPosX());

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
            temp->bullet->setPosY(boss_clw.getPosY() + boss_clw.getSize() / 2 - temp->bullet->getSize() / 2);
            temp->bullet->setPosX(boss_clw.getPosX());

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

            temp->next->asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - temp->asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
            temp->next->asteroid->setPosX(WINDOW_WIDTH - temp->asteroid->getSize());

            break;
        }

        temp = temp->next;
    }
}

bool is_colliding_ap(AsteroidClass *a, PlayerClass p) {
    if (
        (a->getPosY() >= p.getPosY() && a->getPosY() <= p.getPosY() + p.getSize() \
        && a->getPosX() >= p.getPosX() && a->getPosX() <= p.getPosX() + p.getSize())
        ||
        (a->getPosY()+a->getSize() >= p.getPosY() && a->getPosY()+a->getSize() <= p.getPosY() + p.getSize() \
        && a->getPosX()+a->getSize() >= p.getPosX() && a->getPosX()+a->getSize() <= p.getPosX() + p.getSize())
        )
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_hp(HeartClass h, PlayerClass p) {
    if (
        (h.getPosY() >= p.getPosY() && h.getPosY() <= p.getPosY() + p.getSize() \
        && h.getPosX() >= p.getPosX() && h.getPosX() <= p.getPosX() + p.getSize())
        ||
        (h.getPosY()+h.getSize() >= p.getPosY() && h.getPosY()+h.getSize() <= p.getPosY() + p.getSize() \
        && h.getPosX()+h.getSize() >= p.getPosX() && h.getPosX()+h.getSize() <= p.getPosX() + p.getSize())
        )
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_ba(BulletClass *b, AsteroidClass *a) {
    if (
        (b->getPosY() >= a->getPosY() && b->getPosY() <= a->getPosY() + a->getSize() \
        && b->getPosX() >= a->getPosX() && b->getPosX() <= a->getPosX() + a->getSize())
        ||
        (b->getPosY()+b->getSize() >= a->getPosY() && b->getPosY()+b->getSize() <= a->getPosY() + a->getSize() \
        && b->getPosX()+b->getSize() >= a->getPosX() && b->getPosX()+b->getSize() <= a->getPosX() + a->getSize())
        ) 
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_bp(BulletClass *b, PlayerClass p) {
    if (
        (b->getPosY() >= p.getPosY() && b->getPosY() <= p.getPosY() + p.getSize() \
        && b->getPosX() >= p.getPosX() && b->getPosX() <= p.getPosX() + p.getSize())
        ||
        (b->getPosY()+b->getSize() >= p.getPosY() && b->getPosY()+b->getSize() <= p.getPosY() + p.getSize() \
        && b->getPosX()+b->getSize() >= p.getPosX() && b->getPosX()+b->getSize() <= p.getPosX() + p.getSize())
        )
    {
        return true;
    } else {
        return false;
    }
}

bool is_colliding_bbs(BulletClass *b, BossClass bs) {
    if (
        (b->getPosY() >= bs.getPosY() && b->getPosY() <= bs.getPosY() + bs.getSize() \
        && b->getPosX() >= bs.getPosX() && b->getPosX() <= bs.getPosX() + bs.getSize())
        ||
        (b->getPosY()+b->getSize() >= bs.getPosY() && b->getPosY()+b->getSize() <= bs.getPosY() + bs.getSize() \
        && b->getPosX()+b->getSize() >= bs.getPosX() && b->getPosX()+b->getSize() <= bs.getPosX() + bs.getSize())
        )
    {
        return true;
    } else {
        return false;
    }
}

void update_boss_bullet_position(BulletClass *bullet) {
    if (is_bullet_on_screen(bullet)) {
        bullet->changePosX(-bullet->getSpeed());

        if (!is_bullet_on_screen(bullet)) {
            remove_from_blist(boss_bullets, bullet);
        }
    }
}

void update_bullet_position(BulletClass *bullet) {
    if (is_bullet_on_screen(bullet)) {
        bullet->changePosX(bullet->getSpeed());

        if (!is_bullet_on_screen(bullet)) {
            remove_from_blist(bullets, bullet);
        }
    }
}

void update_asteroid_position(AsteroidClass *asteroid) {
    if (is_asteroid_on_screen(asteroid)) {
        asteroid->changePosX(-(asteroid->getSpeed() + (3 * (player_clw.getLevel() - 1))));
    } else if (!is_asteroid_on_screen(asteroid) && player_clw.getLives() > 0) {
        asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
        asteroid->setPosX(WINDOW_WIDTH - asteroid->getSize());
    }
}

void update(int aux) {
    if (megalovania_is_playing) {
        add_bullet(bullets);
    }

    if (player_clw.getLives() == 0 && player_is_dead == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//lose.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        player_is_dead = true;
        spawn_asteroids = false;
    }

    if (boss_clw.getLives() == 0 && boss_is_dead == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//win.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        boss_is_dead = true;
        spawn_asteroids = false;
    }

    if (player_clw.getScore() == FOR_SECOND_LEVEL && changed_to_second == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        add_asteroid(small_asteroids);
        add_asteroid(medium_asteroids);
        add_asteroid(big_asteroids);

        player_clw.setLevel(2);
        changed_to_second = true;
    }

    if (player_clw.getScore() == FOR_THIRD_LEVEL && changed_to_third == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        add_asteroid(small_asteroids);
        add_asteroid(medium_asteroids);
        add_asteroid(big_asteroids);

        player_clw.setLevel(3);
        changed_to_third = true;
    }

    if (player_clw.getScore() == FOR_BOSS_LEVEL && changed_to_fourth == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        player_clw.setLevel(4);
        
        spawn_asteroids = false;
        changed_to_fourth = true;
    }

    //update player bullet position
    for_bullet_list(bullets, update_bullet_position);

    //update heart position
    if (heart_clw.getPosX() >= 0) {
        heart_clw.changePosX(-heart_clw.getSpeed());
        if (heart_clw.getPosX() <= 0) {
            heart_clw.setPosY(-heart_clw.getSize());
            heart_clw.setPosX(-heart_clw.getSize());
        }
    }

    //check heart-player collision
    if (is_colliding_hp(heart_clw, player_clw)) {
        player_clw.changeLives(1);
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//heal.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        heart_clw.setPosY(-heart_clw.getSize());
        heart_clw.setPosX(-heart_clw.getSize());
    }
    
    //!small_asteroid
    //update asteroid position
    if (spawn_asteroids == true && player_clw.getLevel() != 4) {
        for_asteroid_list(small_asteroids, update_asteroid_position);

        //check bullet-asteroid collision
        struct Asteroid_list *check_bsa_a = small_asteroids;
        struct Bullet_list *check_bsa_b = bullets;

        while (check_bsa_b != NULL) {
            check_bsa_a = small_asteroids;
            while (check_bsa_a != NULL) {
                if (is_colliding_ba(check_bsa_b->bullet, check_bsa_a->asteroid) \
                && (is_bullet_on_screen(check_bsa_b->bullet) && is_asteroid_on_screen(check_bsa_a->asteroid))) {
                    player_clw.changeScore(1);
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                    
                    remove_from_blist(bullets, check_bsa_b->bullet);

                    int rand_int = rand() % 100;
                    if (rand_int > 70 && player_clw.getLives() < 3 && heart_clw.getPosX() < 0) {
                        if (!megalovania_is_playing) {
                            PlaySound("..//..//sounds//heart_spawn.wav", NULL, SND_FILENAME | SND_ASYNC);
                        }
                        
                        heart_clw.setPosX(check_bsa_a->asteroid->getPosX());
                        heart_clw.setPosY(check_bsa_a->asteroid->getPosY());
                    }

                    check_bsa_a->asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bsa_a->asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
                    check_bsa_a->asteroid->setPosX(WINDOW_WIDTH - check_bsa_a->asteroid->getSize());

                    break;
                }
                check_bsa_a = check_bsa_a->next;
            }
            check_bsa_b = check_bsa_b->next;
        }

        //check asteroid-player collision
        struct Asteroid_list *check_sap = small_asteroids;
        while (check_sap != NULL) {
            if (is_colliding_ap(check_sap->asteroid, player_clw) \
            && is_asteroid_on_screen(check_sap->asteroid)) {
                if (!player_clw.inGodMode()) {
                    player_clw.changeLives(-1);
                }
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                check_sap->asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_sap->asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
                check_sap->asteroid->setPosX(WINDOW_WIDTH - check_sap->asteroid->getSize());
            }
            check_sap = check_sap->next;
        }
    }


    //!medium_asteroid
    //update asteroid position
    if (spawn_asteroids == true && player_clw.getLevel() != 4) {
        for_asteroid_list(medium_asteroids, update_asteroid_position);

        //check bullet-asteroid collision
        struct Asteroid_list *check_bma_a = medium_asteroids;
        struct Bullet_list *check_bma_b = bullets;

        while (check_bma_b != NULL) {
            check_bma_a = medium_asteroids;
            while (check_bma_a != NULL) {
                if (is_colliding_ba(check_bma_b->bullet, check_bma_a->asteroid) \
                && (is_bullet_on_screen(check_bma_b->bullet) && is_asteroid_on_screen(check_bma_a->asteroid))) {
                    player_clw.changeScore(1);
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                    remove_from_blist(bullets, check_bma_b->bullet);

                    check_bma_a->asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bma_a->asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
                    check_bma_a->asteroid->setPosX(WINDOW_WIDTH - check_bma_a->asteroid->getSize());

                    break;
                }
                check_bma_a = check_bma_a->next;
            }
            check_bma_b = check_bma_b->next;
        }

        //check asteroid-player collision
        struct Asteroid_list *check_map = medium_asteroids;
        while (check_map != NULL) {
            if (is_colliding_ap(check_map->asteroid, player_clw) \
            && is_asteroid_on_screen(check_map->asteroid)) {
                if (!player_clw.inGodMode()) {
                    player_clw.changeLives(-1);
                }

                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                check_map->asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_map->asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
                check_map->asteroid->setPosX(WINDOW_WIDTH - check_map->asteroid->getSize());
            }
            check_map = check_map->next;
        }
    }

    //!big_asteroid
    //update asteroid position
    if (spawn_asteroids == true && player_clw.getLevel() != 4) {
        for_asteroid_list(big_asteroids, update_asteroid_position);

        //check bullet-asteroid collision
        struct Asteroid_list *check_bba_a = big_asteroids;
        struct Bullet_list *check_bba_b = bullets;

        while (check_bba_b != NULL) {
            check_bba_a = big_asteroids;
            while (check_bba_a != NULL) {
                if (is_colliding_ba(check_bba_b->bullet, check_bba_a->asteroid) \
                && (is_bullet_on_screen(check_bba_b->bullet) && is_asteroid_on_screen(check_bba_a->asteroid))) {
                    player_clw.changeScore(1);
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                    
                    remove_from_blist(bullets, check_bba_b->bullet);

                    check_bba_a->asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bba_a->asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
                    check_bba_a->asteroid->setPosX(WINDOW_WIDTH - check_bba_a->asteroid->getSize());

                    break;
                }
                check_bba_a = check_bba_a->next;
            }
            check_bba_b = check_bba_b->next;
        }

        //check asteroid-player collision
        struct Asteroid_list *check_bap = big_asteroids;
        while (check_bap != NULL) {
            if (is_colliding_ap(check_bap->asteroid, player_clw) \
            && is_asteroid_on_screen(check_bap->asteroid)) {
                if (!player_clw.inGodMode()) {
                    player_clw.changeLives(-1);
                }

                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                check_bap->asteroid->setPosY(rand() % ((WINDOW_HEIGHT - BORDERS_SIZE - check_bap->asteroid->getSize()) - BORDERS_SIZE + 1) + BORDERS_SIZE);
                check_bap->asteroid->setPosX(WINDOW_WIDTH - check_bap->asteroid->getSize());
            }
            check_bap = check_bap->next;
        }
    }

    //! update boss
    if (player_clw.getLevel() == 4 && boss_is_dead == false) {
        //boss movement
        if (boss_clw.getPosY() >= boss_clw.getSize() && boss_clw.hasReachedTop() == true) {
            boss_clw.changePosY(-3);

            if (boss_clw.getPosY() < boss_clw.getSize()) {
                boss_clw.setPosY(boss_clw.getSize());
                boss_clw.setReachedBot(true);
                boss_clw.setReachedTop(false);
            }
        } 
        
        if (boss_clw.getPosY() <= WINDOW_HEIGHT - boss_clw.getSize() - 40 && boss_clw.hasReachedBot() == true) {
            boss_clw.changePosY(3);

            if (boss_clw.getPosY() > WINDOW_HEIGHT - boss_clw.getSize() - 40) {
                boss_clw.setPosY(WINDOW_HEIGHT - boss_clw.getSize() - 40);
                boss_clw.setReachedBot(false);
                boss_clw.setReachedTop(true);
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
            if (is_colliding_bp(check_bsp->bullet, player_clw)) {
                if (!player_clw.inGodMode()) {
                    player_clw.changeLives(-1);
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
            if (is_colliding_bbs(check_bbs->bullet, boss_clw)) {
                boss_clw.changeLives(-1);
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