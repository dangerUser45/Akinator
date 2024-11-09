#define TX_COMPILED
#include "..\SuperLibs\TXLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "akinator.h"

FILE* Log_File;
FILE* Graph_File;

//====================================================================================================================================
int main ()
{
    Create_file ("LOG_AKINATOR.html", Log_File);
    Create_file ("Dot.txt", Graph_File);

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
    Dump_graph (node50_root);

    return 0;
}
//====================================================================================================================================
node_akntr* Create_node (el_t data)
{
    node_akntr* new_node = (node_akntr*) calloc (1, sizeof (node_akntr));
    if (!new_node) {fprintf (Log_File, "Error!"); assert (new_node);}

    new_node -> data = data;

    return new_node;
}
//====================================================================================================================================
int  Create_file (const char* name_of_file, FILE* file)
{
    if ((file = fopen (name_of_file, "w+")) == NULL)
    {
        fprintf (stdout, "Не удается открыть файл %s\n", name_of_file);
        return 0;
    }
    setvbuf (file, 0, 0, _IONBF);
    fprintf (file, "<pre>\n");
    return 0;
}
//====================================================================================================================================
void Dump_graph (node_akntr* node)
{
    if (!node) return;
    if (node -> right <= NULL)  {#define  node -> right -> data  0 
                                 #define  node -> right -> left  0 
                                 #define  node -> right -> right 0 };

    if (node -> left <= NULL) {  #define  node -> left -> data   0 
                                 #define  node -> left -> left   0 
                                 #define  node -> left -> right  0 };       
    fprintf(Graph_File, ""                                                                                                                  
                                                                                                                                              
       "digraph" 
    "{"
       "rankdir = TB;"

        "{" 
           "node[shape=plaintext];"
         "edge[color=white]"
         "\"1\" ->  \"2\";" 
        "}"
 
        "node [ color = \"#0d5a0e\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f8a4\"];"
        "edge [color = \"blue\", fontsize = 16];");
    fprintf(Graph_File, ""
        "null    [ shape = \"Mrecord\", label = \" { data = %d\n addr: %p | { <left> L:\n addr: %p \n| <right> R: \n addr: %p \n} }\" ];", node -> data, node -> left, node -> right);
    fprintf(Graph_File, ""
        "first   [ shape = \"Mrecord\", label = \" { data = %d\n addr: %p | { <left> L:\n addr: %p \n| <right> R: \n addr: %p \n} }\" ];", node -> left -> data, node -> left -> left, node -> left -> right);
    fprintf(Graph_File, ""   
        "second  [ shape = \"Mrecord\", label = \" { data = %d\n addr: %p | { <left> L:\n addr: %p \n| <right> R: \n addr: %p \n} }\" ];", node -> right -> data, node -> right -> left, node -> right -> right);
 
    fprintf(Graph_File, ""
        "null: <left> -> first;"
        "null: <right> -> second;"

        "{ rank = same; \"1\"; \"null\" }"
        "{ rank = same; \"2\"; \"first\"; \"second\";}"
    "}"

    );
}
//====================================================================================================================================
void Dump_in_line (node_akntr* node)
{
    if (!node) return;
    fprintf (Log_File, "(");
    fprintf (Log_File, "%" TYPE, node -> data);

    if (node -> left) Dump_in_line (node -> left);
    if (node -> right) Dump_in_line (node -> right);
   
    fprintf (Log_File, ")");
}
//====================================================================================================================================

struct node
{
    el_t data;
    node* left;
    node* right;
};
 node* x = 0;

x -> data;
x -> right;
x -> left;


