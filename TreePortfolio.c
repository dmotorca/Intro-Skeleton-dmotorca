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
    double sun_x = 80.0;
    double sun_y = 700.0;
    double sun_radius = 50.0; // the radius of the sun

    // Draw the sun rays
    int num_rays = 12;
    double ray_length = 70.0;
    double ray_angle = 360.0 / num_rays;

    for (int i = 0; i < num_rays; i++)
    {
        double angle = deg2rad(ray_angle * i);
        double end_x = sun_x + ray_length * cos(angle);
        double end_y = sun_y - ray_length * sin(angle);

        // Draw the ray as a line segment
        G_rgb(1.0, 1.0, 0.0); // yellow color
        G_line(sun_x, sun_y, end_x, end_y);
    }

    // Draw the sun's disk with a gradient from orange to yellow
    double start_r = 1.0;
    double start_g = 0.5;
    double start_b = 0.0;
    double end_r = 1.0;
    double end_g = 1.0;
    double end_b = 0.0;

    for (double i = sun_radius; i >= 0; i -= 0.1)
    {
        double t = i / sun_radius;
        double r = start_r * (1 - t) + end_r * t;
        double g = start_g * (1 - t) + end_g * t;
        double b = start_b * (1 - t) + end_b * t;
        G_rgb(r, g, b);
        G_fill_circle(sun_x, sun_y, i);
    }
}

void draw_clouds()
{
    // Main clouds
    double cloud_x1 = 200.0;
    double cloud_x2 = 450.0;
    double cloud_y1 = 710.0;
    double cloud_y2 = 710.0;

    // Above main
    double cloud_x3 = 200.0;
    double cloud_x4 = 450.0;
    double cloud_y3 = 720.0;
    double cloud_y4 = 720.0;

    // Below main
    double cloud_x5 = 200.0;
    double cloud_x6 = 450.0;
    double cloud_y5 = 700.0;
    double cloud_y6 = 700.0;

    int i = 0;
    double cloud_radius = 25.0;

    for (i = 0.0; i < 14; i++)
    {
        cloud_x1 += 20;
        cloud_x2 += 20;
        cloud_x3 += 20;
        cloud_x4 += 20;
        cloud_x5 += 20;
        cloud_x6 += 20;

        // If even, let's make the cloud color lighter
        if (i % 2 == 0)
        {
            cloud_radius = 50;
            double t = (double)i / 10.0;
            double r = 0.7568627451 + t * (1.0 - 0.7568627451);
            double g = 0.7450980392 + t * (1.0 - 0.7450980392);
            double b = 0.7294117647 + t * (1.0 - 0.7294117647);
            G_rgb(r, g, b);
            G_fill_circle(cloud_x1, cloud_y1, cloud_radius);
            G_fill_circle(cloud_x2, cloud_y2, cloud_radius);

            G_fill_circle(cloud_x3, cloud_y3, cloud_radius);
            G_fill_circle(cloud_x4, cloud_y4, cloud_radius);
            G_fill_circle(cloud_x5, cloud_y5, cloud_radius);
            G_fill_circle(cloud_x6, cloud_y6, cloud_radius);
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
    double r1 = 0.98, g1 = 0.84, b1 = 0.65;
    double r2 = 0.10, g2 = 0.10, b2 = 0.44;

    for (int y = 0; y < sheight; y++)
    {
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

    /* Production rules for the tree*/
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
    G_save_to_bmp_file("TreePortfolio.bmp");
}
