#include "FPToolkit.c"
#include <math.h>

// Globals
double point[2];
int swidth = 766;
int sheight = 766;

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

void rotate(double angle)
{
    double x = point[0];
    double y = point[1];
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);

    point[0] = x * cos_angle - y * sin_angle;
    point[1] = x * sin_angle + y * cos_angle;
}

void square(double random)
{
    if (random < 0.25)
    {
        G_rgb(1.0, 0.0, 0.0);
        scale(0.5, 0.5);
        translate(0.0, 0.0);
    }
    else if (random < 0.5)
    {
        G_rgb(0.0, 1.0, 0.0);
        scale(0.5, 0.5);
        translate(0.5, 0.0);
    }
    else if (random < 0.75)
    {
        G_rgb(0.0, 0.0, 1.0);
        scale(0.5, 0.5);
        translate(0.0, 0.5);
    }
    else
    {
        G_rgb(0.4, 0.3, 0.4);
        scale(0.5, 0.5);
        translate(0.5, 0.5);
    }
}

void carpet(double random)
{
    // Define eight transformations to form the Sierpinski carpet, each with a unique color.
    if (random < 0.125)
    {
        scale(0.3333, 0.3333);
        translate(0.0, 0.0);
        G_rgb(1.0, 0.0, 0.0); // Red
    }
    else if (random < 0.25)
    {
        scale(0.3333, 0.3333);
        translate(0.3333, 0.0);
        G_rgb(0.0, 1.0, 0.0); // Green
    }
    else if (random < 0.375)
    {
        scale(0.3333, 0.3333);
        translate(0.6666, 0.0);
        G_rgb(0.0, 0.0, 1.0); // Blue
    }
    else if (random < 0.5)
    {
        scale(0.3333, 0.3333);
        translate(0.0, 0.3333);
        G_rgb(1.0, 1.0, 0.0); // Yellow
    }
    else if (random < 0.625)
    {
        scale(0.3333, 0.3333);
        translate(0.6666, 0.3333);
        G_rgb(1.0, 0.0, 1.0); // Magenta
    }
    else if (random < 0.75)
    {
        scale(0.3333, 0.3333);
        translate(0.0, 0.6666);
        G_rgb(0.0, 1.0, 1.0); // Cyan
    }
    else if (random < 0.875)
    {
        scale(0.3333, 0.3333);
        translate(0.3333, 0.6666);
        G_rgb(0.5, 0.5, 0.5); // Gray
    }
    else
    {
        scale(0.3333, 0.3333);
        translate(0.6666, 0.6666);
        G_rgb(0.3, 0.3, 0.3); // Dark Gray
    }
}

void D_rule(double random)
{
    if (random < 0.3)
    {
        // Define the straight part of "D"
        scale(0.3, 0.3);
        translate(0.0, 0.0);
        G_rgb(0.0, 1.0, 0.0); // green
    }
    else if (random < 0.6)
    {
        // Define the upper curved part of "D"
        scale(0.3, 0.3);
        translate(0.3, 0.3);
        G_rgb(0.1, 0.5, 0.3); // green
    }
    else
    {
        // Define the lower curved part of "D"
        scale(0.3, 0.3);
        rotate(90);
        translate(0.0, 0.3);
        G_rgb(0.0, 1.0, 0.0); // green
    }
}

void J_rule(double random)
{
    if (random < 0.3)
    {
        // Define the curved part of "J"
        scale(0.5, 0.5);
        translate(0.5, 0.0);
        G_rgb(1.0, 0.0, 0.0); // red
    }
    else
    {
        // Define the straight part of "J"
        scale(0.5, 0.5);
        translate(0.0, 0.5);
        G_rgb(1.0, 0.0, 0.0); // red
    }
}

void M_rule(double random)
{
    if (random < 0.25)
    {
        // Define the left slant of "M"
        scale(0.5, 0.5);
        translate(0.0, 0.0);
        G_rgb(0.0, 0.0, 1.0); // blue
    }
    else if (random < 0.5)
    {
        // Define the right slant of "M"
        scale(0.5, 0.5);
        translate(0.5, 0.0);
        G_rgb(0.0, 0.0, 1.0); // blue
    }
    else if (random < 0.75)
    {
        // Define the left straight part of "M"
        scale(0.5, 0.5);
        translate(0.0, 0.5);
        G_rgb(0.0, 0.0, 1.0); // blue
    }
    else
    {
        // Define the right straight part of "M"
        scale(0.5, 0.5);
        translate(0.5, 0.5);
        G_rgb(0.0, 0.0, 1.0); // blue
    }
}

void leaf(double random)
{
    // Inverse or arctan needed to find degrees/rotation

    // point[0] = x
    // point[1] = y

    if (random < .01)
    {
        // 1st case
        scale(0, 0.16);
        G_rgb(0.5, 0.5, 0.5);
    }
    else if (random < .85)
    {
        // 2nd case
        scale(0, .85);
        G_rgb(0.0, 0.0, 1.0); // blue
    }
    else if (random < .07)
    {
        // 3rd case
        G_rgb(1.0, 0.0, 1.0); // Magenta
    }
    else
    {
        G_rgb(1.0, 1.0, 0.0); // Yellow
        // 4th case
    }
}

int main()
{

    double random = 0.0;
    point[0] = random_num();
    point[1] = random_num();

    // must do this before you do 'almost' any other graphical tasks
    G_init_graphics(swidth, sheight); // interactive graphics
    G_rgb(0.0, 0.0, 0.0);             // dark gray
    G_clear();

    // Loop my function a few times
    for (int i = 0; i < 5000000; i++)
    {
        random = random_num();
        // leaf(random);
        //  carpet(random);
        //   square(random)
        //   ifs_line(random)
        //    Determine which rule to apply based on the position of the point

        if (point[0] < 0.33)
        {
            D_rule(random);
        }
        else if (point[0] < 0.66)
        {
            J_rule(random);
        }
        else
        {
            M_rule(random);
        }
        G_point(point[0] * swidth, point[1] * sheight);

        // Flush output to the screen
    }

    // clear the screen in a given color
    int key;
    key = G_wait_key(); // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp");
}