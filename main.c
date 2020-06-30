#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	List *sll;
	sll = initialize();
	
	while(1) {
		/*printf("Enter 1 to insert: \n");
		printf("Enter 2 to delete: \n");
		printf("Enter 3 to search: \n");
		printf("Enter 4 to display: \n");
		printf("Enter 0 to exit\n");*/
		printf("Enter your choice : \n");
		int choice;
		scanf("%d",&choice);
		
		if(choice==1) {
			int newnode;
			printf("Enter the new node \n");
			scanf("%d",&newnode);
			insert(sll, newnode);
		}
		
		else if(choice==2) {
			int delnode;
			printf("Enter the node to be deleted\n");
			scanf("%d",&delnode);
			int node_deleted = delete(sll, delnode);
			if(node_deleted == -1 )
				printf("Element to be deleted is not present\n");
		}
		
		else if(choice==3) {
			int searchnode;
			printf("Enter the node to be searched\n");
			scanf("%d",&searchnode);
			int position;
			position = search(sll, searchnode);
			if(position == -1)
				printf("The element is not found in the list\n");
			else 
				printf("%d\n",position);				
		}
		
		else if(choice==4) {
			print(sll);
		}
		
		else if(choice==0) {
			break;
		}
		else {
			continue;
		}
	}
	
	return 0;
}