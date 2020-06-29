struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;

struct list
{
    struct node* head;
    int no_of_nodes;
};
typedef struct list List;

Node* createnode(int);
void insert(List*, int);
void delete(List*, int);
void search(List*, int);
void print(List*)
