// David Motorca <dmotorca@pdx.edu>
// Fractals
#include "FPToolkit.c"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define SIZE 256

int top_stack = -1, inp_array[SIZE];
void push();
void pop();
void show();

char userArray[1000000];
char v[1000000];
char u[1000000];

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

void stack_push()
{

    int x;

    if (top_stack == SIZE - 1)
    {
    }
}

/*
void string_builder()
{
    printf("Please enter in the axiom: \n");
    scanf("%s", prd[0].axiom);

    printf("Please enter in the depth");
    scanf("%d", &depth);

    printf("Please enter in how many rules you would like: \n");
    scanf("%d", &num_rules);

    for (int i = 0; i < num_rules; i++)
    {
        printf("Please enter in the variable for rule %d: \n", i + 1);
        scanf(" %c", &prd[i + 1].var);
        printf("Please enter in the rule for variable %c: \n", prd[i + 1].var);
        scanf("%s", prd[i + 1].rule);
    }

    arrLen = strlen(prd[0].axiom);
    char tempArray[1000000] = "";

    for (int i = 0; i < depth; i++)
    {
        int found = 0;
        for (int j = 1; j <= num_rules; j++)
        {
            if (prd[j].var == prd[0].axiom[i])
            {
                strcat(tempArray, prd[j].rule);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            char temp[2];
            temp[0] = prd[0].axiom[i];
            temp[1] = '\0';
            strcat(tempArray, temp);
        }
    }

    strcpy(prd[0].axiom, tempArray);
}
*/

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
    G_rgb(0.0, 1.0, 0.0);

    for (int i = 0; i < depth; i++)
    {
        for (int j = 0; j < strlen(oldString); j++)
        {
            char c = oldString[j];
            int ruleApplied = 0;
            for (int k = 0; k < num_rules; k++)
            {
                if (c == prd[k].var)
                {
                    strcat(newString, prd[k].rule);
                    ruleApplied = 1;
                    break;
                }
            }

            if (!ruleApplied)
            {
                strncat(newString, &c, 1);
            }
        }

        printf("%s MEOW: ", newString);
        strcpy(oldString, newString);
        newString[0] = '\0';
    }

    strcpy(userArray, oldString);
    arrLen = strlen(userArray);
}
/*
void string_builder()
{
    // Temp counter
    int count = 0;

    printf("Please enter in the axiom: \n");
    scanf("%s", prd[0].axiom);
    printf("%s", prd[0].axiom);

    printf("Please enter in how many rules you would like: \n");
    scanf("%d", &num_rules);
    printf("%d", num_rules);

    while (count < num_rules)
    {
        printf("Please enter in what the rules should be: \n");
        scanf("%s", prd[count].rule);
        printf("%s", prd[count].rule);
        count++;
    }

    printf("Please enter in the depth you would like: \n");
    scanf("%d", &depth);
    printf("%d", depth);

    printf("Please enter in the degree you would like: \n");
    scanf("%lf", &degree);
    printf("%lf", degree);
}
*/

void read_string()
{
    /*
    scanf("%s", &userArray);
    */
    scanf("%s", userArray);

    // printf("%s", userArray);
}

double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}

void process()
{
    // "f" = Move 1 units
    // "+" = Rotate 30 degrees(pi/2) in the positive direction
    // "-" = Rotate 30 degrees(pi/2) in the negative direction
    arrLen = strlen(userArray); // Getting the strlen of userArray
    double ogx = 200.0;
    double ogy = 200.0;
    double newx = 0.0;
    double newy = 0.0;

    for (int i = 0; i < arrLen; i++)
    {
        double randomx = ((double)rand() / (double)RAND_MAX);
        double randomy = ((double)rand() / (double)RAND_MAX);
        double randomz = ((double)rand() / (double)RAND_MAX);

        /*
                int key;
                key = G_wait_key(); // pause so user can see results


        */
        if (userArray[i] == 'f' || userArray[i] >= 'A' && userArray[i] <= 'Z')
        {
            double newx = ogx + 10 * cos(deg2rad(angle));
            double newy = ogy + 10 * sin(deg2rad(angle));

            /*
                How to make gradient color(s)


            */

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

int main()
{

    int swidth, sheight;
    // must do this before you do 'almost' any other graphical tasks
    swidth = 800;
    sheight = 800;
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