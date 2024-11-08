#define TX_COMPILED
#include "..\SuperLibs\TXLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "akinator.h"

FILE* Log_File;

int main ()
{
    Create_file ("LOG_AKINATOR.html");

    node_akntr* node50_root = Create_node (50);
    node_akntr* node30 = Create_node (30);
    node_akntr* node70 = Create_node (70);
    node_akntr* node10 = Create_node (10);
    node_akntr* node65 = Create_node (65);
    node_akntr* node80 = Create_node (80);

    node50_root -> left  = node30;
    node50_root -> right = node70;

    node30 -> left = node10;

    node70 -> left = node65;
    node70 -> right = node80;

    Dump_in_line (node50_root);

    return 0;
}

int Build_Graph ()
{
    FILE* Log_graph = fopen ("LOG_GRAPH", "w+") ;
    fprintf (Log_graph, "");


    return 0;
}

node_akntr* Create_node (el_t data)
{
    node_akntr* new_node = (node_akntr*) calloc (1, sizeof (node_akntr));
    if (!new_node) {fprintf (Log_File, "Error!"); assert (new_node);}

    new_node -> data = data;

    return new_node;
}

int  Create_file (const char* name_of_file)
{
    if ((Log_File = fopen (name_of_file, "w+")) == NULL)
    {
        fprintf (stdout, "Не удается открыть файл %s\n", name_of_file);
        return 0;
    }
    setvbuf (Log_File, 0, 0, _IONBF);
    fprintf (Log_File, "<pre>\n");
    return 0;
}

void Dump_graph (node_akntr* node)
{

  
}
 

void Dump_in_line (node_akntr* node)
{
    if (!node) return;
    fprintf (Log_File, "(");
    fprintf (Log_File, "%" TYPE, node -> data);

    if (node -> left) Dump_in_line (node -> left);
    if (node -> right) Dump_in_line (node -> right);
   
    fprintf (Log_File, ")");
}