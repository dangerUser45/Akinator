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
    int val = 0;

    scanf("%d", &val);
    while (1)
    {
        printf ("here\n");
        switch (val)
        {
            case 1:
                continue;

            case 2:
                printf ("ura ura ura\n");
                break;
        }

    }
    

}