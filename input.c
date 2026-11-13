#include <stdio.h>

#define MAX 100
#define STR(x) #x
#define PI 3.14159f

/* A multi-line comment
   that spans two lines, with <tags> & stuff */

int main(void)
{
    // single line comment with "quotes" and /* nested marker
    unsigned long big = 0x1FUL;
    float f = 1.5e-3f, g = .5;
    char c = '\'';
    char *s = "say \"hi\" // not a comment /* nor this */ <b>";
    int x = 10 / 2;            /* trailing comment */

    for (int i = 0; i < MAX; i++)
    {
        if (i % 2 == 0)
            continue;
        printf("%d\n", i);
    }
    return 0;
}