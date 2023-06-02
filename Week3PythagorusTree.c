/*
    FPToolkit.c : A simple set of graphical tools.
    PythagorasTree.c
    Copyright (C) 2023  ChatGPT

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "FPToolkit.c"
#include <math.h>

void draw_tree(double x, double y, double size, double angle, int depth, double r, double g, double b)
{
    // draw a rectangle
    G_rgb(r, g, b);
    G_fill_rectangle(x - size / 2.0, y - size / 2.0, size, size);

    if (depth == 0)
    {
        return;
    }

    // calculate coordinates of the next rectangle
    double x2 = x + (size / 2.0) * cos(angle * M_PI / 180.0);
    double y2 = y + (size / 2.0) * sin(angle * M_PI / 180.0);

    // calculate sizes of the next rectangles
    double size1 = size / sqrt(2.0);
    double size2 = size1 * sin(45);

    // calculate angles of the next rectangles
    double angle1 = angle - 45.0;
    double angle2 = angle + 45.0;

    // draw two trees recursively
    draw_tree(x2, y2, size1, angle1, depth - 1, r + 0.01, g - 0.01, b + 0.01);

    draw_tree(x2, y2, size2, angle2, depth - 1, r - 0.01, g + 0.01, b + 0.01);
}

int main()
{
    int swidth = 600, sheight = 600;
    G_init_graphics(swidth, sheight);

    // clear the screen
    G_rgb(1.0, 1.0, 1.0);
    G_clear();

    // set the origin to the middle of the screen
    G_rgb(0.0, 0.0, 0.0);
    G_line(0, sheight / 2, swidth, sheight / 2);
    G_line(swidth / 2, 0, swidth / 2, sheight);

    // draw the tree recursively
    double x = swidth / 2.0, y = sheight / 2.0;
    double size = 200.0, angle = -90.0;
    int depth = 12;
    draw_tree(x, y, size, angle, depth, 0.0, 0.0, 0.0);

    G_wait_key();
    return 0;
}
