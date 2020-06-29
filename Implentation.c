#include <stdio.h>
#include <stdlib.h>
#include "header.h"

Node* createnode(int data)
{
    Node *new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    return new;
}

List* initialize()
{
    List* l = (List*)malloc(sizeof(List));
    l->head = NULL;
    l->no_of_nodes = 0;
    return l;
}

void insert(List* sll, int data)
{
    Node *temp = createnode(data);
    if(!sll->head)
    {
        sll->head = temp;
    }
    else
    {
        Node *curr = sll->head;
        while(curr->next)
        {
            curr = curr->next;
        }
        curr->next = temp;
    }
    sll->no_of_nodes++;
}
void delete(List *sll, int key)
{
    Node *curr = sll->head;
    Node *prev = NULL;
    while((curr!=NULL) && (curr->data!=key))
    {
        prev = curr;
        curr = curr->next;
    }
    if(key == curr->data)
    {
        if(prev)
        {
            prev->next = curr->next;
        }
        else
        {
            sll->head = curr->next;
        }
        free(curr);
        curr = NULL;
        sll->no_of_nodes--;
    }
    else
    {
        return -1;
    }
}

int search(List *sll, int key)
{
    Node *curr = sll->head;
    int pos = 1;
    while(curr!=NULL)
    {
        if(key == curr->data)
        {
            return pos;
        }
        pos++;
    }
    return -1;
}

void print(List *sll)
{
    Node *temp = sll->head;
    while(temp)
    {
        print("%d ", temp->data);
        temp = temp->next;
    }
}
