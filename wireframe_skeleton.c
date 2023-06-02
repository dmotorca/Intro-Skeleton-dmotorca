#include "FPToolkit.c"

/*

       Y+
       |
       |    * (y,z)
       |
<------+--------Z+
   D   |
       |
       |


y'    y
- =  ---
D    D+z

H = D*tan(halfangle) ;

with the x-axis perpendicular to this plane.

*/

#define M 700000
double Wsize = 700; // window size ... choose 600 for repl
double X[M], Y[M], Z[M];
double Xplot[M], Yplot[M];
int N = 0;

int translate(double dx, double dy, double dz)
{
  int i;

  for (i = 0; i < N; i++)
  {
    X[i] += dx;
    Y[i] += dy;
    Z[i] += dz;
  }
}

int rotate_x(double degrees)
// Y[] and Z[] will change but X[] will be unchanged
{
  double radians, c, s, temp;
  int i;

  radians = degrees * M_PI / 180;
  c = cos(radians);
  s = sin(radians);
  for (i = 0; i < N; i++)
  {
    temp = c * Y[i] - s * Z[i];
    Z[i] = s * Y[i] + c * Z[i];
    Y[i] = temp;
  }
}

int rotate_y(double degrees)
// X[] and Z[] will change but Y[] will be unchanged
{
  double radians, c, s, temp;
  int i;

  radians = degrees * M_PI / 180;
  c = cos(radians);
  s = sin(radians);
  for (i = 0; i < N; i++)
  {
    temp = c * X[i] + s * Z[i];
    Z[i] = -s * X[i] + c * Z[i];
    X[i] = temp;
  }
}

int rotate_z(double degrees)
// X[] and Y[] will change but Z[] will be unchanged
{
  double radians, c, s, temp;
  int i;

  radians = degrees * M_PI / 180;
  c = cos(radians);
  s = sin(radians);
  for (i = 0; i < N; i++)
  {
    temp = c * X[i] - s * Y[i];
    Y[i] = s * X[i] + c * Y[i];
    X[i] = temp;
  }
}

int project(double observer_distance, double halfangle_degrees)
{
  // 1. Compute H
  double H = observer_distance * tan(halfangle_degrees * M_PI / 180);

  // 3. Apply transformations to X, Y, and Z arrays and map to screen coordinates
  for (int i = 0; i < N; i += 2)
  {
    double projectedY1 = Y[i] / (observer_distance + Z[i]) * H;
    double projectedX1 = X[i] / (observer_distance + Z[i]) * H;

    double projectedY2 = Y[i + 1] / (observer_distance + Z[i + 1]) * H;
    double projectedX2 = X[i + 1] / (observer_distance + Z[i + 1]) * H;

    // Scale
    projectedX1 = projectedX1 * (Wsize / H);
    projectedY1 = projectedY1 * (Wsize / H);

    projectedX2 = projectedX2 * (Wsize / H);
    projectedY2 = projectedY2 * (Wsize / H);

    Xplot[i] = (Wsize / 2) + projectedX1;
    Yplot[i] = (Wsize / 2) + projectedY1;

    Xplot[i + 1] = (Wsize / 2) + projectedX2;
    Yplot[i + 1] = (Wsize / 2) + projectedY2;

    // Yplot[i + 1] = Wsize / 2 + (projectedY2 * observer_distance);
    // Xplot[i + 1] = Wsize / 2 + (projectedX2 * observer_distance);
  }

  return 1;
}

int draw()
{
  int i;
  for (i = 0; i < N; i = i + 2)
  {
    G_line(Xplot[i], Yplot[i], Xplot[i + 1], Yplot[i + 1]);
  }
}

int print_object()
{
  int i;
  for (i = 0; i < N; i = i + 2)
  {
    // i = start , i + 1 = end -> In terms of a line segement
    printf("(%lf, %lf, %lf)   (%lf, %lf, %lf)\n",
           X[i], Y[i], Z[i], X[i + 1], Y[i + 1], Z[i + 1]);
  }

  printf("===============================\n");

  for (i = 0; i < N; i = i + 2)
  {
    printf("(%lf, %lf)   (%lf, %lf)\n",
           Xplot[i], Yplot[i], Xplot[i + 1], Yplot[i + 1]);
  }
}

int save_line(double xs, double ys, double zs,
              double xe, double ye, double ze)
{
  // about to add items at slots N and N+1 :
  if (N + 1 >= M)
  {
    printf("full\n");
    return 0;
  }

  X[N] = xs;
  Y[N] = ys;
  Z[N] = zs;
  N++;
  X[N] = xe;
  Y[N] = ye;
  Z[N] = ze;
  N++;

  return 1;
}

int build_pyramid()
{
  int n, k;
  double a, x[100], z[100], yv;

  N = 0; // global

  n = 4;
  for (k = 0; k <= n; k++)
  {
    a = k * 2 * M_PI / n;
    x[k] = cos(a);
    z[k] = sin(a);
  }

  yv = -1;
  for (k = 0; k < n; k++)
  {
    save_line(0, 2, 0, x[k], yv, z[k]);
    save_line(x[k], yv, z[k], x[k + 1], yv, z[k + 1]);
  }
}

int build_square()
{

  int n, k;
  double a, x[100], z[100], yv;

  N = 0; // global

  n = 4;
  for (k = 0; k <= n; k++)
  {
    a = k * 2 * M_PI / n;
    x[k] = cos(a);
    z[k] = sin(a);
  }

  yv = -1;
  for (k = 0; k < n; k++)
  {

    save_line(x[k], yv, z[k], x[k + 1], yv, z[k + 1]); // Bottom Tile
    save_line(x[k], 1, z[k], x[k + 1], 1, z[k + 1]);   // Top Tile
    save_line(x[k], yv, z[k], x[k], 1, z[k]);          // Lines
  }
}

int test_square()
{
  G_init_graphics(Wsize, Wsize);
  G_rgb(0, 0, 0);
  G_clear();
  G_rgb(0, 1, 0);

  build_square();
  project(5, 45);
  draw();
  print_object();

  G_wait_key();
}

int test_square_rotate()
{
  //  G_choose_repl_display() ; // not too bad as a repl movie
  G_init_graphics(Wsize, Wsize);

  build_square();

  while (1)
  {
    G_rgb(0, 0, 0);
    G_clear();
    G_rgb(0, 1, 0);
    project(5, 45);
    draw();

    int key;
    key = G_wait_key(); // pause so user can see results

    if (key == 'y')
    {
      rotate_y(2);
    }

    if (key == 'x')
    {
      rotate_x(2);
    }

    if (key == 'z')
    {
      rotate_z(2);
    }

    if (G_wait_key() == 'q')
    {
      break;
    }

    else
    {
      rotate_y(2);
    }
  }
}

int test_pyramid()
{

  G_init_graphics(Wsize, Wsize);
  G_rgb(0, 0, 0);
  G_clear();
  G_rgb(0, 1, 0);

  build_pyramid();
  project(45, 45);
  draw();
  print_object();

  G_wait_key();
}

int test_pyramid_rotate()
{
  //  G_choose_repl_display() ; // not too bad as a repl movie
  G_init_graphics(Wsize, Wsize);

  build_pyramid();

  while (1)
  {
    G_rgb(0, 0, 0);
    G_clear();
    G_rgb(0, 1, 0);
    project(5, 45);
    draw();
    rotate_y(2);
    if (G_wait_key() == 'q')
    {
      break;
    }
  }
}

void draw_ser(x_1, y_1, x_2, y_2, x_3, y_3)
{

  // G_rgb(color_1 / 2, color_2 / 2, color_3 / 2);
  G_triangle(x_1, y_1, x_2, y_2, x_3, y_3);
}

double depth = 0.0;

void build_triangle(x_1, y_1, x_2, y_2, x_3, y_3, depth)
{

  double r = 0.0;
  double g = 0.0;
  double b = 0.0;
  r = (float)rand() / RAND_MAX;
  g = (float)rand() / RAND_MAX;
  b = (float)rand() / RAND_MAX;

  // printf("Random number between 0.0 and 1.0: %f\n", color1);

  G_rgb(r, g, b);

  if (depth == 0)
  {

    draw_ser(x_1, y_1, x_2, y_2, x_3, y_3);
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

    build_triangle(x_1, y_1, x1_2, y1_2, x3_1, y3_1, depth - 1);
    build_triangle(x_2, y_2, x1_2, y1_2, x2_3, y2_3, depth - 1);
    build_triangle(x_3, y_3, x2_3, y2_3, x3_1, y3_1, depth - 1);
  }
}

void build_serpinski(double x1, double y1, double z1,
                     double x2, double y2, double z2,
                     double x3, double y3, double z3,
                     double x4, double y4, double z4, int depth)
{
  if (depth == 0)
  {
    save_line(x1, y1, z1, x2, y2, z2);
    save_line(x2, y2, z2, x3, y3, z3);
    save_line(x3, y3, z3, x1, y1, z1);

    save_line(x1, y1, z1, x4, y4, z4);
    save_line(x2, y2, z2, x4, y4, z4);
    save_line(x3, y3, z3, x4, y4, z4);
    return;
  }

  double x12 = (x1 + x2) / 2, y12 = (y1 + y2) / 2, z12 = (z1 + z2) / 2;
  double x13 = (x1 + x3) / 2, y13 = (y1 + y3) / 2, z13 = (z1 + z3) / 2;
  double x14 = (x1 + x4) / 2, y14 = (y1 + y4) / 2, z14 = (z1 + z4) / 2;
  double x23 = (x2 + x3) / 2, y23 = (y2 + y3) / 2, z23 = (z2 + z3) / 2;
  double x24 = (x2 + x4) / 2, y24 = (y2 + y4) / 2, z24 = (z2 + z4) / 2;
  double x34 = (x3 + x4) / 2, y34 = (y3 + y4) / 2, z34 = (z3 + z4) / 2;

  build_serpinski(x1, y1, z1, x12, y12, z12, x13, y13, z13, x14, y14, z14, depth - 1);
  build_serpinski(x12, y12, z12, x2, y2, z2, x23, y23, z23, x24, y24, z24, depth - 1);
  build_serpinski(x13, y13, z13, x23, y23, z23, x3, y3, z3, x34, y34, z34, depth - 1);
  build_serpinski(x14, y14, z14, x24, y24, z24, x34, y34, z34, x4, y4, z4, depth - 1);
}

int test_serpinski()
{

  G_init_graphics(Wsize, Wsize);
  G_rgb(0, 0, 0);
  G_clear();
  G_rgb(0, 1, 0);

  double x1 = -1.0, y1 = -1.0, z1 = -1.0;
  double x2 = 1.0, y2 = -1.0, z2 = -1.0;
  double x3 = 0.0, y3 = 1.0, z3 = -1.0;
  double x4 = 0.0, y4 = 0.0, z4 = 1.0;

  int depth = 3;

  build_serpinski(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, depth);

  project(5, 45);
  draw();
  print_object();

  G_wait_key();

  return 0;
}

int test_serpinski_rotate()
{
  G_init_graphics(Wsize, Wsize);
  double x1 = -1.0, y1 = -1.0, z1 = -1.0;
  double x2 = 1.0, y2 = -1.0, z2 = -1.0;
  double x3 = 0.0, y3 = 1.0, z3 = -1.0;
  double x4 = 0.0, y4 = 0.0, z4 = 1.0;

  int depth = 4;

  build_serpinski(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, depth);

  while (1)
  {
    G_rgb(0, 0, 0);
    G_clear();
    G_rgb(0, 1, 0);
    project(5, 45);
    draw();

    int key;
    key = G_wait_key(); // pause so user can see results

    if (key == 'y')
    {
      rotate_y(2);
    }

    if (key == 'x')
    {
      rotate_x(2);
    }

    if (key == 'z')
    {
      rotate_z(2);
    }

    if (G_wait_key() == 'q')
    {
      break;
    }

    else
    {
      rotate_y(2);
    }
  }
}
int main()
{
  // test_pyramid();
  // test_pyramid_rotate();
  // test_square();
  // test_square_rotate();
  // test_serpinski();

  test_serpinski_rotate();
}
