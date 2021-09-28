/*
 * image.c
 * Copyright (c) 2021 Ben Fuller
 */
#include <cairo.h>
#include <stdio.h>
#include "cgol.h"

/* cells[i][j]; i = img->ny; j = img->nx */
int
png(struct imgdata *img, short *cells, char *fname)
{
    double width, height, scale;
    int nx, ny;
    cairo_surface_t *surface;
    cairo_t *cr;
    scale = 1;

    width = img->width;
    height = img->height;
    nx = img->nx;
    ny = img->ny;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);
    cairo_scale(cr, scale, scale);

    /* background fill */
    cairo_set_source_rgb(cr, img->b.r, img->b.g, img->b.b);
    cairo_rectangle(cr, 0, 0, width/scale, height/scale);
    cairo_fill(cr);

    for (int i = 0; i < ny; i++) {
        for (int j = 0; j < nx; j++) {
            if (*(cells + i * nx + j))
                cairo_set_source_rgb(cr, img->a.r, img->a.g, img->a.b);
            else
                cairo_set_source_rgb(cr, img->i.r, img->i.g, img->i.b);
            cairo_rectangle(cr, j * width/nx/scale, i * height/ny/scale,
                    width/nx/scale * 0.9,
                    height/ny/scale * 0.9);
            cairo_fill(cr);
        }
    }
    cairo_status_t crs;
    crs = cairo_status(cr);
    if (crs != CAIRO_STATUS_SUCCESS) {
        fprintf(stderr, "cairo: %s\n", cairo_status_to_string(crs));
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
        return 1;
    }

    /* Write output and clean up */
    cairo_surface_write_to_png(surface, fname);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}
