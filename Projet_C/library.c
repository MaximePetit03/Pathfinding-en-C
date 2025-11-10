#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"


int error_file() {
    FILE *file = fopen("file.txt", "r");
    if (file == NULL){
        printf("Erreur %d : FILE_NOT_FOUND\n", FILE_NOT_FOUND);
        return FILE_NOT_FOUND;
    } 
    return 0;
}

int error_no_start(StartEnd limits) {
    if (limits.start == 0) {
        printf("Erreur %d : NO_START_NODE\n", NO_START_NODE);
        return 1;
    }
    return 0;
}

int error_no_end(StartEnd limits) {
    if (limits.end == 0) {
        printf("Erreur %d : NO_END_NODE\n", NO_END_NODE);
        return 1;
    }
    return 0;
}

int error_bad_format(int node, int link) {
    if (node == 0 || link == 0) {
        printf("Erreur %d : BAD_FILE_FORMAT\n", BAD_FILE_FORMAT);
        return BAD_FILE_FORMAT;
    }
    return 0;
}
//print node
int print_node(){
    FILE *file = fopen("file.txt", "r");
    char array[256];
    int nodes = 0;
    
    while(fgets(array, sizeof(array), file) != NULL){
        for(int i = 0; array[i] != '\0'; i++){
            if ((array[i] != ' ' && array[i] != '\n' && array[i] != '\t' ) &&
            (i == 0 || array[i - 1] == ' ' || array[i - 1] == '\n' || 
            array[i - 1] == '\t') && (array[i] != '#' &&
            array[i + 1] != '-' )) {
                nodes++;
            }
        }
    }
    fclose(file);
    return nodes;
}

//print node links
int print_link(){
    FILE *file = fopen("file.txt", "r");
    char array[256];
    int links = 0;
    if (file == NULL){
        return 1;
    }
    while(fgets(array, sizeof(array), file) != NULL){
        for(int i = 0; array[i] != '\0'; i++){
            if ((array[i] != ' ' && array[i] != '\n' && array[i] != '\t' 
                && (array[i] > 1 && array[i] < 255 && array[i + 1] =='-')) &&
                (i == 0 || array[i - 1] == ' ' || array[i - 1] == '\n' || 
                array[i - 1] == '\t') && (array[i] != '#')) {
                    links++;
            }
        }
    }
    printf("links: %d\n", links);
    fclose(file);
    return links;
}

StartEnd print_limits(){
    FILE *file = fopen("file.txt", "r");
    char array[256];
    StartEnd result = {0, 0};
    if (file == NULL){
        printf("Erreur de fichier\n");
        return result;
    }
    while(fgets(array, sizeof(array), file) != NULL){
        if (strstr(array, "#start")){
            if (fgets(array, sizeof(array), file) != NULL)
            result.start = atoi(array);
        }
        else if (strstr(array, "#end")){
            if (fgets(array, sizeof(array), file) != NULL)
            result.end = atoi(array);
        }
    }
    fclose(file);
    return result;
}

int check_node(char *array, int number, int *node, int *link){
    
    if (strstr(array, "#node")) {
        *node = 1;
        return 0;
    } else if (strstr(array, "#links")) {
        *link = 1;
        return 1;
    }
    return number;
}

int add_nodes(char *array, int i, int number, int nodes, Node **graph){
    if (number == 0 && i < nodes) {
        if (array[0] == '\n' || array[0] == '\0' || array[0] == '#'){
        return 1;
        }
        int id = atoi(array);
            if (id > 0) { // only numbers
                graph[i] = malloc(sizeof(Node));
                graph[i]->id = id;
                graph[i]->links = NULL;
                return 0;
            }
    }
    return 1;
}
void find_link(char *array, Node **graph, int nodes) {
    int i = 0;
    // Find '-'
    while (array[i] != '-' && array[i] != '\0' && array[i] != '\n')
        i++;

    array[i] = '\0'; // Cut the number(a-b) by two numbers(a et b)
    int id1 = atoi(array);
    int id2 = atoi(&array[i + 1]);

    //Find nodes
    Node *node1 = NULL;
    Node *node2 = NULL;
    for (int j = 0; j < nodes; j++) {
        if (graph[j]->id == id1)
            node1 = graph[j];
        else if (graph[j]->id == id2)
            node2 = graph[j];
    }
    add_links(node1, node2);
}
// add the links
void add_links(Node *node2, Node *node1) {
    int i = 0;
    if (!node1->links) { // Link node1 to node2 (file.txt : node1-node2)
        node1->links = malloc(2 * sizeof(Node*));
        node1->links[0] = node2;
        node1->links[1] = NULL;
    } else {
        while (node1->links[i]) i++; // Link node1 to node3 if exist
        node1->links = realloc(node1->links, (i + 2) * sizeof(Node*));
        node1->links[i] = node2;
        node1->links[i + 1] = NULL;
    }
    i = 0;
    if (!node2->links) { // Link node2 to node1 (bidirectional)
        node2->links = malloc(2 * sizeof(Node*));
        node2->links[0] = node1;
        node2->links[1] = NULL;
    } else {
        while (node2->links[i]) i++; //Same else but in the opposite direction
        node2->links = realloc(node2->links, (i + 2) * sizeof(Node*));
        node2->links[i] = node1;
        node2->links[i + 1] = NULL;
    }
}
//initialize the links between nodes
Node** init_node(char *filename){
    int nodes = print_node();
    printf("nodes: %d\n", nodes);
    char array[256];
    int i = 0, number = 1, node = 0, link = 0;
    Node **graph = malloc(nodes * sizeof(Node* ));
    FILE *file = fopen(filename, "r");

    while (fgets(array, sizeof(array), file) != NULL) {
        if (array[0] == '#') {
            number = check_node(array, number, &node, &link);
            continue;
        }
        
        int added = add_nodes(array, i, number, nodes, graph);
        if (added == 0) {
            i++;
        } else if (number == 1) {
            find_link(array, graph, nodes);
        }

    }
    if (error_bad_format(node, link) == BAD_FILE_FORMAT)
        return NULL;
    fclose(file);
    return graph;
}

// Find link no visited while links not NULL and if a link exists
Node* check_link(Node *current, Node **seen, int count){
    for (int i = 0; current->links && current->links[i]; i++) {
        int node_seen = 0;
        for (int j = 0; j < count; j++)
            if (current->links[i] == seen[j])
                node_seen = 1;
        if (!node_seen)
            return current->links[i]; // renvoie le prochain non visité
    }
    return NULL; // aucun lien disponible
}
//print pathfinding
void display_nodes(Node *start) {
    printf("pathfinding: \n");
    Node *current = start;
    Node *seen[100];  // noode's array already visited
    int count = 0;

    while (current) {
        printf("%d ", current->id);
        seen[count++] = current;
        Node *next = NULL;
        next = check_link(current, seen, count);
        current = next;
    }
    printf("\n");
}
/*
//detect and print isolated nodes
Node** get_unconnected_nodes(Node **nodes, int size, Node *head ){

}
*/