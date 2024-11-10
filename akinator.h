#pragma once

typedef int el_t;

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
void Dump_graph_init (node_akntr* node);
void Dump_graph_recursive (node_akntr* node);
void Dump_in_line (node_akntr* node);
FILE* Close_File (FILE* file);

#define TYPE "d"