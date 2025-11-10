#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    BAD_FILE_FORMAT = 4,
} Error;

typedef struct n{
    int id;
    struct n **links;
} Node;

typedef struct {
    int start;
    int end;
} StartEnd;

int error_file();

int error_no_start(StartEnd limit);

int error_no_end(StartEnd limits);

int error_bad_format(int node, int link);

//print node
int print_node();

//print node links
int print_link();

//print the start node and the end node
StartEnd print_limits();

//check if they are tags or numbers
int check_node(char *array, int number, int *node, int *link);

int add_nodes(char *array, int i, int number, int nodes, Node **graph);

//find links in the file.txt
void find_link(char *array, Node **graph, int nodes);

// add the links
void add_links(Node *node1, Node *node2);

//initialize the links between nodes
Node** init_node(char *filename );

// Find link no visited while links not NULL and if a link exists
Node* check_link(Node *current, Node **seen, int count);

//Print pathfinding
void display_nodes(Node* start);
/*
//detect and print isolated nodes
node** get_unconnected_nodes( Node **nodes, int size, Node *head );
*/