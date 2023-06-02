#include "FPToolkit.c"

void drawKoch(double x1, double y1, double x2, double y2, int level)
{
    if (level == 0)
    {
        G_line(x1, y1, x2, y2);
    }
    else
    {
        double dx = x2 - x1;
        double dy = y2 - y1;

        double x3 = x1 + dx / 3;
        double y3 = y1 + dy / 3;

        double x5 = x2 - dx / 3;
        double y5 = y2 - dy / 3;

        double angle = atan2(dy, dx);
        angle += M_PI / 3;

        double length = sqrt((dx * dx) + (dy * dy)) / 3;

        double x4 = x3 + length * cos(angle);
        double y4 = y3 + length * sin(angle);

        drawKoch(x1, y1, x3, y3, level - 1);
        drawKoch(x3, y3, x4, y4, level - 1);
        drawKoch(x4, y4, x5, y5, level - 1);
        drawKoch(x5, y5, x2, y2, level - 1);
    }
}

void drawSnowflake(double x, double y, double size, int level)
{
    double height = size * sqrt(3) / 2;

    drawKoch(x, y, x + size, y, level);
    drawKoch(x + size, y, x + size / 2, y + height, level);
    drawKoch(x + size / 2, y + height, x, y, level);
}

int main()
{
    G_init_graphics(800, 800);
    G_rgb(0, 0, 0);
    G_clear();
    G_rgb(1, 1, 1);

    drawSnowflake(100, 100, 600, 4);

    G_wait_key();
}
