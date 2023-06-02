#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <ctype.h>
#include "FPToolkit.c"
// for isspace

// Global

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

complex sccmx()
// scan complex number
{
  double rp, ip;
  complex c;
  scanf("%lf %lf", &rp, &ip);
  c = rp + ip * I;
  return c;
}

// How to check if something converges or diverges?

double find_converges()
{
  double n = 0;
  double z = 0;
  double c = 1.0;
  while (n < 100.0)
  {
    z = cpow(z, 2) + c;
    n++;
    if (fabs(z) > 2)
    {
      printf("%s \n", "This diverges");
    }
    else
    {

      printf("%s \n", "This Converges");
    }
    // printf("%lf \n", z);
  }
}

int main()
{

  int swidth, sheight;

  swidth = 800;
  sheight = 800;
  G_init_graphics(swidth, sheight);
  G_rgb(0.0, 0.0, 0.0); // Black
  find_converges();

  complex a, b, c, d, e, f, g, h;
  double z;

  a = 3 + 4 * I;
  b = 2 + 3 * I;
  c = a + b;
  d = a - b;
  e = a * b;
  f = a / b;
  g = csqrt(a);
  h = cpow(a, 2);
  z = cabs(a);

  printf("a         = ");
  prcmx("%20.16lf", a);
  printf("\n");
  printf("b         = ");
  prcmx("%20.16lf", b);
  printf("\n");
  printf("a + b     = ");
  prcmx("%20.16lf", c);
  printf("\n");
  printf("a - b     = ");
  prcmx("%20.16lf", d);
  printf("\n");
  printf("a * b     = ");
  prcmx("%20.16lf", e);
  printf("\n");
  printf("a / b     = ");
  prcmx("%20.16lf", f);
  printf("\n");
  printf("csqrt(a)  = ");
  prcmx("%20.16lf", g);
  printf("\n");
  printf("cpow(a,2) = ");
  prcmx("%20.16lf", h);
  printf("\n");
  printf("cabs(a)   = %20.16lf\n", z);

  complex m;
  printf("input real part and then imaginary part of a complex number ");
  m = sccmx();
  printf("m        = ");
  prcmx("%lf", m);
  printf("\n");
  printf("csin(m)  = ");
  prcmx("%.16e", csin(m));
  printf("\n");
}
