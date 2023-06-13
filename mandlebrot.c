#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <ctype.h>
#include "FPToolkit.c"

#define WIDTH 800
#define HEIGHT 800
#define MAX_ITERATIONS 100

void plot(int x, int y, double r, double g, double b)
{
    G_rgb(r, g, b);
    G_point(x, y);
}

void draw(double x_min, double x_max, double y_min, double y_max, int max_iterations)
{
    double dx = (x_max - x_min) / WIDTH;
    double dy = (y_max - y_min) / HEIGHT;

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            double x0 = x_min + i * dx;
            double y0 = y_min + j * dy;

            complex z = 0;
            complex c = x0 + y0 * I;

            int iteration = 0;
            while (cabs(z) < 2 && iteration < max_iterations)
            {
                z = (z * z) + c;
                iteration++;
            }

            // Color the pixel based on the iteration count
            if (iteration == max_iterations)
            {
                plot(i, j, 0.0, 0.0, 0.0); // Black for points in the set
            }
            else
            {
                double t = (double)iteration / max_iterations;
                double r = sin(2 * M_PI * t);
                double g = sin(2 * M_PI * (t + 1.0 / 3.0));
                double b = sin(2 * M_PI * (t + 2.0 / 3.0));
                plot(i, j, r, g, b);
            }
        }
    }
}

int main()
{
    double x_min = -2.0;
    double x_max = 1.0;
    double y_min = -1.5;
    double y_max = 1.5;

    int mlimit = 256;
    G_init_graphics(WIDTH, HEIGHT);
    G_rgb(0.0, 0.0, 0.0); // Black background

    for (double zoom = 1.0; zoom > 1e-6; zoom *= 0.95)
    {
        double x_center = (x_min + x_max) / 2.0;
        double y_center = (y_min + y_max) / 2.0;
        double x_range = (x_max - x_min) / 2.0 * zoom;
        double y_range = (y_max - y_min) / 2.0 * zoom;

        double new_x_min = x_center - x_range;
        double new_x_max = x_center + x_range;
        double new_y_min = y_center - y_range;
        double new_y_max = y_center + y_range;

        draw(new_x_min, new_x_max, new_y_min, new_y_max, mlimit);

        G_display_image();
        G_wait_key();
        G_rgb(0.0, 0.0, 0.0); // Clear the screen

        // Save each frame as a BMP image
        char filename[100];
        sprintf(filename, "mandelbrot%d.bmp", (int)(1.0 / zoom));
        G_save_to_bmp_file(filename);
    }
}
