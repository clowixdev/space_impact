#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

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

void add_bullet(struct Bullet_list **b_array) {
    int y_coordinate = player.playerY + player.playerSize / 2 - B_SIZE / 2;
    int line_number = (y_coordinate - BORDERS_SIZE) / BA_SIZE;
    bool flag_between = false;
    struct Bullet_list *temp = b_array[line_number];
    struct Bullet *bullet;
    
    while (true) {
        if (is_bullet_on_screen(temp->bullet) && temp->next == NULL) {
            struct Bullet_list *bl_elem = init_bullet_list_elem();
            temp->next = bl_elem;
        } else if (is_bullet_on_screen(temp->bullet) && temp->next != NULL) {
            temp = temp->next;
        } else if (!is_bullet_on_screen(temp->bullet)) {
            temp->bullet->bulletY = y_coordinate;
            temp->bullet->bulletX = player.playerX;
            bullet = temp->bullet;

            if(((y_coordinate + bullet->bulletSize - BORDERS_SIZE) / BA_SIZE) != line_number) {
                flag_between = true;
            }
            bullet->between = flag_between;

            break;
        }
    }

    // bullet between lines
    if (flag_between) {
        temp = b_array[line_number + 1];
        while (true) {
            if (is_bullet_on_screen(temp->bullet) && temp->next == NULL) {
                struct Bullet_list *bl_elem = init_bullet_list_elem();
                temp->next = bl_elem;
            } else if (is_bullet_on_screen(temp->bullet) && temp->next != NULL) {
                temp = temp->next;
            } else if (!is_bullet_on_screen(temp->bullet)) {
                temp->bullet = bullet;
                
                break;
            }
        }
    }
}

void add_boss_bullet(struct Bullet_list **b_array) {
    int y_coordinate = boss.bossY + boss.bossSize / 2 - B_SIZE / 2;
    int line_number = (y_coordinate - BORDERS_SIZE) / BA_SIZE;
    bool flag_between = false;

    if(((y_coordinate + B_SIZE - BORDERS_SIZE) / BA_SIZE) != line_number) {
        flag_between = true;
    }

    struct Bullet_list *temp = b_array[line_number];
    struct Bullet *bullet;
    
    while (true) {
        if (is_bullet_on_screen(temp->bullet) && temp->next == NULL) {
            struct Bullet_list *bl_elem = init_bullet_list_elem();
            temp->next = bl_elem;
        } else if (is_bullet_on_screen(temp->bullet) && temp->next != NULL) {
            temp = temp->next;
        } else if (!is_bullet_on_screen(temp->bullet)) {
            temp->bullet->bulletY = y_coordinate;
            temp->bullet->bulletX = boss.bossX;
            bullet = temp->bullet;
            bullet->between = flag_between;

            break;
        }
    }

    // bullet between lines
    if (flag_between) {
        temp = b_array[line_number + 1];
        while (true) {
            if (is_bullet_on_screen(temp->bullet) && temp->next == NULL) {
                struct Bullet_list *bl_elem = init_bullet_list_elem();
                temp->next = bl_elem;
            } else if (is_bullet_on_screen(temp->bullet) && temp->next != NULL) {
                temp = temp->next;
            } else if (!is_bullet_on_screen(temp->bullet)) {
                temp->bullet = bullet;
                
                break;
            }
        }
    }
}

void add_asteroid(struct Asteroid_list **a_array) {
    char asteroid_type = 'o';
    int asteroidsize = -10;
    int line_number;
    int y_coordinate;

    if (a_array == small_asteroids_array) {
        line_number = get_random_number() % LINE_COUNT;
        asteroid_type = 's';
        asteroidsize = SA_SIZE;
        y_coordinate = (BORDERS_SIZE + line_number * BA_SIZE) + get_random_number() % (BA_SIZE - asteroidsize);
    } else if (a_array == medium_asteroids_array) {
        line_number = get_random_number() % LINE_COUNT;
        asteroid_type = 'm';
        asteroidsize = MA_SIZE;
        y_coordinate = (BORDERS_SIZE + line_number * BA_SIZE) + get_random_number() % (BA_SIZE - asteroidsize);
    } else if (a_array == big_asteroids_array) {
        line_number = get_random_number() % LINE_COUNT;
        y_coordinate = (BORDERS_SIZE + line_number * BA_SIZE);    
        asteroid_type = 'b';
        asteroidsize = BA_SIZE;
    }

    struct Asteroid_list *temp = a_array[line_number];
    while (temp != NULL) {
        if (temp->next == NULL) {
            struct Asteroid_list *al_elem = init_asteroid_list_elem(asteroid_type);
            temp->next = al_elem;

            temp->next->asteroid->asteroidY = y_coordinate;
            temp->next->asteroid->asteroidX = WINDOW_WIDTH - asteroidsize;
            temp->next->asteroid->line = line_number;

            return;
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
            int line_number = (bullet->bulletY - BORDERS_SIZE) / BA_SIZE;
            remove_from_blist(boss_bullet_array[line_number], bullet);
            if (bullet->between) {
                remove_from_blist(boss_bullet_array[line_number + 1], bullet);
            }
        }
    }
}

void update_bullet_position(struct Bullet *bullet) {
    if (is_bullet_on_screen(bullet)) {
        if (bullet->between) {
            bullet->bulletX += bullet->bulletSpeed / 2;
        } else {
            bullet->bulletX += bullet->bulletSpeed;
        }

        if (!is_bullet_on_screen(bullet)) {
            int line_number = (bullet->bulletY - BORDERS_SIZE) / BA_SIZE;
            remove_from_blist(bullet_array[line_number], bullet);
        }
    }
}

void update_asteroid_position(struct Asteroid_list **asteroid_array, struct Asteroid *asteroid) {
    if (is_asteroid_on_screen(asteroid)) {
        asteroid->asteroidX -= asteroid->asteroidSpeed + (3 * (player.currentLevel - 1));
    } else if (!is_asteroid_on_screen(asteroid) && player.playerLives > 0) {
        if (megalovania_is_playing) {
            asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
            return;
        }

        int rand = get_random_number();
        int new_line_number = rand % LINE_COUNT;
        int size_offset = BA_SIZE - asteroid->asteroidSize;
        int size = asteroid->asteroidSize;
        struct Asteroid_list * list_elem;
        list_elem = remove_from_alist(asteroid_array[asteroid->line], asteroid);
        add_to_alist(asteroid_array[new_line_number], list_elem);
        asteroid->asteroidY = (new_line_number * BA_SIZE + BORDERS_SIZE);
        
        if (asteroid->asteroidSize < BA_SIZE) {
            asteroid->asteroidY += rand % size_offset;
        }

        asteroid->line = new_line_number;
        asteroid->asteroidX = WINDOW_WIDTH - asteroid->asteroidSize;
    }
}

void update_player_state() {
    if (game_just_started == true) { //!! move to another place
        add_asteroid(small_asteroids_array);
        add_asteroid(medium_asteroids_array);
        add_asteroid(big_asteroids_array);

        game_just_started = false;
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

        add_asteroid(small_asteroids_array);
        add_asteroid(medium_asteroids_array);
        add_asteroid(big_asteroids_array);

        player.currentLevel = 2;
        changed_to_second = true;
    }

    if (player.playerScore == FOR_THIRD_LEVEL && changed_to_third == false) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//next_level.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        add_asteroid(small_asteroids_array);
        add_asteroid(medium_asteroids_array);
        add_asteroid(big_asteroids_array);

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

void update_boss_state() {
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
        } else if (boss_delay == BOSS_DELAY_VALUE) {
            add_boss_bullet(boss_bullet_array);
            boss_delay = 0;
        }

        //update boss_bullet position
        for (int i = 0; i < LINE_COUNT; i++) {
            for_bullet_list(boss_bullets, update_boss_bullet_position);
        }

        //boss_bullet - player collision
        int line_number = (player.playerY - BORDERS_SIZE) / BA_SIZE;
        struct Bullet_list *check_bsp = boss_bullet_array[line_number];
        while (check_bsp != NULL) {
            if (is_colliding_bp(check_bsp->bullet, player)) {
                if (!player.godMode) {
                    player.playerLives -= 1;
                }

                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                }

                remove_from_blist(boss_bullet_array[line_number], check_bsp->bullet);

                if ((line_number + 1) <= LINE_COUNT) {
                    remove_from_blist(boss_bullet_array[line_number + 1], check_bsp->bullet);
                }

                break;
            }
            check_bsp = check_bsp->next;
        }

        // between lines
        if ((line_number * BA_SIZE + BORDERS_SIZE + player.playerSize) / BA_SIZE != line_number) {
            struct Bullet_list *check_bsp = boss_bullet_array[line_number + 1];
            while (check_bsp != NULL) {
                if (is_colliding_bp(check_bsp->bullet, player)) {
                    if (!player.godMode) {
                        player.playerLives -= 1;
                    }

                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }

                    remove_from_blist(boss_bullet_array[line_number], check_bsp->bullet);

                    if ((line_number + 1) <= LINE_COUNT) {
                        remove_from_blist(boss_bullet_array[line_number + 1], check_bsp->bullet);
                    }

                    break;
                }
                check_bsp = check_bsp->next;
            }
        }

        //bullet - boss collision
        line_number = (boss.bossY - BORDERS_SIZE) / BA_SIZE;
        struct Bullet_list *check_bbs = bullet_array[line_number];
        while (check_bbs != NULL) {
            if (is_colliding_bbs(check_bbs->bullet, boss)) {
                boss.bossLives -= 1;
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_boss.wav", NULL, SND_FILENAME | SND_ASYNC);
                }
                
                remove_from_blist(bullet_array[line_number], check_bbs->bullet);

                if ((line_number + 1) <= LINE_COUNT) {
                    remove_from_blist(bullet_array[line_number + 1], check_bsp->bullet);
                }

                break;
            }
            check_bbs = check_bbs->next;
        }

        line_number++;
        check_bbs = bullet_array[line_number];
        while (check_bbs != NULL) {
            if (is_colliding_bbs(check_bbs->bullet, boss)) {
                boss.bossLives -= 1;
                if (!megalovania_is_playing) {
                    PlaySound("..//..//sounds//hit_boss.wav", NULL, SND_FILENAME | SND_ASYNC);
                }
                
                remove_from_blist(bullet_array[line_number], check_bbs->bullet);

                if ((line_number + 1) <= LINE_COUNT) {
                    remove_from_blist(bullet_array[line_number + 1], check_bsp->bullet);
                }

                break;
            }
            check_bbs = check_bbs->next;
        }

        if ((line_number+1) <= LINE_COUNT && \
            ((boss.bossY + boss.bossSize - BORDERS_SIZE) / BA_SIZE - \
            (boss.bossY - BORDERS_SIZE) / BA_SIZE ) == 2) {

            line_number++;
            check_bbs = bullet_array[line_number];
            while (check_bbs != NULL) {
                if (is_colliding_bbs(check_bbs->bullet, boss)) {
                    boss.bossLives -= 1;
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_boss.wav", NULL, SND_FILENAME | SND_ASYNC);
                    }
                    
                    remove_from_blist(bullet_array[line_number], check_bbs->bullet);

                    if ((line_number + 1) <= LINE_COUNT) {
                        remove_from_blist(bullet_array[line_number + 1], check_bsp->bullet);
                    }

                    break;
                }
                check_bbs = check_bbs->next;
            }
        }
    }
}

void maybe_spawn_heart(struct Asteroid_list *a) {
    int rand_int = get_random_number() % 100;
    if (rand_int > 70 && player.playerLives < 3 && heart.heartX < 0) {
        if (!megalovania_is_playing) {
            PlaySound("..//..//sounds//heart_spawn.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
        
        heart.heartX = a->asteroid->asteroidX;
        heart.heartY = a->asteroid->asteroidY;
    }
}

void check_bullet_asteroid_collisions(struct Asteroid_list **asteroids) {
    for (int i = 0; i < LINE_COUNT; i++) {
        struct Asteroid_list *current_asteroid = asteroids[i]->next;
        struct Bullet_list *current_bullet = bullet_array[i];
        while (current_bullet != NULL) {
            while (current_asteroid != NULL) {
                if (is_colliding_ba(current_bullet->bullet, current_asteroid->asteroid) &&
                    is_bullet_on_screen(current_bullet->bullet) &&
                    is_asteroid_on_screen(current_asteroid->asteroid)) {

                    player.playerScore++;
                    if (!megalovania_is_playing) {
                        PlaySound("..//..//sounds//hit_asteroid.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if (asteroids == small_asteroids_array) {
                            maybe_spawn_heart(current_asteroid);
                        }
                    }
                    
                    remove_from_blist(bullet_array[i], current_bullet->bullet);

                    if ((i + 1) < LINE_COUNT && current_bullet->bullet->between) {
                        remove_from_blist(bullet_array[i + 1], current_bullet->bullet);
                    }

                    int new_line_number = get_random_number() % LINE_COUNT;

                    remove_from_alist(asteroids[i], current_asteroid->asteroid);
                    add_to_alist(asteroids[new_line_number], current_asteroid);

                    current_asteroid->asteroid->line = new_line_number;
                    current_asteroid->asteroid->asteroidY = (new_line_number * BA_SIZE + BORDERS_SIZE);//!!!
                    current_asteroid->asteroid->asteroidX = WINDOW_WIDTH - current_asteroid->asteroid->asteroidSize;
                
                    break;
                }
                current_asteroid = current_asteroid->next;
            }
            current_bullet = current_bullet->next;
            current_asteroid = asteroids[i]->next;
        }
    }
}

void check_asteroid_player_collisions(struct Asteroid_list **asteroid_array) {
    int line_number = (player.playerY - BORDERS_SIZE) / BA_SIZE;
    struct Asteroid_list *current_asteroid = asteroid_array[line_number]->next;
    struct Asteroid_list *next_asteroid;
    while (current_asteroid != NULL) {
        next_asteroid = current_asteroid->next;
        if (is_colliding_ap(current_asteroid->asteroid, player) \
            && is_asteroid_on_screen(current_asteroid->asteroid)) {
            if (!player.godMode) {
                player.playerLives -= 1;
            }

            if (!megalovania_is_playing) {
                PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
            }

            int new_line_number = get_random_number() % LINE_COUNT;
            
            remove_from_alist(asteroid_array[line_number], current_asteroid->asteroid);
            add_to_alist(asteroid_array[new_line_number], current_asteroid);

            current_asteroid->asteroid->line = new_line_number;
            current_asteroid->asteroid->asteroidY = (new_line_number * BA_SIZE + BORDERS_SIZE);//!!
            current_asteroid->asteroid->asteroidX = WINDOW_WIDTH - current_asteroid->asteroid->asteroidSize;
        }
        current_asteroid = next_asteroid;
    }

    //last line
    if (line_number == LINE_COUNT) {
        return;
    }

    current_asteroid = asteroid_array[line_number + 1];
    while (current_asteroid != NULL) {
        next_asteroid = current_asteroid->next;
        if (is_colliding_ap(current_asteroid->asteroid, player) \
            && is_asteroid_on_screen(current_asteroid->asteroid)) {
            if (!player.godMode) {
                player.playerLives -= 1;
            }

            if (!megalovania_is_playing) {
                PlaySound("..//..//sounds//hit_player.wav", NULL, SND_FILENAME | SND_ASYNC);
            }

            int new_line_number = get_random_number() % LINE_COUNT;
                
            remove_from_alist(asteroid_array[line_number + 1],current_asteroid->asteroid);
            add_to_alist(asteroid_array[new_line_number], current_asteroid);

            current_asteroid->asteroid->line = new_line_number;
            current_asteroid->asteroid->asteroidY = (new_line_number * BA_SIZE + BORDERS_SIZE);//!!
            current_asteroid->asteroid->asteroidX = WINDOW_WIDTH - current_asteroid->asteroid->asteroidSize;
        }
        current_asteroid = next_asteroid;
    }
}

void update(int aux) {
    if (megalovania_is_playing) {
        add_bullet(bullet_array);
    }

    if (!player.godMode && update_count % 16 == 0) {
        update_player_state();
    }

    if (!player.godMode && player.currentLevel == 4) {
        //TODO
        //update_boss_state();
    }

    //update player bullet position
    for(int i = 0; i < LINE_COUNT; i++) {
        for_bullet_list(bullet_array[i], update_bullet_position);
    }

    if (!player.godMode) {
        //update heart position
        if (heart.heartX >= 0) {
            heart.heartX -= heart.heartSpeed;
            if (heart.heartX <= 0) {
                heart.heartY = -heart.heartSize;
                heart.heartX = -heart.heartSize;
            }
        }

        //check heart-player collision
        if (update_count % 4 == 0 && is_colliding_hp(heart, player)) {
            player.playerLives += 1;
            if (!megalovania_is_playing) {
                PlaySound("..//..//sounds//heal.wav", NULL, SND_FILENAME | SND_ASYNC);
            }

            heart.heartY = -heart.heartSize;
            heart.heartX = -heart.heartSize;
        }
    }

    // collisions check
    if (spawn_asteroids == true && player.currentLevel != 4) {
        for(int i = 0; i < LINE_COUNT; i++) {
            for_asteroid_list(small_asteroids_array, small_asteroids_array[i], update_asteroid_position);
            for_asteroid_list(medium_asteroids_array, medium_asteroids_array[i], update_asteroid_position);
            for_asteroid_list(big_asteroids_array, big_asteroids_array[i], update_asteroid_position);
        }

        if (update_count % 2 == 0 ) {
            check_bullet_asteroid_collisions(small_asteroids_array);
            check_bullet_asteroid_collisions(medium_asteroids_array);
            check_bullet_asteroid_collisions(big_asteroids_array);

            check_asteroid_player_collisions(small_asteroids_array);
            check_asteroid_player_collisions(medium_asteroids_array);
            check_asteroid_player_collisions(big_asteroids_array);
        }
    }
    
    update_count++;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}