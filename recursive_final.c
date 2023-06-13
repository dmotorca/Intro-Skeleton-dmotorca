#include "FPToolkit.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void level_draw(int depth)
{
    if (depth == 0)
    {
        G_rgb(1.0, 1.0, 0.0); // Yellow
    }
    else if (depth == 1)
    {
        G_rgb(1.0, 0.0, 0.0); // Red
    }
    else if (depth == 2)
    {
        G_rgb(0.0, 1.0, 0.0); // Green
    }
    else if (depth == 3)
    {
        G_rgb(0.0, 0.0, 1.0); // Blue
    }
    else if (depth == 4)
    {
        G_rgb(1.0, 0.0, 1.0); // Magenta
    }
    else if (depth == 5)
    {
        G_rgb(0.0, 1.0, 1.0); // Cyan
    }
}

void draw(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, int depth)
{
    level_draw(depth);
    G_triangle(x_1, y_1, x_2, y_2, x_3, y_3);
}

void build_triangle(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, int depth)
{
    if (depth == 0)
    {
        draw(x_1, y_1, x_2, y_2, x_3, y_3, depth);
    }
    else
    {
        double x1_2 = (x_1 + x_2) / 2;
        double y1_2 = (y_1 + y_2) / 2;
        double x2_3 = (x_2 + x_3) / 2;
        double y2_3 = (y_2 + y_3) / 2;
        double x3_1 = (x_3 + x_1) / 2;
        double y3_1 = (y_3 + y_1) / 2;

        build_triangle(x_1, y_1, x1_2, y1_2, x3_1, y3_1, depth - 1);
        build_triangle(x_2, y_2, x1_2, y1_2, x2_3, y2_3, depth - 1);
        build_triangle(x_3, y_3, x2_3, y2_3, x3_1, y3_1, depth - 1);

        draw(x_1, y_1, x1_2, y1_2, x3_1, y3_1, depth);
        draw(x1_2, y1_2, x_2, y_2, x2_3, y2_3, depth);
        draw(x3_1, y3_1, x2_3, y2_3, x_3, y_3, depth);
    }
}

int main()
{
    int swidth = 750;
    int sheight = 750;

    // Sierpinski's Triangle
    double x_1 = 0.0;
    double y_1 = sheight / 2.0;
    double x_2 = swidth / 2.0;
    double y_2 = sheight / 2.0 - swidth / 4.0 * sqrt(3.0);
    double x_3 = swidth;
    double y_3 = sheight / 2.0;

    G_init_graphics(swidth, sheight);
    G_rgb(0.0, 0.0, 0.0);
    G_clear();

    build_triangle(x_1, y_1, x_2, y_2, x_3, y_3, 6);

    // Upper Sierpinski's Triangle
    build_triangle(x_1, y_1, x_2, y_1 - (y_2 - y_1), x_3, y_1, 6);

    // Lower Sierpinski's Triangle
    build_triangle(x_1, y_1, x_2, y_1 + (y_1 - y_2), x_3, y_1, 6);

    int key = G_wait_key();
    G_save_to_bmp_file("demo.bmp");

    return 0;
}
