ReadME File :-

This is a concurrent implementation of singly linked lists in C language.
It has been implemented using pthreads present in the <pthread.h> header file.

The functions that can be performed by this are:
	1)INSERT - inserting at the end of the linked list
	2)DELETE - deleting an item from the linked list
			   (returns -1 if element is not present)
	3)SEARCH - searches for an element and gives its position from head 
			   (considering head to be at position 1)
			   (returns -1 if element is not present)
	4)PRINT -  prints the linked list from head to tail
	
It has been implemented using a menu-based system:

First the function to be performed needs to be entered :-

Enter 1 to : INSERT       (performed by "insert_rear" function)
Enter 2 to : DELETE       (performed by "Delete" function)
Enter 3 to : SEARCH       (performed by "search" function)
Enter 4 to : DISPLAY      (performed by "display_list" function)

If 1, 2, or 3 is the option chosen, then the item needed to be inserted, deleted, or 
searched needs to be entered.

For example :-

To have the following linked list :- 2->3->5
Enter:
1
2
1
3
1
5

To display the linked list :-
Enter:
4
Output:
	|2|    |3|    |5|

To delete an element (for example 2) from the linked list :-
Enter:
2
2

To search an element (for example 3) :-
Enter:
3
3
Output:
2
 
			   
It is input and output redirect-able.   

INPUT-REDIRECTION :
	
There are three test-files provided namely test1.txt, test2.txt, test3.txt.
In order to run the code the commands to be entered on the terminal are :
1)gcc sll.c -lpthread
2)./a.out <test1.txt
		or
  ./a.out <test2.txt
		or
  ./a.out <test3.txt
  
OUTPUT-REDIRECTION :
In order to run the code the commands to be entered on the terminal are:
1)gcc sll.c -lpthread
2)./a.out >outputfile.txt

