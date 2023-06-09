#include "FPToolkit.c"
#include <math.h>

// Globals
double point[2];
int swidth = 750;
int sheight = 750;

double random_num()
{
    double n;      // Random n
    n = drand48(); // Generate
    return n;
}

void scale(double scale_x, double scale_y)
{
    point[0] = point[0] * scale_x;
    point[1] = point[1] * scale_y;
}

void translate(double scale_x, double scale_y)
{
    point[0] = point[0] + scale_x;
    point[1] = point[1] + scale_y;
}

void harmonograph_rule(double random)
{
    double a1 = 1.0 + random * 1.5;   // Amplitude 1
    double a2 = 1.0 + random * 1.5;   // Amplitude 2
    double f1 = 1.0 + random * 1.5;   // Frequency 1
    double f2 = 1.0 + random * 5.5;   // Frequency 2
    double p1 = random * 10.0 * M_PI; // Phase offset 1
    double p2 = random * 1.0 * M_PI;  // Phase offset 2
    double t = random * 30.0 * M_PI;  // Time parameter

    double x = a1 * sin(f1 * t + p1) + a2 * sin(f2 * t + p2);
    double y = a1 * cos(f1 * t + p1) + a2 * cos(f2 * t + p2);

    point[0] = x;
    point[1] = y;
}

int main()
{
    // must do this before you do 'almost' any other graphical tasks
    G_init_graphics(swidth, sheight); // interactive graphics
    G_rgb(0.0, 0.0, 0.0);             // black background
    G_clear();

    double random = 0.0;
    point[0] = random_num();
    point[1] = random_num();

    // Loop the function a few times
    for (int i = 0; i < 5000000; i++) // Adjust the number of iterations as desired
    {
        random = random_num();
        harmonograph_rule(random);

        // Set color for the supernova
        double hue = random * 0.1 + 0.8; // Purple and orange range
        double saturation = random * 0.6 + 0.4;
        double value = random * 0.6 + 0.4;
        G_rgb(hue, saturation, value);

        // Adjust the scaling and translation factors as desired
        double scale_x = 0.08;
        double scale_y = 0.08;

        double translate_x = 0.5;
        double translate_y = 0.5;

        double x = point[0] * scale_x + translate_x;
        double y = point[1] * scale_y + translate_y;

        G_point(x * swidth, y * sheight);
    }

    // clear the screen in a given color
    int key;
    key = G_wait_key(); // pause so the user can see the results
    G_save_to_bmp_file("IFS_final_zoom3.bmp");
}
