#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OF_THREADS 1000

void* display_list();

int t_count = 0;

typedef struct node
{
    int data;
    struct node *next;
    pthread_mutex_t mut;
}Node;
/*
typedef struct list
{
    struct node *head;
    struct node *tail;
    int number_of_nodes;
}List;

List* list_initialize()
{
    List *new_l = (List*)malloc(sizeof(List));
    new_l->head = NULL;
    new_l->tail = NULL;
    new_l->number_of_nodes = 0;
    return new_l;
}

List sll = list_initialize(); 
*/

struct node *head = NULL;
struct node *tail = NULL;
int number_of_nodes = 0;

Node* createnode(int* data)
{
    Node *new = (Node*)malloc(sizeof(Node));
    new->data = *data;
    new->next = NULL;
    pthread_mutex_init(&new->mut, 0);
    return new;
}
void* insert_rear(void* value)
{
    int *key = (int*)value;
    Node *new = createnode(key);
    if(head == NULL)
    {
        head = tail = new;
    }
    else
    {
        pthread_mutex_lock(&tail->mut);
        Node *curr = head;
        while(curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = new;
        pthread_mutex_unlock(tail->mut);
    }
    tail = new;
    number_of_nodes++;
    return NULL;
}

void* display_list()
{
    Node *temp = head;
    while(temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    int opt;
    pthread_t threads[NUM_OF_THREADS];
    while(t_count < NUM_OF_THREADS)
    {
        //printf("Enter your choice: ");
        scanf("%d", &opt);
        //printf("\nInput received");
        int key;
        switch(opt)
        {
            case 1: 
                printf("Enter value: ");
                scanf("%d", &key);
                pthread_create(&threads[t_count++], NULL, insert_rear, (void*)&key );
                printf("\nInsertion complete");
                break;
            case 4:
                pthread_create(&threads[t_count++], NULL, display_list, NULL);
                break;
            case 0:
                for(int i = 0; i < t_count; ++i)
                {
                    pthread_join(threads[i], NULL);
                }
                exit(0);
        }
    }
    return 0;
}
