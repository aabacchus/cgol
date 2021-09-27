/*
 * stroke.c
 * Copyright (c) 2021 Ben Fuller
 *
 * This program makes a PNG image "stroke.png" consisting of blocks of colour
 * in a gradient. The dimensions of the image, and size of <<pixels>> can be
 * easily adjusted - try setting the number of rows and columns to the width
 * and height so that each block is one pixel.
 *
 * Between each pixel is left a small gap, and the background is coloured in
 * black.
 */
#include <cairo.h>
#include <stdio.h>

int
main(void)
{
    double width, height, scale;
    int nx, ny;
    cairo_surface_t *surface;
    cairo_t *cr;

    width = 600;
    height = 600;
    scale = 1;
    /* number of columns and rows */
    nx = 60;
    ny = 60;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);
    cairo_scale(cr, scale, scale);

    /* background fill */
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, width/scale, height/scale);
    cairo_fill(cr);

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            cairo_set_source_rgb(cr,
                    (double)j / ny,
                    (double)i / nx,
                    0);
            cairo_rectangle(cr, i * width/nx/scale, j * height/ny/scale,
                    width/nx/scale * 0.9,
                    height/ny/scale * 0.9);
            cairo_fill(cr);
        }
    }
    printf("cairo_status: %s\n", cairo_status_to_string(cairo_status(cr)));

    /* Write output and clean up */
    cairo_surface_write_to_png(surface, "stroke.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}
