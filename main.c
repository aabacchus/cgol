/*
 * Copyright (c) 2021 Ben Fuller
 */
#include "cgol.h"
#include <errno.h>
#include <string.h>
#include <limits.h>

#ifndef __TEST
#define NROWS 20
#define NCOLS 20
#else
#define NROWS 10
#define NCOLS 10
#endif

/* check errno and the result of ato* for an error */
void
check(int res) {
    if (res == 0 && errno != 0) {
        fprintf(stderr, "bad argument\n");
        fprintf(stderr, "usage: cgol [width height [gens]]\nthe defaults are \"800\" \"600\" \"200\"\n");
        exit(1);
    }
    errno = 0;
}


int
main(int argc, char **argv) {
    double width, height;
    int gens;

    if (argc > 1 && strncmp("-h", *(argv + 1), 2) == 0) {
        fprintf(stderr, "usage: %s [width height [gens]]\nthe defaults are \"800\" \"600\" \"200\"\n", *argv);
        return 1;
    }
    if (argc > 2) {
        errno = 0;
        width = atof(*++argv);
        check(width);
        height = atof(*++argv);
        check(height);
        if (argc > 3) {
            gens = atoi(*++argv);
            check(gens);
            if (gens < 1 || gens > 999999) {
                /* the upper limit is to ensure the gen number fits onto the
                 * image filenames */
                fprintf(stderr, "bad gens arg\n");
                return 1;
            }
        } else
            gens = 200;
    } else {
        width = 800;
        height = 600;
        gens = 200;
    }

    struct imgdata img = {
        width, height,
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
        { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
#endif

    int gen, n_alive;
    char *fn = malloc(12 + 6);
    for (gen = 0; gen < gens; gen++) {
#ifdef __TEST
        printf("==> GEN %d <==\r", gen);
#endif

        /* %06d because gens <= 999999 */
        sprintf(fn, "images/%06d.png", gen);
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
#ifdef __TEST
    puts("");
#endif

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
