#include "FPToolkit.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
        G_rgb(1.0, 0.5, 0.0); // Orange
    }
    else if (depth == 5)
    {
        G_rgb(0.5, 0.0, 1.0); // Purple
    }
}
void draw(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, int depth)
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
void draw_koch(double x_1, double y_1, double x_2, double y_2, int depth)
{
    level_draw(depth);
    G_line(x_1, y_1, x_2, y_2);
}

void koch_snowflake(double x1, double y1, double x5, double y5, int depth)
{
    if (depth == 0)
    {
        draw(x1, y1, x5, y5, depth);
    }
    else
    {
        double deltaX = x5 - x1;
        double deltaY = y5 - y1;

        double x2 = x1 + deltaX / 3.0;
        double y2 = y1 + deltaY / 3.0;

        double x3 = 0.5 * (x1 + x5) + sqrt(3.0) * (y1 - y5) / 6.0;
        double y3 = 0.5 * (y1 + y5) + sqrt(3.0) * (x5 - x1) / 6.0;

        double x4 = x1 + 2.0 * deltaX / 3.0;
        double y4 = y1 + 2.0 * deltaY / 3.0;

        koch_snowflake(x1, y1, x2, y2, depth - 1);
        koch_snowflake(x2, y2, x3, y3, depth - 1);
        koch_snowflake(x3, y3, x4, y4, depth - 1);
        koch_snowflake(x4, y4, x5, y5, depth - 1);
    }
}

int main()
{
    int swidth = 800;
    int sheight = 800;

    // Serpinskis Triangle
    double x_1 = 0.0;
    double y_1 = 100.0;
    double x_2 = 799.0;
    double y_2 = 100.0;
    double x_3 = 400.0;
    double y_3 = 600.0;

    // Koch Curve
    double x = 400.0;
    double y = 400.0;
    double length = 600.0;

    G_init_graphics(swidth, sheight);
    G_rgb(0.0, 0.0, 0.0);
    G_clear();

    koch_snowflake(x, y, length, 4);
    // build_triangle(x_1, y_1, x_2, y_2, x_3, y_3, 6);

    int key = G_wait_key();
    G_save_to_bmp_file("demo.bmp");

    return 0;
}
