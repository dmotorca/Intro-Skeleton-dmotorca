#include "FPToolkit.c"
#define MAX_RULES 100
#define MAX_DEPTH 10
#define STRING_LENGTH 1000000

// Global Variables
char axiom[STRING_LENGTH] = "";
double depth = 0.0;     // Depth of the image
double angle = 0.0;     // Angle of drawing
double num_rules = 0.0; // Number of rules
double x_min = 0.0;     // X min for calculating auto-scale
double x_max = 0.0;     // X max for calculating auto-scale
double y_min = 0.0;     // Y min for calculating auto-scale
double y_max = 0.0;     // Y max for calculating auto-scale
// Global Variables

// Struct Production
struct production
{
    char var;       // Single char
    char rule[100]; // Rules to apply to the string
} prd[MAX_RULES];

double find_diff(double x_min, double x_max, double y_min, double y_max)
{
}

void auto_scale(const char *userArray)
{
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

// Function to convert from degrees to radians
double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}
void set_dragon_color(const char *userArray, const char *ch)
{
    // Calculate how far we've progressed through the string.
    double progress = (double)(ch - userArray) / strlen(userArray);

    // Define some colors for the start, middle, and end of the curve.
    double start[3] = {50 / 255.0, 168 / 255.0, 109 / 255.0}; // Green at the start
    double mid[3] = {140 / 255.0, 200 / 255.0, 75 / 255.0};   // Lighter green in the middle
    double end[3] = {255 / 255.0, 223 / 255.0, 0 / 255.0};    // Gold at the end

    double color[3];
    if (progress < 0.5)
    {
        // Interpolate between start and mid colors.
        for (int i = 0; i < 3; ++i)
        {
            color[i] = start[i] + progress * 2 * (mid[i] - start[i]);
        }
    }
    else
    {
        // Interpolate between mid and end colors.
        for (int i = 0; i < 3; ++i)
        {
            color[i] = mid[i] + (progress - 0.5) * 2 * (end[i] - mid[i]);
        }
    }

    // Set the color.
    G_rgb(color[0], color[1], color[2]);
}

void generate(const char *userArray)
{
    double ogx = 200.0; // Origin - x
    double ogy = 450.0; // Origin - y
    double newx = 0.0;  // Used to generate new x
    double newy = 0.0;  // Used to generate new y
    //    double current_angle = 0.0; // Keep track of our current angle
    double current_angle = -M_PI / 2; // For Dragon Curve Start

    for (const char *ch = userArray; *ch != '\0'; ++ch)
    {

        if (*ch == 'F' || *ch >= 'A' && *ch <= 'Z') // Any Alphabetical Character
        {
            set_dragon_color(userArray, ch);
            newx = ogx + 12 * cos(current_angle); // Setting
            newy = ogy + 12 * sin(current_angle); // Setting
            G_line(ogx, ogy, newx, newy);         // Draw
            ogx = newx;
            ogy = newy;
        }
        else if (*ch == '+') // Rotate in the positive direction by some angle
        {
            current_angle += deg2rad(angle);
        }
        else if (*ch == '-') // Rotate in the negative direction by some angle
        {
            current_angle -= deg2rad(angle);
        }
    }
}

int main()
{
    int swidth, sheight;

    swidth = 800;
    sheight = 800;
    G_init_graphics(swidth, sheight);
    G_rgb(0.0, 0.0, 0.0); // Black
    // G_rgb(157 / 255.0, 193 / 255.0, 131 / 255.0); // Sage Green

    // G_rgb(50 / 255.0, 168 / 255.0, 109 / 255.0); //Cool light green
    G_clear();

    strcpy(axiom, "F");
    prd[0].var = 'F';
    strcpy(prd[0].rule, "F+G");
    prd[1].var = 'G';
    strcpy(prd[1].rule, "F-G");
    num_rules = 2;
    depth = 10;
    angle = 90.0;
    /*
    //Serpenskis triangle
    //Size = 24
    // starting value = 10.0 x , 750.0 y
        strcpy(axiom, "F-G-G");
        prd[0].var = 'F';
        strcpy(prd[0].rule, "F-G+F+G-F");
        prd[1].var = 'G';
        strcpy(prd[1].rule, "GG");
        num_rules = 2;
        depth = 5;
        angle = 120.0;
    */
    char userArray[STRING_LENGTH];
    strcpy(userArray, axiom);
    modify_string(userArray);
    generate(userArray);

    G_wait_key();
    G_save_to_bmp_file("demo.bmp");
}
