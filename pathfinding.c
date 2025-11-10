#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main() {
    if (error_file() == FILE_NOT_FOUND)
        return FILE_NOT_FOUND;

    StartEnd limits = print_limits();
    if (error_no_start(limits) || error_no_end(limits))
        return 1;

    Node **graph = init_node("file.txt");
    int nodes = print_node();
    Node *start = NULL;
    print_link();
    for (int i = 0; i < nodes; i++) {
        if (graph[i]->id == limits.start)
            start = graph[i];
    }
    printf("start: %d\n", limits.start);
    printf("end: %d\n", limits.end);
    display_nodes(start);
    return 0;
}