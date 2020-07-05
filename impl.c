#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <inttypes.h>
#define NUM_OF_THREADS 1000

int t_count = 0;

typedef struct node
{
    int data;
    struct node *next;
    pthread_mutex_t lock;                                   // Mutex variable 'lock' is a part of every node to maintain consistency.
}Node;

struct node *head = NULL;
struct node *tail = NULL;
pthread_mutex_t ins_lock = PTHREAD_MUTEX_INITIALIZER;       // ins_lock is a mutex variable to be used when inserting into an empty list.
pthread_mutex_t paracheck = PTHREAD_MUTEX_INITIALIZER;      // paracheck is used to ensure consistency of the operations on the data structure

Node* createnode(int);
void* insert_rear(void*);
void* display_list();
void* search(void*);
void* delete(void*);

Node* createnode(int data)
{
    Node *new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    pthread_mutex_init(&new->lock, NULL);                   // Every node is initialised to be in the unlocked state.
    return new;
}

void* insert_rear(void* data)
{
    if(head != NULL)
    {
        pthread_mutex_lock(&head->lock);
        pthread_mutex_unlock(&paracheck);                   // Unlock to allow other threads to start the exec of their functions.
    }
    int key = (intptr_t)data;
    Node *new = createnode(key);
    if(head == NULL)
    {
        pthread_mutex_lock(&ins_lock);
        pthread_mutex_unlock(&paracheck);                   // Unlock to allow other threads to start the exec of their functions.
        head = tail = new;
        pthread_mutex_unlock(&ins_lock);
    }
    else
    {
        Node *curr = head;
        while(curr->next != NULL)
        {
            pthread_mutex_lock(&curr->next->lock);          // The thread traverses throught the list by first locking the next node
            pthread_mutex_unlock(&curr->lock);              // And then unlocking the current node
            curr = curr->next;
        }
        curr->next = new;
        tail = new;
        pthread_mutex_unlock(&curr->lock);
    }
    return NULL;
}

void* display_list()
{
    pthread_mutex_lock(&head->lock);
    pthread_mutex_unlock(&paracheck);                       // Unlock paracheck to allow other threads to start the exec of their functions.
    Node *temp = head;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        if(temp->next)                                      // The thread traverses through the sll by locking the next node
        {
            pthread_mutex_lock(&temp->next->lock);
        }
        pthread_mutex_unlock(&temp->lock);                  // And unlocking the current node.
        temp = temp->next;
    }
    printf("\n");
    return NULL;
}


void* search(void* data)
{
    int key = (intptr_t)data;
    int offset = 1;
    Node *temp = head;
    pthread_mutex_lock(&temp->lock);
    pthread_mutex_unlock(&paracheck);                       // Unlock paracheck to allow other threads to start exec of their functions
    while(temp != NULL)
    {
        if((key) == temp->data)
        {
            printf("%d\n", offset);
            pthread_mutex_unlock(&temp->lock);
            return NULL;
        }
        if(temp->next)                                      // The thread traverses through the sll by first locking the next node
        {
            pthread_mutex_lock(&temp->next->lock);
        }
        pthread_mutex_unlock(&temp->lock);                  // And then unlocking the current node.
        temp = temp->next;
        offset++;
    }
    printf("-1\n");
    return NULL;
}

void* delete(void* data)
{
    if(head)
    {
    	int key = (intptr_t)data;
    	Node *temp = head;
    	Node *prev = NULL;
    	pthread_mutex_lock(&temp->lock);
    	pthread_mutex_unlock(&paracheck);                   // Unlock paracheck to allow other threadsto execute their functions.
    	while((temp!=NULL) && (temp->data!=key))
    	{
        	prev = temp;
        	if(temp->next)                                  // The thread traverses through the sll by first locking the next node                             
        	{	
        		pthread_mutex_lock(&temp->next->lock);
        	}
        	pthread_mutex_unlock(&temp->lock);              // And then unlocking the current node.
        	temp = temp->next;
    	}
    	if(temp)
    	{
        	if(prev)
        	{
            	prev->next = temp->next;
        	}
        	else
        	{
            	head = temp->next;
        	}
        	free(temp);
        	temp = NULL;
    	}
    	else
    	{
            printf("-1\n");
    	}
    }
    else
    {
    	pthread_mutex_unlock(&paracheck);
        printf("-1\n");
    }
    return NULL;
}

int main()
{
	int opt;
	pthread_t threads[NUM_OF_THREADS];
	while(t_count<NUM_OF_THREADS)
	{
		scanf("%d",&opt);
		intptr_t key;
		switch(opt)
		{
			case 1:
				scanf("%ld",&key);
				pthread_mutex_lock(&paracheck);                                         // paracheck is locked to ensure this thread enters its function call first, to maintain consistency.
				pthread_create(&threads[t_count++], NULL, insert_rear, (void*)key );    // a thread is created for the insert function.
				break;
			case 2:
				scanf("%ld",&key);
				pthread_mutex_lock(&paracheck);
				pthread_create(&threads[t_count++], NULL, delete, (void*)key );
				break;
			case 3:
				scanf("%ld",&key);
				pthread_mutex_lock(&paracheck);
				pthread_create(&threads[t_count++], NULL, search, (void*)key );
				break;
			case 4:
				pthread_mutex_lock(&paracheck);
				pthread_create(&threads[t_count++], NULL, display_list, NULL );
				break;
			case 0:
                for(int i = 0; i < t_count; ++i)                                        // To ensure the program doesn't exit before the completion of all threads.
            		pthread_join(threads[i], NULL);
                exit(0);	
        }
    }
    for(int i = 0; i < t_count; ++i)                                                    // To ensure the program doesn't exit before the completion of all threads.
        pthread_join(threads[i], NULL);
    return 0;
}







































