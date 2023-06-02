// David Motorca <dmotorca@pdx.edu>
// Fractals
#include "FPToolkit.c"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

char userArray[1000000];

int swidth, sheight;
// must do this before you do 'almost' any other graphical tasks
swidth = 800;
sheight = 800;

int stack[256];
int stack_count = 0;
int arrLen = 0;
double angle = 0.0;

// For string builder
int depth = 0;
double degree = 0.0;
int num_rules = 0;
struct production
{
    char var;
    char axiom[10];
    char rule[100];
} prd[10];

int find_greatest_points(double x_min, double x_max, double y_min, double y_max)
{
}

int find_diff(double x_min, double x_max, double y_min, double y_max)
{
    double scale_factor = 0.0;
    double diff_in_x = 0.0;
    double diff_in_y = 0.0;
    diff_in_x = x_max - x_min;
    diff_in_y = y_max - y_min;

    // Now lets see which one is larger, we will pick the biggest one for our scale factor

    if (diff_in_x >= diff_in_y)
    {
        // Lets use x as the scale factor
        scale_factor = (766 / diff_in_x) * .9;

        return scale_factor;
    }
    else
    {
        // Lets pick y as the sf
        scale_factor = (766 / diff_in_y) * .9;
        return scale_factor;
    }
}
void string_builder()
{
    // Temp counter
    int count = 0;

    printf("Please enter the axiom: \n");
    scanf("%s", prd[0].axiom);

    printf("Please enter the number of rules: \n");
    scanf("%d", &num_rules);

    while (count < num_rules)
    {
        printf("Please enter the rule for variable %c: \n", 'A' + count);
        scanf(" %c", &prd[count].var);
        scanf(" %s", prd[count].rule);
        count++;
    }

    printf("Please enter the depth: \n");
    scanf("%d", &depth);

    // Apply rules to the axiom to produce a new string
    char *oldString = (char *)malloc(sizeof(char) * 1000000);
    strcpy(oldString, prd[0].axiom);
    char *newString = (char *)malloc(sizeof(char) * 1000000);

    for (int i = 0; i < depth; i++)
    {
        int newPosition = 0;
        for (int j = 0; j < strlen(oldString); j++)
        {
            char c = oldString[j];
            int ruleApplied = 0;
            for (int k = 0; k < num_rules; k++)
            {
                if (c == prd[k].var)
                {
                    // Replace the part of the string that the rule applies to
                    int ruleLen = strlen(prd[k].rule);
                    strncpy(newString + newPosition, prd[k].rule, ruleLen);
                    newPosition += ruleLen;
                    ruleApplied = 1;
                    break;
                }
            }

            if (!ruleApplied)
            {
                newString[newPosition] = c;
                newPosition++;
            }
        }

        newString[newPosition] = '\0'; // Add null terminator to new string
        char *temp = oldString;
        oldString = newString;
        newString = temp;
    }

    strcpy(userArray, oldString);
    arrLen = strlen(userArray);

    free(oldString);
    free(newString);
}

/* String Builder code before 10:45am on May8th
void string_builder()
{
    // Temp counter
    int count = 0;

    printf("Please enter the axiom: \n");
    scanf("%s", prd[0].axiom);

    printf("Please enter the number of rules: \n");
    scanf("%d", &num_rules);

    while (count < num_rules)
    {
        printf("Please enter the rule for variable %c: \n", 'A' + count);
        scanf(" %c", &prd[count].var);
        scanf(" %s", prd[count].rule);
        count++;
    }

    printf("Please enter the depth: \n");
    scanf("%d", &depth);

    // Apply rules to the axiom to produce a new string
    char *oldString = prd[0].axiom;
    char *newString = (char *)malloc(sizeof(char) * 1000000);
    strcpy(newString, oldString);

    for (int i = 0; i < depth; i++)
    {
        int newPosition = 0;
        for (int j = 0; j < strlen(oldString); j++)
        {
            char c = oldString[j];
            int ruleApplied = 0;
            for (int k = 0; k < num_rules; k++)
            {
                if (c == prd[k].var)
                {
                    // Replace the part of the string that the rule applies to
                    int ruleLen = strlen(prd[k].rule);
                    strncpy(newString + newPosition, prd[k].rule, ruleLen);
                    newPosition += ruleLen;
                    ruleApplied = 1;
                    break;
                }
            }

            if (!ruleApplied)
            {
                newString[newPosition] = c;
                newPosition++;
            }
        }

        newString[newPosition] = '\0'; // Add null terminator to new string
        printf("%s MEOW: ", newString);
        strcpy(oldString, newString);
    }

    strcpy(userArray, oldString);
    arrLen = strlen(userArray);
    free(newString);
}

*/
double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}

void update_bounding_box(double x, double y, double *x_min, double *x_max, double *y_min, double *y_max)
{
    if (x < *x_min)
        *x_min = x;
    if (x > *x_max)
        *x_max = x;
    if (y < *y_min)
        *y_min = y;
    if (y > *y_max)
        *y_max = y;
}

/*
void process()
{
    // "f" = Move 1 units
    // "+" = Rotate 30 degrees(pi/2) in the positive direction
    // "-" = Rotate 30 degrees(pi/2) in the negative direction
    arrLen = strlen(userArray); // Getting the strlen of userArray
    double ogx = 400.0;
    double ogy = 400.0;
    double newx = 0.0;
    double newy = 0.0;

    for (int i = 0; i < arrLen; i++)
    {
        double randomx = ((double)rand() / (double)RAND_MAX);
        double randomy = ((double)rand() / (double)RAND_MAX);
        double randomz = ((double)rand() / (double)RAND_MAX);

                //int key;
                //key = G_wait_key(); // pause so user can see results


if (userArray[i] == 'f' || userArray[i] >= 'A' && userArray[i] <= 'Z')
{
    double newx = ogx + 10 * cos(deg2rad(angle));
    double newy = ogy + 10 * sin(deg2rad(angle));

//        How to make gradient color(s)



    G_rgb(randomx, randomy, randomz);
    G_line(ogx, ogy, newx, newy);
    ogx = newx;
    ogy = newy;
}

if (userArray[i] == '+')
{
    angle += 90;
}

if (userArray[i] == '-')
{
    angle -= 90;
}
// printf("%d", i);
}
}
*/
void process()
{

    double ogx = 400.0;
    double ogy = 400.0;
    double newx = 0.0;
    double newy = 0.0;
    // Initialize bounding box values
    double x_min = DBL_MAX;
    double x_max = -DBL_MAX;
    double y_min = DBL_MAX;
    double y_max = -DBL_MAX;

    for (int i = 0; i < arrLen; i++)
    {
        double randomx = ((double)rand() / (double)RAND_MAX);
        double randomy = ((double)rand() / (double)RAND_MAX);
        double randomz = ((double)rand() / (double)RAND_MAX);

        if (userArray[i] == 'f' || userArray[i] >= 'A' && userArray[i] <= 'Z')
        {
            double newx = ogx + 10 * cos(deg2rad(angle));
            double newy = ogy + 10 * sin(deg2rad(angle));

            // Update bounding box values
            update_bounding_box(ogx, ogy, &x_min, &x_max, &y_min, &y_max);
            update_bounding_box(newx, newy, &x_min, &x_max, &y_min, &y_max);

            ogx = newx;
            ogy = newy;
        }

        if (userArray[i] == '+')
        {
            angle += 90;
        }

        if (userArray[i] == '-')
        {
            angle -= 90;
        }
    }

    // Calculate scale factor and center offsets
    double scale_factor = find_diff(x_min, x_max, y_min, y_max);
    double x_offset = (swidth - scale_factor * (x_max - x_min)) / 2 - scale_factor * x_min;
    double y_offset = (sheight - scale_factor * (y_max - y_min)) / 2 - scale_factor * y_min;

    // Redraw with scaling and centering
    ogx = 400.0;
    ogy = 400.0;
    angle = 0.0;

    for (int i = 0; i < arrLen; i++)
    {
        double randomx = ((double)rand() / (double)RAND_MAX);
        double randomy = ((double)rand() / (double)RAND_MAX);
        double randomz = ((double)rand() / (double)RAND_MAX);

        if (userArray[i] == 'f' || userArray[i] >= 'A' && userArray[i] <= 'Z')
        {
            double newx = ogx + 10 * cos(deg2rad(angle));
            double newy = ogy + 10 * sin(deg2rad(angle));

            // Apply scale factor and center offsets
            double scaled_ogx = ogx * scale_factor + x_offset;
            double scaled_ogy = ogy * scale_factor + y_offset;
            double scaled_newx = newx * scale_factor + x_offset;
            double scaled_newy = newy * scale_factor + y_offset;

            G_rgb(randomx, randomy, randomz);
            G_line(scaled_ogx, scaled_ogy, scaled_newx, scaled_newy);

            ogx = newx;
            ogy = newy;
        }

        if (userArray[i] == '+')
        {
            angle += 90;
        }

        if (userArray[i] == '-')
        {
            angle -= 90;
        }
    }
}

int main()
{

    G_init_graphics(swidth, sheight); // interactive graphics

    G_rgb(0.0, 0.0, 0.0);
    G_clear();
    // read_string();
    string_builder();
    process();

    int key;
    key = G_wait_key(); // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp");

    return 0;
}