#define TX_COMPILED
#include "..\SuperLibs\TXLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "..\Processor\Onegin_for_proc\Onegin_processing.h"
#include "..\Processor\Onegin_for_proc\Onegin_General.h"
#include "..\Processor\Onegin_for_proc\Print.h"
#include "akinator.h"


extern FILE* Log_File;
extern FILE* Graph_File;
extern FILE* Graph_File_Utf8;

//====================================================================================================================================
int main (int argc, char* argv[])
{
    Log_File = Create_file ("LOG_AKINATOR.html");
    fprintf (Log_File, "<pre>");
    //system ("mkdir Picture_tree");

    ONEGIN onegin_data = {};
    Check_argc (argc);

    onegin_data.name = argv[1];
    onegin_data.fsize = file_size (argv[1]);
    Check_fsize (onegin_data.fsize);

    Read_File (&onegin_data); 

    //Strings_Number (&onegin_data);
    //Address_String (&onegin_data);

    DBG_Print (&onegin_data);

    /*node_akntr* node_root = Create_node ("Квадробер?");
    node_akntr* node_1 = Create_node ("Дед");
    node_akntr* node_2 = Create_node ("Животное?");
    node_akntr* node_3 = Create_node ("На физтехе?");
    node_akntr* node_4 = Create_node ("Ведёт матан?");
    node_akntr* node_5 = Create_node ("Свинья");
    node_akntr* node_6 = Create_node ("Овчос");

    node_root -> left = node_1;
    Dump_akin (node_root, node_1);

    node_root -> right = node_2;
    Dump_akin (node_root, node_2);

    node_2 -> left = node_3;
    Dump_akin (node_root, node_3);

    node_2 -> right = node_4;
    Dump_akin (node_root, node_4);

    node_3 -> left = node_5;
    Dump_akin (node_root, node_5);

    node_4 -> right = node_6;
    Dump_akin (node_root, node_6);

    //Insert_akinator (node_root);
    Dump_akin (node_root, node_root);*/

    node_akntr* node_root = 0;

    Read3 (&onegin_data, argv[1], &node_root);
    $(node_root);
    Dump_akin (node_root, node_root);
    Dump_akin (node_root, node_root);


    Close_File (Log_File);
    txDisableAutoPause ();

    DBG_Print (&onegin_data);

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
        fprintf (stdout, "ERROR in open file\n %s", name_of_file);
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
    if (!node) return 1;
    assert (new_node);

    Graph_File = Create_file ("Dot.txt");
    Graph_File_Utf8 = Create_file ("Dot_UTF-8.txt");

    static size_t number_pic = 1;
    
    
    char* name_cmd = (char*) calloc (64, sizeof (char));
    char* name_pic = (char*) calloc (16, sizeof (char));

    snprintf (name_cmd, 64, "dot Dot_UTF-8.txt -Tsvg -o Picture_tree/tree_%zu.svg", number_pic);
    snprintf (name_pic, 16, "tree_%zu.svg", number_pic);

    Dump_in_line (node);
    Dump_graph_init (node, new_node);

    Close_File (Graph_File);
    Close_File (Graph_File_Utf8);

    system ("D:/Приложения/iconv/gettext-iconv/bin/iconv.exe -f CP1251 -t UTF-8 Dot.txt > Dot_UTF-8.txt");
    system (name_cmd);

    fprintf (Log_File ,"\n<img src = \"Picture_tree/%s\" width = %d%%>\n\n\n\n\n\n\n\n\n\n", name_pic, SCALE);
    fflush (Graph_File);
    $(number_pic);
    ++number_pic;

    //fprintf (Log_File, "<b><font color = #b2b2b2><font size = \"7\"> _______________________________________________________________________________________________________________________________________________________________________\n</font size></font></b>");
    //fprintf (Log_File, "<b><font color = #8080ff><font size = \"3\"> /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n</font size></font></b>");
    //fprintf (Log_File, "<b><font color = #b2b2b2><font size = \"7\"> ________________________________________________________________________________________________________________________________________________________________________\n</font size></font></b>");

    
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
void Insert_akinator (node_akntr* node)
{
    if (!node) return;
    char* object = (char*) calloc (256, sizeof (char));

    printf ("Hello! Welcome to the akinator programm !\n"
            "Enter the object you want to guess: ");

    if ((scanf ("%s", object    )) != 1) {printf ("You put wrong data, try again...\n");}
    getchar ();
    if (strcmp (object, node -> data) == 0)
    printf ("I guess your object ! It's %s !", node -> data);

    node_akntr* new_node = 0;
    if (!node) return;
  
    while (1)
    {
        printf ("That is %s ?\n", node -> data);
        printf ("Enter [Y]/[N] - \"yes\"/\"no\"\n");
        char temp_str = 0; 
        scanf ("%c", &temp_str);
        getchar();

        if (toupper (temp_str) == 'Y')
        {
            new_node = node -> left;
            if (!new_node)
            {
                node -> left = Create_node (object);
                return;
            }
            node = new_node;
        }

        else if (toupper (temp_str) == 'N')
        {
            new_node = node -> right; 
            if (!new_node) 
            {
                node -> right = Create_node (object); 
                return;
            }
            node = new_node;
        } 

        else 
        {
            printf ("Wrong, input, enter [Y] or [N]\n");
            continue;
        }
    }
}
//====================================================================================================================================
node_akntr* Read3 (ONEGIN* onegin, const char* name_base_file, node_akntr** node_root)
{
    assert (onegin);
    assert (name_base_file);
    static size_t counter = 1;

    if (onegin -> buffer_addr[0] != '{')
        return 0;

    else
    {   
        printf ("onegin -> buffer_addr[0] = <%c>\n", onegin -> buffer_addr[0]);
        onegin -> buffer_addr = Skip_space (onegin -> buffer_addr);
        printf ("onegin -> buffer_addr[0] = <%c>\n", onegin -> buffer_addr[0]);
        if (*onegin -> buffer_addr != '\"'){
            printf ("here\n");
            return 0;}  
        else
        {
            printf ("QWA QWA QWA\n");
            char* addr_cavich = strchr (onegin -> buffer_addr, '\"');         //addr '" Qvadrober' 

            if (addr_cavich != NULL)
            {
                onegin -> buffer_addr = addr_cavich + 1;                      //addr buff == Q
                printf ("%c\n",  onegin -> buffer_addr[0]);

                char* addr_cavich_end = strchr (onegin -> buffer_addr, '\"');
                printf ("%c\n",  *(addr_cavich_end - 1));

                *addr_cavich_end = '\0';                                         //'..er \0'
                $(*addr_cavich) ;
                node_akntr* node = Create_node (addr_cavich + 1);
                fprintf (Log_File, "Я добавил узел: %s\n", addr_cavich + 1);
                printf ("%s\n", addr_cavich + 1);

                onegin -> buffer_addr = addr_cavich_end + 1;
                onegin -> buffer_addr = Skip_space (onegin -> buffer_addr);

                $(onegin -> buffer_addr[0]);

                node -> left  = Read3 (onegin, name_base_file, node_root);
                node -> right = Read3 (onegin, name_base_file, node_root);

                if (counter == 1) *node_root = node;
                $(counter);
                
                ++counter;
                return node;
            }
        }
    }
}     
//====================================================================================================================================
char*   Skip_space (const char* ptr) 
{
    ++ptr;
    while (1)
        if (*ptr == ' ' || *ptr == '\r' || *ptr == '\n')
            ++ptr;
        else break;
    
    return (char*) ptr;
}