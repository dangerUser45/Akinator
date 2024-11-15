#pragma once

#define DEBUG 1

#if  (DEBUG == 1) 
    #define DBGAKN( ... ) __VA_ARGS__
#else 
    #define DBGAKN( ... )
#endif

FILE* Log_File = 0;
FILE* Graph_File = 0;
FILE* Graph_File_Utf8 = 0;

typedef const char* el_t;    

struct node_akntr
{
    el_t data;
    node_akntr* left;
    node_akntr* right;
};

struct akinator
{
    el_t* root_node;
};

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
void Print3 (node_akntr* node_root);

#define TYPE "s"

const int SCALE = 50;

