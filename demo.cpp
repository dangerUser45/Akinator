#include "..\SuperLibs\TXLib.h"

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>



char*  Skip_space (const char* ptr);
int My_Strcmp (const char* first_string, const char* second_string);
int Check_input_akin (char* temp_str);
enum input_akin {GUESS = 1, COMPARE, DEFINITION, EXIT_AKIN, YES, NO};


//=============================================================================================================================
int main()
{
    char* temp_str = (char*) calloc (256, sizeof (char));
    
   
    while (true)
    {
        //char* ret_val  = fgets  (temp_str, 256, stdin); printf ("temp_str = \"%s\"", temp_str);
        scanf ("%[^\n]", temp_str);
        getchar ();
        int action = Check_input_akin (temp_str); $(action);    
        switch (action)
        {
            case GUESS:
                //Guess_Akin (node);
                break;
            
            case COMPARE:
                //Compare_Akin ();
                break;

            case DEFINITION:
                //Definition_Akin ();
                break;

            case EXIT_AKIN:
                exit (0);
        
            case 0:
                break;
                
            default:
                printf ("ERROR IN Run_akinator(): line %d", __LINE__);
                break;
        }
    }
   
    free (temp_str);
}
//=============================================================================================================================
int My_Strcmp (const char* first_string, const char* second_string)
{
    assert (first_string);
    assert (second_string);

    int i = 0;
    for (; toupper(first_string[i]) == toupper(second_string[i]); i++)
    if (first_string[i] == '\0')
    return 0;
    return first_string[i] - second_string[i];

}
//=============================================================================================================================
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
//=============================================================================================================================
int Check_input_akin (char* temp_str)
{
    if ((toupper (temp_str[0]) == 'G' && temp_str[1] == '\0') || !(My_Strcmp (temp_str, "guess")))
        return GUESS;

    if ((toupper (temp_str[0]) == 'C' && temp_str[1] == '\0') || !(My_Strcmp (temp_str, "compare")))
        return COMPARE;

    if ((toupper (temp_str[0]) == 'D' && temp_str[1] == '\0') || !(My_Strcmp (temp_str, "define")))
        return DEFINITION;

    if ((toupper (temp_str[0]) == 'E' && temp_str[1] == '\0') || !(My_Strcmp (temp_str, "exit")))
        return EXIT_AKIN;  

    if ((toupper (temp_str[0]) == 'Y' && temp_str[1] == '\0') || !(My_Strcmp (temp_str, "yes")))
        return YES;
    
    if ((toupper (temp_str[0]) == 'N' && temp_str[1] == '\0') || !(My_Strcmp (temp_str, "no")))
        return NO;

    else {(printf ("Incorrect input ! Try again\n"));
        return 0;}

}
//=============================================================================================================================

