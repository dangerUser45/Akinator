#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

char*  Skip_space (const char* ptr) 
{
    ++ptr;
    printf ("%c", ptr[0]);
    while (1)
        if (*ptr == ' ')
            ++ptr;
        else break;
    
    return (char*) ptr;
}


int main()
{
    char* str = (char*) calloc (16, sizeof (char));

    if (!str) printf ("error\n");
    assert (str);
    printf ("addr = %lld" ,str);
    str[0] = 'Q';
    printf ("%c\n", str[0]);
    printf ("Hello %c   \n", str[0]);

    sprintf (str, "%s\n", "Q   WE    RTY");
    printf ("%s", str);

    char* str_s = Skip_space (str);
    printf ("str_s = %lld", str_s);

}