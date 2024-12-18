#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <stdio.h>

#include "constants.h"
#include "extern_pointers.h"

void init_random_pool() {
    srand(time(NULL));
    random_pool = (int*) malloc(RAND_POOL_SIZE * sizeof(int));
    for (int i = 0; i < RAND_POOL_SIZE; i++) {
        random_pool[i] = rand();
    }
}

int get_random_number() {
    int num = random_pool[random_index];
    random_index = (random_index+1) % RAND_POOL_SIZE;
    return num;
}