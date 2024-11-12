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
    fprintf (Log_File, "<pre>");
    //system ("mkdir Picture_tree");


    node_akntr* node_root = Create_node ("DEEEEEEEEEEEEEEEEED");
    node_akntr* node_1 = Create_node ("ded_lox");
    node_akntr* node_2 = Create_node ("danik_balbes");
    node_akntr* node_3 = Create_node ("ded_kvadrober");
    node_akntr* node_4 = Create_node ("ded_penisoed");
    node_akntr* node_5 = Create_node ("ded_delaet_minet");
    node_akntr* node_6 = Create_node ("ded_na_golove_omlet");

    node_root -> left = node_1;
    Dump_akin (node_root, node_1);

    node_root -> right = node_2;
    Dump_akin (node_root, node_2);

    node_1 -> left = node_3;
    Dump_akin (node_root, node_3);

    node_3 -> right = node_4;
    Dump_akin (node_root, node_4);

    node_2 -> left = node_5;
    Dump_akin (node_root, node_5);

    node_2 -> right = node_6;
    Dump_akin (node_root, node_6);

    Close_File (Log_File);
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
void Dump_graph_recursive (node_akntr* node, size_t rank)
{
    if (!node) return;                                                                                                                    
    
    fprintf(Graph_File, ""
        "\tnode_%p [ shape = \"Mrecord\", label = \"{ data = %"TYPE" \\n addr: %p | { L:\\n addr: %p | R: \\n addr: %p } }\" ];\n", node, node -> data, node, node -> left, node -> right);

    fprintf (Graph_File, ""
        "\t{\n"                                                        
            "\t\tnode[ color = \"#58184PE\", shape = \"circle\", style = \"filled\" ,fillcolor=\"#fe5656\"];\n"
            "\t\tedge[ color = \"white\"]\n"
            "\t\t\"%zu\" ->  \"%zu\";\n", rank, rank + 1);
    
    fprintf (Graph_File,  "\t}\n\n"
        "\t{ rank = %zu; \"%zu\"; \"node_%p\" }\n", rank, rank, node);

    if (node -> left != NULL)
    {
        fprintf(Graph_File, "\n"
        "\tnode_%p[ shape = \"Mrecord\", label = \"{ data = %"TYPE"\\n addr: %p | { L:\\n addr: %p |   R: \\n addr: %p } }\" ];\n", node -> left,  node -> left -> data, node -> left, node -> left -> left, node -> left -> right);
        fprintf (Graph_File, ""
        "\tnode_%p  -> node_%p;\n", node, node -> left);
    }

    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_l_null_%p[ shape = \"ellipse\", label = \"null\" ];\n", node);
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_l_null_%p;\n", node, node);
        fprintf(Graph_File, ""
            "\t}\n");
        }  

    if (node -> right != NULL)
    {
        fprintf(Graph_File, "\n"   
            "\tnode_%p [ shape = \"Mrecord\", label = \" { data = %"TYPE"\\n addr: %p | { L:\\n addr: %p | R: \\n addr: %p } }\" ];", node -> right, node -> right -> data, node -> right, node -> right -> left, node -> right -> right);
        fprintf(Graph_File, "\n"
            "\tnode_%p  -> node_%p;\n", node, node -> right);
    }

    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_r_null_%p [shape = \"ellipse\", label = \" null\" ];\n", node);
        
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_r_null_%p;\n", node, node);
        fprintf(Graph_File, "" 
            "\t}\n");
          }

        fprintf (Graph_File, ""
        "\t{\n"                                                        
            "\t\tnode[ shape = \"plaintext\", style = \"filled\" ,fillcolor=\"white\"];\n"
            "\t\tedge[ color = \"white\"]\n"
            "\t\t\"%zu\" ->  \"%zu\";\n", rank, rank + 1);

        fprintf (Graph_File, ""
        "\t}\n\n");

        ++rank;

        Dump_graph_recursive (node -> left, rank);
        Dump_graph_recursive (node -> right, rank);

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
void Dump_graph_init (node_akntr* node, node_akntr* new_node)
{
    fprintf (Graph_File, "digraph\n" 
    "{\n"
    
    "\trankdir = TB;\n"
        "\tnode [ color = \"#004b00\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f8a4\"];\n"
        "\tedge [ color = \"#004b00\", fontsize = 16];\n\n");

    Dump_graph_recursive (node, 1);

    fprintf(Graph_File, "\n"   
            "\tnode_%p [ fillcolor = \"#ffa615\"];\n", new_node);

    fprintf (Graph_File, "}");
}
//====================================================================================================================================
int Dump_akin (node_akntr* node, node_akntr* new_node)
{
    Graph_File = Create_file ("Dot.txt");
    static size_t number_pic = 1;
    
    char* name_cmd = (char*) calloc (64, sizeof (char));
    char* name_pic = (char*) calloc (16, sizeof (char));

    sprintf (name_cmd, "dot Dot.txt -Tpng -o Picture_tree/tree_%zu.png", number_pic);
    sprintf (name_pic, "tree_%zu.png", number_pic);

    Dump_in_line (node);
    Dump_graph_init (node, new_node);

    Close_File (Graph_File);
    system (name_cmd);

    fprintf (Log_File ,"\n<img src = Picture_tree/\"%s\" width = %d%%>\n\n\n\n\n\n\n\n\n\n", name_pic, SCALE);
    fflush (Graph_File);
    ++number_pic;
    
    free (name_cmd);
    free (name_pic);

    return 0;
}
//====================================================================================================================================
void Insert (node_akntr* node, el_t value)
{
    node_akntr* new_node = 0;
    if (!node) return;

    while (1)
    {
        if (value < node -> data)
        {
            new_node = node -> left;
            if (!new_node)
            {
                node -> left = Create_node (value);
                return;
            }
            node = new_node;
        }
        else 
        {
            new_node = node -> right; 
            if (!new_node) 
            {
                node -> right = Create_node (value); 
                return;
            }
            node = new_node;
        }   
    }
}
//====================================================================================================================================

