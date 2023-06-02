
/*
    FPToolkit.c : A simple set of graphical tools.
    FPToolkitDemo.c
    Copyright (C) 2018  Ely

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

/*

This code assumes an underlying X11 environment.

       Most freshly installed unbuntu environments do not have
       the X11 developr stuff they'll need to do graphics.
       To download X11 developer stuff, connect to the internet and
       issue the following two commands.  Each will ask for your password
       and each will take a few minutes.  At some point it might even
       look like nothing is happening....be patient :

sudo  apt-get  install  libx11-dev

sudo  apt-get  install  xorg-dev

*/

/*
If this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,
do the following :

cc  FPToolkitDemoB.c   -lm  -lX11

note : the 'X' in -X11 is capitalized
*/

#include "FPToolkit.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Hard code

void draw(x_1, y_1, x_2, y_2, x_3, y_3)
{

    // G_rgb(color_1 / 2, color_2 / 2, color_3 / 2);
    G_triangle(x_1, y_1, x_2, y_2, x_3, y_3);
}

double depth = 0.0;

void build_triangle(x_1, y_1, x_2, y_2, x_3, y_3, depth)
{

    double color1 = 0.0;
    double color2 = 0.0;
    double color3 = 0.0;
    color1 = (float)rand() / RAND_MAX;
    color2 = (float)rand() / RAND_MAX;
    color3 = (float)rand() / RAND_MAX;

    // printf("Random number between 0.0 and 1.0: %f\n", color1);

    G_rgb(color1, color2, color3);

    // input == depth
    if (depth == 0)
    {

        // G_rgb(0.0, 1.0, 0.0);
        draw(x_1, y_1, x_2, y_2, x_3, y_3);
    }
    else
    {
        // Calculating Midpoints
        double x1_2 = (x_1 + x_2) / 2;
        double y1_2 = (y_1 + y_2) / 2;
        double x2_3 = (x_2 + x_3) / 2;
        double y2_3 = (y_2 + y_3) / 2;
        double x3_1 = (x_3 + x_1) / 2;
        double y3_1 = (y_3 + y_1) / 2;

        // G_rgb(color_1 / 2, color_2 / 2, color_3 / 2);
        //  G_rgb(1.0, 0.6, 0.0); // yellow

        build_triangle(x_1, y_1, x1_2, y1_2, x3_1, y3_1, depth - 1);
        build_triangle(x_2, y_2, x1_2, y1_2, x2_3, y2_3, depth - 1);
        build_triangle(x_3, y_3, x2_3, y2_3, x3_1, y3_1, depth - 1);
        /*
        printf("Value of x1_2 = %f\n", x1_2);
        printf("Value of y1_2 = %f\n", y1_2);

        printf("Value of x2_3 = %f\n", x2_3);
        printf("Value of y2_3 = %f\n", y2_3);

        printf("Value of x3_1 = %f\n", x3_1);
        printf("Value of y3_1 = %f\n", y3_1);

        G_triangle(x_1, y_1, x1_2, y1_2, x3_1, y3_1);
        G_triangle(x1_2, y1_2, x_2, y_2, x2_3, y2_3);
        G_triangle(x3_1, y3_1, x2_3, y2_3, x_3, y_3);
        */
    }
}

int main()
{
    int swidth, sheight;
    double lowleftx, lowlefty, width, height;
    double x[10], y[10];
    double numxy;
    double a[20], b[20];
    double numab;

    double x_1 = 0.0;
    double y_1 = 100.0;

    double x_2 = 799.0;
    double y_2 = 100.0;

    double x_3 = 400.0;
    double y_3 = 600.0;

    // must do this before you do 'almost' any other graphical tasks
    swidth = 800;
    sheight = 800;
    G_init_graphics(swidth, sheight); // interactive graphics

    // clear the screen in a given color
    G_rgb(0.0, 0.0, 0.0); // black
    G_clear();

    // Build initial triangle
    // Asking for user input for depth

    build_triangle(x_1, y_1, x_2, y_2, x_3, y_3, 6);

    //===============================================

    double p[2],
        q[2];

    int key;
    key = G_wait_key(); // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp");
}
