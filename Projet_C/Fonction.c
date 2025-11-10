#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n{
    int data;
    n *next;
}Node;

void insert(Node *head, Node  *insert, int value){
    Node *n = head;
    while(n != NULL){
        if(n.data == value){
            Node *tmp = n->next;
            n->next = insert;
            insert->next = tmp;
            break;
        }
        n = n->next;
    }
}