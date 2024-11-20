#include "..\Processor\Onegin_for_proc\Onegin_General.h"
#include "akinator.h"

extern FILE* Base_File;


//====================================================================================================================================
int main (int argc, char* argv[])
{
    akinator* Akin_data = Akin_init (argc, argv);
    node_akntr* node_null = *(Akin_data -> root_node);

    Read3 (Akin_data, argv[1], &node_null);
    Dump_akin (node_null, node_null);

    Run_akinator (Akin_data, node_null);
    Dump_akin (node_null, node_null);

    Print3 (node_null);

    Dtor_akin (Akin_data);
}
//====================================================================================================================================