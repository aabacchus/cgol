#include <cairo.h>
#include <stdio.h>

struct rgb {
    double r, g, b;
};

struct imgdata {
    double width, height;
    int ny, nx;           /* number of columns and rows */
    struct rgb a, i, b;   /* RGB for active, inactive, background pixels */
};

/* cells[i][j] should match i = img->ny, j = img->nx */
int png(struct imgdata *img, short *cells, char *fname);
