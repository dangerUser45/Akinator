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

struct akinator
{
    node_akntr** root_node;
    ONEGIN* onegin_data;
    FILE* base;
};

akinator* Akin_init (int argc, char* argv[]);
FILE*  Create_file (const char* name_of_file);
node_akntr* Create_node (el_t data);
void Dump_graph_init (node_akntr* node, node_akntr* new_node);
void Dump_graph_recursive (node_akntr* node, size_t rank);
void Dump_in_line (node_akntr* node);
FILE* Close_File (FILE* file);
int Dump_akin (node_akntr* node, node_akntr* new_node);
void Insert (node_akntr* node, el_t value);
void Insert_akinator (node_akntr* node);
node_akntr* Read3 (ONEGIN* onegin, const char* name_base_file, node_akntr** node_root);
char* Skip_space (const char* ptr);
node_akntr* Print3 (node_akntr* node);
void Print_tab (size_t cnt, FILE* file_ptr);
void Free_akin (akinator* akin_data);


#define TYPE "s"

const int SCALE = 50;


//TODO fix all free
// 