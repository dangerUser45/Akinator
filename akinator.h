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

int  Create_file (const char* name_of_file, FILE* file);
node_akntr* Create_node (el_t data);
void Dump_graph (node_akntr* node);
void Dump_in_line (node_akntr* node);

#define TYPE "d"