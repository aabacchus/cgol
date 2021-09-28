#include "cgol.h"

#define WHATS_OUTSIDE 0

int
evolve(short *cells, int nx, int ny) {
    int i, j;
    int n_alive;
    short newcells[ny][nx];
    n_alive = 0;
    for (i = 0; i < ny; i++) {
        for (j = 0; j < nx; j++) {
            int n = neighbours(j, i, cells, nx, ny);
            int isalive = alive(j, i, cells, nx, ny);
#ifdef __TEST_VERBOSE
            if (n) {
                printf("%d,%d is %d and has %d neighbours\n", j, i, isalive, n);
                verbose_neighbours(j, i, cells, nx, ny);
            }
#endif
            if (isalive && (n == 2 || n == 3)) {
                newcells[i][j] = 1;
                n_alive++;
                continue;
            } else if (!isalive && n == 3) {
                newcells[i][j] = 1;
                n_alive++;
            } else {
                newcells[i][j] = 0;
            }
        }
    }

    for (i = 0; i < ny; i++)
        for (j = 0; j < nx; j++)
            *(cells + i * nx + j) = newcells[i][j];

    return n_alive;
}

int
alive(int x, int y, short *cells, int nx, int ny) {
    if (y < 0)
        y += ny;
    else if (y >= ny)
        y -= ny;
    if (x < 0)
        x += nx;
    else if (x >= nx)
        x -= nx;
    return (int) *(cells + y * nx + x);
}

int
neighbours(int x, int y, short *cells, int nx, int ny) {
    int n = 0;
    int x0, y0;
    for (y0 = y - 1; y0 <= y + 1; y0++) {
        for (x0 = x - 1; x0 <= x + 1; x0++) {
            if (alive(x0, y0, cells, nx, ny))
                n++;
        }
    }
    if (alive(x, y, cells, nx, ny))
        n--;

    return n;
}

#ifdef __TEST_VERBOSE
int
verbose_neighbours(int x, int y, short *cells, int nx, int ny) {
    int n = 0;
    int x0, y0;
    for (y0 = y - 1; y0 <= y + 1; y0++) {
        if (y0 < 0 || y0 >= ny) {
            n += WHATS_OUTSIDE;
            continue;
        }
        for (x0 = x - 1; x0 <= x + 1; x0++) {
            if (x0 < 0 || x0 >= nx) {
                n += WHATS_OUTSIDE;
                continue;
            }
            if (alive(x0, y0, cells, nx, ny)) {
                printf("%d,%d: %d,%d found\n", x, y, x0, y0);
                n++;
            }
        }
    }
    if (alive(x, y, cells, nx, ny))
        n--;

    printf("found %d neighbours\n", n);

    return n;
}
#endif
