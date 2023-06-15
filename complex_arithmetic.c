#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "FPToolkit.c"

#define Wsize 800

void draw(double rcen, double icen, double rad, double cutoff, int mlimit)
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

      double r, g, b;
      if (reps == mlimit)
      {
        // Inside the set
        r = g = b = 0;
      }
      else
      {
        // Outside the set, color based is determined by the number of iterations
        double t = (double)reps / mlimit; // Normalized iteration count.

        if (t < 1.0 / 6.0)
        {
          // Black to Red
          r = t * 6.0;
          g = 0;
          b = 0;
        }
        else if (t < 1.0 / 3.0)
        {
          // Red to Yellow
          r = 1;
          g = (t - 1.0 / 6.0) * 6.0;
          b = 0;
        }
        else if (t < 0.5)
        {
          // Yellow to Green
          r = 1 - (t - 1.0 / 3.0) * 6.0;
          g = 1;
          b = 0;
        }
        else if (t < 2.0 / 3.0)
        {
          // Green to Cyan(similar?)
          r = 0;
          g = 1;
          b = (t - 0.5) * 6.0;
        }
        else if (t < 5.0 / 6.0)
        {
          // Cyan to blue
          r = 0;
          g = 1 - (t - 2.0 / 3.0) * 6.0;
          b = 1;
        }
        else
        {
          // Blue to purple transition.
          r = (t - 5.0 / 6.0) * 6.0;
          g = 0;
          b = 1;
        }
      }

      G_rgb(r, g, b);
      G_point(xp, yp);
      x = x + delta;
    }
    y = y + delta;
  }
}

int main()
{
  double rcen = -0.5;
  double icen = 0.0;
  double rad = 2.0;
  double cutoff = 100.0;
  int mlimit = 100;
  double p[2], q[2]; // For clicking

  G_init_graphics(Wsize, Wsize);
  G_rgb(0.0, 0.0, 0.0);
  G_clear();

  while (1)
  {
    draw(rcen, icen, rad, cutoff, mlimit);
    G_display_image();

    // Get the coordinates of the two clicked points
    G_wait_click(p);
    G_wait_click(q);
    // Recalculate the center and radius for zooming each time
    rcen = rcen - rad + (p[0] + q[0]) * rad / Wsize;
    icen = icen - rad + (p[1] + q[1]) * rad / Wsize;
    rad = rad * fabs(p[0] - q[0]) / Wsize;

    G_rgb(0.0, 0.0, 0.0);
    G_clear();
  }

  return 0;
}
