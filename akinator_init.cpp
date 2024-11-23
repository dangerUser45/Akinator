#include <stdio.h>
#include <stdlib.h>
#include "..\Processor\Onegin_for_proc\Onegin_processing.h"
#include "..\Processor\Onegin_for_proc\Onegin_General.h"
#include "..\Processor\Onegin_for_proc\Print.h"
#include "akinator.h"

FILE* Log_File;
FILE* Graph_File;
FILE* Graph_File_Utf8;
FILE* Base_File;



akinator* Akin_init (int argc, char* argv[])
{
    Log_File = Create_file ("LOG_AKINATOR.html");        //!!!    
    fprintf (Log_File, "<pre>");

    akinator* akin_data = (akinator*) calloc (1, sizeof (akinator));
    if (!akin_data) { fprintf (Log_File, "ERROR IN AKIN INIT: akin_data = null\n"); return 0; }

    ONEGIN* onegin_data = (ONEGIN*)   calloc (1, sizeof (ONEGIN));
    if (!onegin_data) { fprintf (Log_File, "ERROR IN AKIN INIT: onegin_data = null\n"); return 0; }

    node_akntr* node_root = (node_akntr*) calloc (1, sizeof (node_akntr));
    if (!node_root) { fprintf (Log_File, "ERROR IN AKIN INIT: akin_data = null\n"); return 0; }

    list_node* list_array = (list_node*) calloc (INIT_NUM_LIST, sizeof (list_node));
    if (!node_root) { fprintf (Log_File, "ERROR IN AKIN INIT: list = null\n"); return 0; }


    DBGAKN(printf ("node_root = %p\n", node_root);)
    DBGAKN(printf ("&node_root = %p\n", &node_root);)


    Check_argc (argc);
    onegin_data -> name = argv[1];
    onegin_data -> fsize = file_size (argv[1]);
    Check_fsize (onegin_data -> fsize);
    Read_File (onegin_data); 
    DBG_Print (onegin_data);

    //Base_File = Create_file (argv[1]);!!!

    akin_data -> onegin_data = onegin_data;
    akin_data -> root_node   = &node_root;
    akin_data -> list_array  = list_array;
    
    DBGAKN (printf ("akin_data -> onegin_data = %p\n", akin_data -> onegin_data);
    printf ("akin_data -> root_node = %p\n", akin_data -> root_node);
    printf ("akin_data -> root_node = %p\n", akin_data -> root_node[0]);
    printf ("*(akin_data -> root_node) = %p\n", *(akin_data -> root_node));)

    return akin_data;
}