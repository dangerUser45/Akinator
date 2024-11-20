#pragma once

#define DEBUG 1

#if  (DEBUG == 1) 
    #define DBGAKN( ... ) __VA_ARGS__
#else 
    #define DBGAKN( ... )
#endif

typedef const char* el_t;    

struct node_akntr
{
    el_t data;
    node_akntr* left;
    node_akntr* right;
};

struct list_node 
{
    node_akntr* node;
    short* path;
};

struct akinator
{
    node_akntr** root_node;
    ONEGIN* onegin_data;
    FILE* base;
    list_node* list_array;
    size_t n_lists;
};

enum input_akin {GUESS = 1, COMPARE, DEFINITION, EXIT_AKIN, YES, NO};
enum list       {LEFT = 0, RIGHT = 1};

akinator* Akin_init (int argc, char* argv[]);
FILE*  Create_file (const char* name_of_file);
node_akntr* Create_node (el_t data);
void Dump_graph_init (node_akntr* node, node_akntr* new_node);
void Dump_graph_recursive (node_akntr* node, size_t rank);
void Dump_in_line (node_akntr* node);
void Close_File (FILE* file);
int Dump_akin (node_akntr* node, node_akntr* new_node);
void Insert (node_akntr* node, el_t value);
void Run_akinator (akinator* akin, node_akntr* node);
void Guess_Akin (node_akntr* node);
void Definition_Akin (akinator* akin);
void Insert_akin (node_akntr* old_node, node_akntr* node, char* object, char* temp_str, bool left);
node_akntr* Read3 (akinator* akin, const char* name_base_file, node_akntr** node_root);
char* Skip_space (const char* ptr);
node_akntr* Print3 (node_akntr* node);
void Print_tab (size_t cnt, FILE* file_ptr);
void Free_akin (akinator* akin_data);
void Dtor_akin (akinator* Akin_data);
int Check_input_akin (char* temp_str);
int My_Strcmp (const char* first_string, const char* second_string);
void Path_obtainig (node_akntr* node_root);

#define TYPE "s"

const int SCALE = 50;
const size_t INIT_NUM_LIST = 128;


//TODO fix all free
// 