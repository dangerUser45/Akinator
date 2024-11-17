

#include <stdio.h>
#include <stdlib.h>
#include "..\Processor\Onegin_for_proc\Onegin_processing.h"
#include "..\Processor\Onegin_for_proc\Onegin_General.h"
#include "..\Processor\Onegin_for_proc\Print.h"
#include "akinator.h"

extern FILE* Log_File;

akinator* Akin_init (int argc, char* argv[])
{
    Log_File = Create_file ("LOG_AKINATOR.html");
    fprintf (Log_File, "<pre>");

    akinator* akin_data = (akinator*) calloc (1, sizeof (akinator));
    if (!akin_data) { fprintf (Log_File, "ERROR IN AKIN INIT: akin_data = null\n"); return 0; }

    ONEGIN* onegin_data = (ONEGIN*)   calloc (1, sizeof (ONEGIN));
    if (!akin_data) { fprintf (Log_File, "ERROR IN AKIN INIT: onegin_data = null\n"); return 0; }

    Check_argc (argc);
    onegin_data -> name = argv[1];
    onegin_data -> fsize = file_size (argv[1]);
    Check_fsize (onegin_data -> fsize);
    Read_File (onegin_data); 
    DBG_Print (onegin_data);

    akin_data -> onegin_data = onegin_data;

    node_akntr* node_root = 0;
    akin_data -> root_node = &node_root;

    return akin_data;
}