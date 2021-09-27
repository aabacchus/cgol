/*
 * Copyright (c) 2021 Ben Fuller
 */
#include "cgol.h"

#ifndef __TEST
#define NROWS 20
#define NCOLS 20
#else
#define NROWS 10
#define NCOLS 10
#endif

int
main(void) {
    int n_gens = 200;
    struct imgdata img = {
        400, 400,
        NROWS, NCOLS,
        { 1, 1, 1, },
        { 0.1, 0.1, 0.1 },
        { 0, 0, 0 }
    };
#ifndef __TEST
    short cells[NROWS][NCOLS] = { 0 };

    randomize(&cells[0][0], NCOLS, NROWS);
#else
    short cells[NROWS][NCOLS] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    int x, y;
    x = 1;
    y = 2;
    printf("%d,%d = %hd and has %d neighbours\n", x, y, cells[y][x], neighbours(x, y, &cells[0][0], NCOLS, NROWS));
#endif

    int gen, n_alive;
    char *fn = malloc(12 + 4);
    for (gen = 0; gen < n_gens; gen++) {
#ifdef __TEST
        printf("==> GEN %d <==\n", gen);
#endif
        sprintf(fn, "images/%04d.png", gen);
        if (png(&img, &cells[0][0], fn) != 0) {
            free(fn);
            return 1;
        }
        n_alive = evolve(&cells[0][0], NCOLS, NROWS);
#ifndef __TEST
        printf("%d\n", n_alive);
#endif
    }
    free(fn);

    return 0;

}

void
randomize(short *cells, int nx, int ny) {
    srand(time(NULL));
    int i, j;
    for (i = 0; i < ny; i++)
        for (j = 0; j < nx; j++)
            *(cells + i * nx + j) = rand() % 2 ? 1 : 0;
}
