#include "FPToolkit.c"
#define MAX_RULES 100
#define MAX_DEPTH 6
#define STRING_LENGTH 1000000

struct production
{
    char var;
    char rule[100];
} prd[MAX_RULES];

char axiom[STRING_LENGTH] = "";
double depth = 0.0;
double angle = 0.0;
double num_rules = 0.0;

struct pos
{
    double x, y, angle;
};
struct pos stack[10000];
int top = 0;

void push(struct pos p)
{
    stack[top++] = p;
}

struct pos pop()
{
    return stack[--top];
}

void modify_string(char *userArray)
{
    for (int d = 0; d < depth; ++d)
    {
        char next_userArray[STRING_LENGTH] = "";
        for (char *ch = userArray; *ch != '\0'; ++ch)
        {
            int rule_found = 0;
            for (int i = 0; i < num_rules; ++i)
            {
                if (prd[i].var == *ch)
                {
                    strcat(next_userArray, prd[i].rule);
                    rule_found = 1;
                    break;
                }
            }
            if (!rule_found)
            {
                char ch_str[2] = {*ch, '\0'};
                strcat(next_userArray, ch_str);
            }
        }
        strcpy(userArray, next_userArray);
    }
}

double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}

void draw_sun()
{
    double sun_x = 55.0;
    double sun_y = 710.0;
    double sun_radius = 50.0; // the radius of the sun

    G_rgb(1.0, 1.0, 0.0);                    // set color to yellow
    G_fill_circle(sun_x, sun_y, sun_radius); // draw the sun
}

void draw_clouds()
{
    double cloud_x1 = 200.0;
    double cloud_y1 = 710.0;
    double cloud_x2 = 500.0;
    double cloud_y2 = 710.0;
    int i = 0;
    double cloud_radius = 25.0;

    G_rgb(0.7568627451, 0.7450980392, 0.7294117647);

    for (i = 0.0; i < 10; i++)
    {
        cloud_x1 += 20;
        cloud_x2 += 20;

        // If even lets make the radius bigger
        if (i % 2 == 0)
        {
            double temp = 35;
            G_fill_circle(cloud_x1, cloud_y1, temp);
            G_fill_circle(cloud_x2, cloud_y2, temp);
        }
    }
}

void generate(const char *userArray)
{
    double ogx = 400.0;
    double ogy = 000.0;
    double newx = 0.0;
    double newy = 0.0;

    double current_angle = M_PI / 2;
    G_rgb(0.0, 0.5, 0.0);

    for (const char *ch = userArray; *ch != '\0'; ++ch)
    {
        if (*ch == 'F')
        {
            newx = ogx + 8 * cos(current_angle);
            newy = ogy + 8 * sin(current_angle);
            G_line(ogx, ogy, newx, newy);
            // G_line(ogx - 1, ogy - 1, newx - 1, newy - 1);
            // G_line(ogx + 1, ogy + 1, newx + 1, newy + 1);
            ogx = newx;
            ogy = newy;
        }
        else if (*ch == '+')
        {
            current_angle += deg2rad(angle);
        }
        else if (*ch == '-')
        {
            current_angle -= deg2rad(angle);
        }
        else if (*ch == '[')
        {
            push((struct pos){ogx, ogy, current_angle});
        }
        else if (*ch == ']')
        {
            struct pos p = pop();
            ogx = p.x;
            ogy = p.y;
            current_angle = p.angle;
        }
    }
}

void draw_background_gradient(int swidth, int sheight)
{
    // double r1 = 0.4, g1 = 0.15, b1 = 0.07;  // brown
    // double r2 = 0.82, g2 = 0.70, b2 = 0.55; // white

    double r1 = 0.98, g1 = 0.84, b1 = 0.65;
    double r2 = 0.10, g2 = 0.10, b2 = 0.44;

    // double r1 = 1.0, g1 = 0.3, b1 = 0.8; // purple hue
    // double r2 = 0.0, g2 = 0.0, b2 = 1.0; // purple hue

    for (int y = 0; y < sheight; y++)
    {
        // Interpolate between the start and end colors
        double t = (double)y / (sheight - 1);
        double r = r1 * (1 - t) + r2 * t;
        double g = g1 * (1 - t) + g2 * t;
        double b = b1 * (1 - t) + b2 * t;
        G_rgb(r, g, b);
        for (int x = 0; x < swidth; x++)
        {
            G_point(x, y);
        }
    }
}

int main()
{
    int swidth, sheight;

    swidth = 800;
    sheight = 800;
    G_init_graphics(swidth, sheight);
    draw_background_gradient(swidth, sheight);

    strcpy(axiom, "X");
    prd[0].var = 'X';
    strcpy(prd[0].rule, "F+[[X]-X]-F[-FX]+X");
    prd[1].var = 'F';
    strcpy(prd[1].rule, "FF");
    num_rules = 2;
    depth = 5;
    angle = 25.0;

    char userArray[STRING_LENGTH];
    strcpy(userArray, axiom);
    modify_string(userArray);
    generate(userArray);

    draw_sun();
    draw_clouds();

    G_wait_key();
    G_save_to_bmp_file("demo.bmp");
}
