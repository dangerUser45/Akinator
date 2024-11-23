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
extern FILE* Base_File; 

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
    FILE* file = fopen (name_of_file, "w+"); DBGAKN($(name_of_file);)

    if (file == NULL)
    {
        fprintf (stdout, "ERROR in open file\n %s", name_of_file);
        return 0;
    }
    
    setvbuf (file, 0, 0, _IONBF);

    return file;
}
//====================================================================================================================================
void Close_File (FILE* file)
{
    if (file) fclose (file); 
    return;
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

    system ("D:\\Приложения\\iconv\\gettext-iconv\\bin\\iconv.exe -f CP1251 -t UTF-8 Dot.txt > Dot_UTF-8.txt");
    system (name_cmd);

    fprintf (Log_File ,"\n<img src = \"Picture_tree/%s\" width = %d%%>\n\n\n\n\n\n\n\n\n\n", name_pic, SCALE);
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
void Run_akinator (akinator* akin,  node_akntr* node)
{
    if (!node) return;

    printf ("Hello! Welcome to the akinator programm !\n"
            "What do you want to do?\n"
            "Enter :\n" 
            "[guess]    - start guessing\n"
            "[compare]  - compare two objects\n"
            "[define]   - define an object\n"
            "[exit]     - programm exit\n");    
    
    char* temp_str = (char*) calloc (256, sizeof (char));

    while (true)
    {
        scanf ("%[^\n]", temp_str);
        getchar ();
        int action = Check_input_akin (temp_str);

        switch (action)
        {
            case GUESS:
                Guess_Akin (node);
                printf ("What do you want to do next ?\n");
                break;
            
            case COMPARE:
                //Compare_Akin ();
                printf ("What do you want to do next ?\n");
                break;

            case DEFINITION:
                Definition_Akin (akin);
                printf ("What do you want to do next ?\n");
                break;

            case EXIT_AKIN:
                return;
        
            case 0:
                printf ("Wrong input, enter [Y] or [N]\n");
                continue;
                
            default:
                fprintf (Log_File, "ERROR IN Run_akinator(): line %d", __LINE__);
                break;
        }
    }

    free (temp_str);
}
//====================================================================================================================================
void Guess_Akin (node_akntr* node_root)
{
    assert (node_root);
    node_akntr* node = node_root;
    printf ("Guess any object and I will try to guess it !\n");
    
    node_akntr* old_node = 0;

    char* temp_str = (char*) calloc (10, sizeof (char));    
    char* object   = (char*) calloc (256, sizeof (char));

    while (1)
    {
        printf ("That is %s ?\n", node -> data);
        printf ("Enter [Y]/[N] - \"yes\"/\"no\"\n");

        scanf ("%[^\n]", temp_str); getchar ();
        int action = Check_input_akin (temp_str);
        bool left = true;

        if (action == YES)
        {
            left = true;
            if (!node -> left){
                if (node->right) {DBGAKN( fprintf (Log_File, "Error in Guess_Akin() line%d: wrong base", __LINE__);) fflush (Log_File); return; }
                printf ("Hooray! I got it!\n");
                return;}
            old_node = node; 
            node = node -> left;    
        }

        else if (action == NO)
        {
            left = false;
            if (!node -> right){
                if (node->left) {DBGAKN( fprintf (Log_File, "Error in Guess_Akin() line%d: wrong base", __LINE__);) fflush (Log_File); return; }
                Insert_akin (old_node, node, object, temp_str, left);
                node_akntr* node__ = node_root;
                //Print3 (node__);
                return;}
            old_node = node; 
            node = node -> right;
        }

        else 
        {
            printf ("Wrong input, enter [Y] or [N]\n");
            continue;
        }
    }   

    free (temp_str);
    free (object);
}
//====================================================================================================================================
void Insert_akin (node_akntr* old_node, node_akntr* node, char* object, char* temp_str, bool left)
{
    printf ("Who it was ?\n");
    scanf ("%[^\n]", object); getchar ();
    printf ("Do you wish to add a new item to the database ?\n Enter [Y] or [N]\n");

    while (true)
    { 
        scanf ("%[^\n]", temp_str); getchar ();
        int action = Check_input_akin (temp_str);

        switch (action)
        {
            case YES: {
                printf ("What's the difference between \"%s\" and \"%s\"?\n", object, node -> data  );
                char* different = (char*) calloc (256, sizeof (char));
                scanf ("%[^\n]", different); getchar ();

                node_akntr* new_node  = Create_node (object);
                node_akntr* diff_node = Create_node (different);


                if (left) old_node  -> left  = diff_node;
                else      old_node  -> right = diff_node;
        
                diff_node -> right = node;
                diff_node -> left  = new_node;
        
                DBGAKN(fprintf (Log_File, "old_node -> data: %s\n", old_node -> data);)
                DBGAKN(fprintf (Log_File, "old_node: %p\n", old_node);)

                DBGAKN(fprintf (Log_File, "old_node -> left -> data: %s\n", old_node -> left -> data);)
                DBGAKN(fprintf (Log_File, "old_node -> left %p\n", old_node -> left);)

                DBGAKN(fprintf (Log_File, "old_node -> right: %s\n", old_node -> right -> data);)
                DBGAKN(fprintf (Log_File, "old_node -> right -> data: %p\n", old_node -> right);)
                return;}
            
            case NO:
                return;

            default:   {
                printf ("Wrong input, enter [Y] or [N]\n");
                continue;}
        }
    }
}
//====================================================================================================================================
node_akntr* Read3 (akinator* akin, const char* name_base_file, node_akntr** node_root)
{
    assert (akin);
    assert (name_base_file);

    ONEGIN* onegin = akin -> onegin_data;
    static size_t counter = 0;

    fprintf (Log_File, "onegin -> buffer_addr[0] = %s\n", onegin -> buffer_addr);
    if (onegin -> buffer_addr[0] != '{')
        return 0;

    else
    {
        onegin -> buffer_addr = Skip_space (onegin -> buffer_addr + 1);

        if (*onegin -> buffer_addr != '\"')
        { 
            onegin -> buffer_addr = strchr (onegin -> buffer_addr, '{');
            DBGAKN (fprintf (Log_File, "пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, onegin -> buffer_addr = &lt;%.20s&gt;\n", onegin -> buffer_addr);)
            return 0;}  
        else
        {
            char* quote_pos     = strchr (onegin -> buffer_addr, '\"');        
            char* quote_pos_end = strchr (quote_pos + 1, '\"');
            
            *quote_pos_end = '\0';                                        
            DBGAKN (printf ("%c\n",  *(quote_pos_end - 1));
                    $(*quote_pos) ;)

            node_akntr* node = Create_node (quote_pos + 1);
            akin -> list_array[0].node = node;
            akin -> n_lists += 1;
           
            DBGAKN (fprintf (Log_File, "пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ: %s\n", quote_pos + 1);
            DBGAKN(fprintf (Log_File, "пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ: %p\n", node);))
            ++counter;

            onegin -> buffer_addr = quote_pos_end + 1;
            onegin -> buffer_addr = Skip_space (onegin -> buffer_addr);
            if (*onegin -> buffer_addr == '}')
            {
                onegin -> buffer_addr = strchr (onegin -> buffer_addr, '{');
                return node;
            }    

            if (counter == 1) {*node_root = node; fprintf (Log_File, "пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ\n");}   
            DBGAKN($(counter);)

            node -> left  = Read3 (akin, name_base_file, node_root);
            node -> right = Read3 (akin, name_base_file, node_root);

            return node;
            
        }
    }
}     
//====================================================================================================================================
char* Skip_space (const char* ptr) 
{
    while (1)
        if (*ptr == ' ' || *ptr == '\t' || *ptr == '\r' || *ptr == '\n' )
            ++ptr;
        else break;
    
    return (char*) ptr;
}
//====================================================================================================================================
node_akntr* Print3 (node_akntr* node)
{
    #define PT Print_tab (cnt, Base_File)

    static size_t cnt = 0;
    if (! node) return 0;
    fprintf (Base_File, "{ ");
    fprintf (Base_File, "\"%"TYPE"\"\n", node -> data); 

    ++cnt;

    if (!node -> left) { PT; fprintf (Base_File, "{}\n"); }
      else  { PT; Print3 (node -> left); }

    if (!node -> right) {PT; fprintf (Base_File, "{}\n"); }
    else { PT; Print3 (node -> right); } 

    --cnt;
    PT; fprintf (Base_File, "}\n");

    return 0;

    #undef PT
}
//====================================================================================================================================
void Print_tab (size_t cnt, FILE* file_ptr)
{
    for (size_t i = 0; i < cnt; ++i)
        fprintf (file_ptr, "\t");
}
//====================================================================================================================================
void Free_akin (akinator* Akin_data)
{
    assert (Akin_data);
    DBGAKN(printf ("Akin_data -> root_node = %p\n", Akin_data -> root_node   );
    printf ("*(Akin_data -> root_node) = %p\n", *(Akin_data -> root_node));
    printf ("Akin_data -> root_node[0] = %p\n", Akin_data -> root_node[0]);)

    free (Akin_data -> onegin_data);
    free (Akin_data);

    return;
}
//====================================================================================================================================
void Dtor_akin (akinator* Akin_data)
{
    txDisableAutoPause ();
    Free_akin (Akin_data);
    Close_File (Log_File);
    Close_File (Base_File);
}
//====================================================================================================================================
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
//====================================================================================================================================
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
//====================================================================================================================================
void Definition_Akin (akinator* akin)
{
    assert (akin);
    printf ("Here's a list of all the facilities:");

    for (size_t i = 0; i < akin -> n_lists; ++i)
        printf ("%zu) \"%s\"\n", i+1,akin -> list_array[i].node -> data);

    printf ("Name the object that needs to be defined\n");

    char* temp_str = (char*) calloc (256, sizeof (char));
    scanf ("%[^\n]", temp_str); getchar ();

    while (true)
    {
        scanf ("%[^\n]", temp_str); getchar ();

        for (size_t i = 0; i < akin -> n_lists; ++i)
            if (!strcmp (akin -> list_array[i].node -> data, temp_str))
               { Path_obtainig (akin -> list_array[i].node); return;}
            else {printf ("Incorrect input ! Try again\n");  continue;}
    }
}
//====================================================================================================================================
void Path_obtainig (node_akntr* node_root)
{

    return;
}
