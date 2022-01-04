#include <stdio.h>
#include <time.h>
#include "cgol.h"

#define ESC_CLEAR   "\033[2J"
#define ESC_HOME    "\033[H"
#define ESC_SAVE    "\033[s"
#define ESC_RESTORE "\033[u"

#define ALIVE_CHAR '#'

int
png(struct imgdata *img, short *cells, char *fn) {
    (void)fn;
    int nx, ny;
    nx = img->nx;
    ny = img->ny;

    printf(ESC_CLEAR ESC_HOME);
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            printf("%c", *(cells + j * nx + i) ? ALIVE_CHAR : ' ');
        }
        puts("");
    }

    const struct timespec req = {
        0, 200000000 /* 0.2 s */
    };
    nanosleep(&req, NULL);

    return 0;
}
