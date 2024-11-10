#define TX_COMPILED
#include "..\SuperLibs\TXLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "akinator.h"

FILE* Log_File = 0;
FILE* Graph_File = 0;

//====================================================================================================================================
int main ()
{
    Log_File = Create_file ("LOG_AKINATOR.html");
    Graph_File = Create_file ("Dot.txt");

    fprintf (Log_File, "<pre>");

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
    Dump_graph_init (node50_root);

    Close_File (Log_File);
    Close_File (Graph_File);
    system ("dot Dot.txt -Tpng -o tree.png");

     txDisableAutoPause ();

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
FILE* Create_file (const char* name_of_file)
{
    FILE* file = fopen ($(name_of_file), "w+");

    if (file == NULL)
    {
        fprintf (stdout, "Не удается открыть файл %s", name_of_file);
        perror (""); 
        return 0;
    }
    
    setvbuf (file, 0, 0, _IONBF);

    return file;
}
//====================================================================================================================================
FILE* Close_File (FILE* file)
{
    if (file) fclose (file); 
    return file;
}
//====================================================================================================================================
void Dump_graph_recursive (node_akntr* node)
{
    if (!node) return;       
    fprintf(Graph_File, ""                                                                                                                  
        "\trankdir = TB;\n"

        /*"\t{\n"                                                         //
            "\t\tnode[shape=plaintext];\n"
            "\t\tedge[color=white]\n"
            "\t\t\"1\" ->  \"2\";\n" 
        "\t}\n\n"*/
 
        "\tnode [ color = \"#004b00\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f8a4\"];\n"
        "\tedge [ color = \"#004b00\", fontsize = 16];\n\n");

    fprintf(Graph_File, ""
        "\tnode_%p [ shape = \"Mrecord\", label = \"{ data = %d\\n addr: %p | { L:\\n addr: %p | R: \\n addr: %p } }\" ];\n", node, node -> data, node, node -> left, node -> right);
    
    if (node -> left != NULL)
    {
        fprintf(Graph_File, "\n"
        "\tnode_%p[ shape = \"Mrecord\", label = \"{ data = %d\\n addr: %p | { L:\\n addr: %p |   R: \\n addr: %p } }\" ];\n", node -> left,  node -> left -> data, node -> left, node -> left -> left, node -> left -> right);
        fprintf (Graph_File, ""
        "\tnode_%p  -> node_%p;\n", node, node -> left);
        
       //Dump_graph_recursive (node -> left);

    }
    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_l_null_%p[ shape = \"Mrecord\", label = \"{ addr: %s | {   L:\\n addr: %s |   R: \\n addr: %s } }\" ];\n", node, "(null)",  "(null)", "(null)");
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_l_null_%p;\n", node, node);
        fprintf(Graph_File, ""
            "\t}\n");
        }  

    if (node -> right != NULL)
    {
        fprintf(Graph_File, "\n"   
            "\t\tnode_%p [ shape = \"Mrecord\", label = \" { data = %d\\n addr: %p | { L:\\n addr: %p | R: \\n addr: %p } }\" ];", node -> right, node -> right -> data, node -> right, node -> right -> left, node -> right -> right);
        fprintf(Graph_File, "\n"
            "\t\tnode_%p  -> node_%p;\n", node, node -> right);
    }
    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_r_null_%p [shape = \"Mrecord\", label = \"{ addr: %s | { L:\\n addr: %s | R: \\n addr: %s } }\" ];\n", node, "(null)",  "(null)", "(null)");
        
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_r_null_%p;\n", node, node);
        fprintf(Graph_File, ""   
            "\t}\n");
          }

        Dump_graph_recursive (node -> left);
        Dump_graph_recursive (node -> right);

        /*fprintf (Graph_File, "\n"
            "\t{ rank = same; \"1\"; \"null\" }\n"
            "\t{ rank = same; \"2\"; \"first\"; \"second\";}\n"
                );*/
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
void Dump_graph_init (node_akntr* node)
{
    fprintf (Graph_File, "digraph\n" 
                         "{\n");
    Dump_graph_recursive (node);
    fprintf (Graph_File, "}");
}
//====================================================================================================================================

