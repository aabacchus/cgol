/*
 * Copyright (c) 2021 Ben Fuller
 */
#include "cgol.h"

int
main(void) {
    struct imgdata img = {
        200, 200,
        11, 10,
        { 1, 1, 1, },
        { 0.1, 0.1, 0.1 },
        { 0, 0, 0 }
    };
    short cells[11][10] = { 0 };
    if (png(&img, &cells[0][0], "out.png") != 0)
        return 1;
    return 0;
}
