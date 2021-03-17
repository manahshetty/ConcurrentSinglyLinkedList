This code is an implementation of Concurrent Singly Linked Lists using the pthread library.

### Execution

* LINUX distribution :
	`$gcc impl.c -lpthread`
	
	`$./a.out <t1.txt`
		OR
	`$./a.out <t2.txt`
		OR
	`$./a.out <t3.txt`

* Windows distribution :
	`$gcc impl.c`
	
	`$a <t1.txt`
		OR
	`$a <t2.txt`
		OR
	`$a <t3.txt`

### Working

The project implements a menu based system to implement the following functions:
	
1. INSERT - Inserts an element at the end of the list.
2. DELETE - Deletes an item from the list if present. 
	    (Returns -1 if element is not present)
3. SEARCH - Searches for an element and gives its offset from the head. Indexing is 1 based. (First node has position 1) 
	    (Returns -1 if element is not present)
4. PRINT -  Prints the linked list from head to tail
0. EXIT  -  Exits the program.
	

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
2 3 5

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
 			   

#### FUNCTION / IMPLEMENTATION :

A thread/process is created for every function called. This has been done using the 'pthread_create function'.

Mutexes have been placed on every node to ensure consistency of the data structures. There is an in-built type in the pthread library called pthread_mutex_t.
They can be locked or unlocked using the functions 'pthread_mutex_lock(&lock_variable)' and 'pthread_mutex_unlock(&lock_variable)'.

Mutex variables ins_lock and paracheck are also in place for the same.
* The mutex ins_lock is used when inserting the first node/ into an empty list since there are no locks on the list at this stage, since the list does not exist.
* The mutex paracheck is locked before every function lock and unlocked on entering the function and locking the head of the list. This is done to maintain the consistency in the order in which the functions are called. If not in effect, a delete process may initiate before insert and so on.
* Finally, there are mutex locks on every node of the linked list.

Each of the functions; insert_rear, delete, search, display_list have been implemented normally with mutex locking during traversal. Traversal follows 'hand-over' locking where the thread first locks the next node and then unlocks the current node, leaving the current node free to be accessed or modified by the other threads. This efficiently takes care of race conditions and deadlocks.

Finally, pthread_join(&thread_variable) is called before exit to ensure that all the pthreads finish execution before main exits.

Thus, by creating a thread for every function called, the operations have all been parallelized while maintaining consistency.

### Thus, a concurrent implementation of singly linked lists is realized.
