#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <ctype.h>
#include "FPToolkit.c"
// for isspace

// Global
#define WIDTH 800
#define HEIGHT 800
#define MAX_ITERATIONS 100

double Wsize = 750.0;

// Converge = Pink - 0.8/0.3/1.0
// Diverge = Baby Blue - 0.1/0.9/0.9

void prcmx(char *control, complex c)
// print complex number
{
  double a, b;
  a = creal(c);
  b = cimag(c);

  printf(control, a);
  if (b >= 0)
  {
    printf("+");
  }
  else
  {
    printf("-");
  }
  printf(control, fabs(b));
  printf("I");
}

/*
complex sccmx()
// scan complex number
{
  double rp, ip;
  complex c;
  scanf("%lf %lf", &rp, &ip);
  c = rp + ip * I;
  return c;
}
*/

// How to check if something converges or diverges?

int find_converges()
{
  double n = 0;
  complex z = -1.0 + 0.5 * I;
  complex c = 1.0;

  while (n < 100.0)
  {
    z = cpow(z, 2) + c;
    n++;

    if (cabs(z) > 2)
    {
      return 0; // Diverges
    }
  }

  return 1; // Converges
}
void plot(int x, int y, double r, double g, double b)
{
  G_rgb(r, g, b);
  G_point(x, y);
}

void ely_draw(double rcen, double icen, double rad, double cutoff, int mlimit)
{
  double delta, x, y, yp, xp;
  complex c;
  complex z;
  int reps;

  delta = 2 * rad / Wsize;

  y = icen - rad;
  for (yp = 0; yp < Wsize; yp++)
  {
    x = rcen - rad;
    for (xp = 0; xp < Wsize; xp++)
    {
      c = x + y * I;
      z = 0;
      for (reps = 0; reps < mlimit; reps++)
      {
        if (cabs(z) > cutoff)
        {
          break;
        }
        z = z * z + c;
      }

      if (reps == mlimit)
      {
        G_rgb(0.0, 1.0, 0.0);
      }
      else
      {
        G_rgb(0.0, 0.0, 1.0);
      }

      G_point(xp, yp);
      x = x + delta;
    }
    y = y + delta;
  }
}

void draw(double click_1[2], double click_2[2])
{
  double x_min = -2.5;
  double x_max = 1.0;
  double y_min = -1.5;
  double y_max = 1.5;
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
      while (cabs(z) < 2 && iteration < MAX_ITERATIONS)
      {
        z = (z * z) + c;
        iteration++;
      }
      // Color the pixel based on the number of iterations
      double t = (double)iteration / MAX_ITERATIONS;
      double r = t;
      double g = 0.3 + 0.7 * t;
      double b = 1.0 - t;

      plot(i, j, r, g, b);

      // Zoom portion
    }
  }
}

void zoom(double click_1[2], double click_2[2])
{
  double x_min = click_1[0];
  double x_max = click_2[0];
  double y_min = click_1[1];
  double y_max = click_2[1];

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
      while (cabs(z) < 2 && iteration < MAX_ITERATIONS)
      {
        z = (z * z) + c;
        iteration++;
      }

      // Color the pixel based on the number of iterations
      double t = (double)iteration / MAX_ITERATIONS;
      double r = t;
      double g = 0.3 + 0.7 * t;
      double b = 1.0 - t;

      plot(i, j, r, g, b);
    }
  }
}

int main()
{
  double x[2];
  double y[2];
  int swidth, sheight;

  int mlimit = 256;
  double click_1[2];
  double click_2[2];

  swidth = 750;
  sheight = 750;
  G_init_graphics(swidth, sheight);
  G_rgb(0.0, 0.0, 0.0); // Black background

  // ely_draw(-0.5, 0, 1.8, 2, mlimit); // Initial Mandelbrot set
  draw(click_1, click_2);

  G_wait_click(x);
  G_wait_click(y);

  click_1[0] = x[0]; // First point x
  click_1[1] = x[1]; // First point y

  click_2[0] = y[0]; // Second point x
  click_2[1] = y[1]; // Second point y

  printf("\n %lf, %lf \n", click_1[0], click_1[1]);
  printf("\n %lf, %lf \n", click_2[0], click_2[1]);

  zoom(click_1, click_2); // Perform initial zoom

  G_wait_key();
  G_save_to_bmp_file("mandelbrot.bmp");
}