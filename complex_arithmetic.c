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

      if (reps == mlimit)
      {
        // Purple color
        double r = 0.6;
        double g = 0.0;
        double b = 0.8;
        G_rgb(r, g, b);
      }
      else
      {
        // Orange color
        double r = 1.0;
        double g = 0.5;
        double b = 0.0;
        G_rgb(r, g, b);
      }

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

  G_init_graphics(Wsize, Wsize);
  G_rgb(0.0, 0.0, 0.0);
  G_clear();

  draw(rcen, icen, rad, cutoff, mlimit);

  G_display_image();
  G_wait_key();

  return 0;
}
