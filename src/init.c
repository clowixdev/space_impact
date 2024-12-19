#include <GL/glut.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "constants.h"
#include "lists.h"
#include "extern_pointers.h"
#include "rand.h"

void main_menu_init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    //?player -> bullet -> boss_bullet -> s_asteroid -> m_asteroid -> b_asteroid -> boss -> background -> main_menu_start -> main_menu_exit
    glGenTextures(TEXTURES_AMT, textures);

    //!main_menu_start - start
    glBindTexture(GL_TEXTURE_2D, textures[11]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int menus_width = 0, menus_height = 0, menus_channels = 0;
    unsigned char *menus_texture_img = stbi_load(MENUS_FILENAME, &menus_width, &menus_height, &menus_channels, 0);
    if(menus_texture_img == NULL) {
        printf("error in loading boss_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", MENUS_FILENAME, menus_width, menus_height, menus_channels);
    if (menus_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, menus_width, menus_height, 0, GL_RGB, GL_UNSIGNED_BYTE, menus_texture_img);
    } else if (menus_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, menus_width, menus_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, menus_texture_img);
    }
    stbi_image_free(menus_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!main_menu_start - end

    //!main_menu_exit - start
    glBindTexture(GL_TEXTURE_2D, textures[12]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int menue_width = 0, menue_height = 0, menue_channels = 0;
    unsigned char *menue_texture_img = stbi_load(MENUE_FILENAME, &menue_width, &menue_height, &menue_channels, 0);
    if(menue_texture_img == NULL) {
        printf("error in loading boss_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", MENUE_FILENAME, menue_width, menue_height, menue_channels);
    if (menue_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, menue_width, menue_height, 0, GL_RGB, GL_UNSIGNED_BYTE, menue_texture_img);
    } else if (menue_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, menue_width, menue_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, menue_texture_img);
    }
    stbi_image_free(menue_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!main_menu_exit - end

    //!objects initialization
    main_menu.option = 1;
}

void init_game() {
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

    //!backgorund_1heart - start
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int bgr1_width = 0, bgr1_height = 0, bgr1_channels = 0;
    unsigned char *bgr1_texture_img = stbi_load(BGR1_FILENAME, &bgr1_width, &bgr1_height, &bgr1_channels, 0);
    if(bgr1_texture_img == NULL) {
        printf("error in loading bgr1_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BGR1_FILENAME, bgr1_width, bgr1_height, bgr1_channels);
    if (bgr1_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bgr1_width, bgr1_height, 0, GL_RGB, GL_UNSIGNED_BYTE, bgr1_texture_img);
    } else if (bgr1_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgr1_width, bgr1_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bgr1_texture_img);
    }
    stbi_image_free(bgr1_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!background_1heart - end

    //!backgorund_2heart - start
    glBindTexture(GL_TEXTURE_2D, textures[8]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int bgr2_width = 0, bgr2_height = 0, bgr2_channels = 0;
    unsigned char *bgr2_texture_img = stbi_load(BGR2_FILENAME, &bgr2_width, &bgr2_height, &bgr2_channels, 0);
    if(bgr2_texture_img == NULL) {
        printf("error in loading bgr2_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BGR1_FILENAME, bgr2_width, bgr2_height, bgr2_channels);
    if (bgr2_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bgr2_width, bgr2_height, 0, GL_RGB, GL_UNSIGNED_BYTE, bgr2_texture_img);
    } else if (bgr2_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgr2_width, bgr2_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bgr2_texture_img);
    }
    stbi_image_free(bgr2_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!background_2heart - end

    //!backgorund_3heart - start
    glBindTexture(GL_TEXTURE_2D, textures[9]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int bgr3_width = 0, bgr3_height = 0, bgr3_channels = 0;
    unsigned char *bgr3_texture_img = stbi_load(BGR3_FILENAME, &bgr3_width, &bgr3_height, &bgr3_channels, 0);
    if(bgr3_texture_img == NULL) {
        printf("error in loading bgr3_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BGR3_FILENAME, bgr3_width, bgr3_height, bgr3_channels);
    if (bgr3_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bgr3_width, bgr3_height, 0, GL_RGB, GL_UNSIGNED_BYTE, bgr3_texture_img);
    } else if (bgr3_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgr3_width, bgr3_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bgr3_texture_img);
    }
    stbi_image_free(bgr3_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!background_3heart - end

    //!backgorund_0heart - start
    glBindTexture(GL_TEXTURE_2D, textures[10]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int bgr0_width = 0, bgr0_height = 0, bgr0_channels = 0;
    unsigned char *bgr0_texture_img = stbi_load(BGR0_FILENAME, &bgr0_width, &bgr0_height, &bgr0_channels, 0);
    if(bgr0_texture_img == NULL) {
        printf("error in loading bgr0_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", BGR0_FILENAME, bgr0_width, bgr0_height, bgr0_channels);
    if (bgr0_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bgr0_width, bgr0_height, 0, GL_RGB, GL_UNSIGNED_BYTE, bgr0_texture_img);
    } else if (bgr0_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgr0_width, bgr0_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bgr0_texture_img);
    }
    stbi_image_free(bgr0_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!background_0heart - end

    //!heart_texture - start
    glBindTexture(GL_TEXTURE_2D, textures[13]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int heart_width = 0, heart_height = 0, heart_channels = 0;
    unsigned char *heart_texture_img = stbi_load(HEART_FILENAME, &heart_width, &heart_height, &heart_channels, 0);
    if(heart_texture_img == NULL) {
        printf("error in loading heart_texture_img\n");
        // exit(1);
    }
    printf("%s - %dx%d with %d channels\n", HEART_FILENAME, heart_width, heart_height, heart_channels);
    if (heart_channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, heart_width, heart_height, 0, GL_RGB, GL_UNSIGNED_BYTE, heart_texture_img);
    } else if (heart_channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, heart_width, heart_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, heart_texture_img);
    }
    stbi_image_free(heart_texture_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //!heart_texture - end

    //!objects initialization
    player.currentLevel = PLAYER_START_LEVEL;
    player.playerSize = PLAYER_SIZE;
    player.playerY = WINDOW_HEIGHT / 2;
    player.playerX = player.playerSize;
    player.playerScore = PLAYER_SCORE;
    player.playerLives = PLAYER_LIVES;
    player.godMode = false;

    boss.bossLives = BOSS_LIVES;
    boss.bossSize = BOSS_SIZE;
    boss.bossY = WINDOW_HEIGHT / 2;
    boss.bossX = WINDOW_WIDTH - boss.bossSize * 2;

    heart.heartSize = HEART_SIZE;
    heart.spawn = true;
    heart.heartX = WINDOW_WIDTH - heart.heartSize;
    heart.heartY = -heart.heartSize;
    heart.heartSpeed = HEART_SPEED;

    boss.reached_top = true;
    boss.reached_bot = false;

    init_random_pool();
}