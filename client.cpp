#include<iostream>
#include "deque.h"
#include<thread>
#include<vector>

using namespace std;

// 1. Enqueue front
// 2. Enqueue back
// 3. Dequeue front
// 4. Dequeue back
// 5. Display

int main() {
    Deque deque;
    int choice = 0;
    int data;
    vector<thread> threads;
    do {
        cin >> choice;
        switch(choice){
            case 1: 
                cin >> data;
                threads.push_back(thread(&Deque::enqueueFront, &deque, data));
                break;
            case 2: 
                cin >> data;
                threads.push_back(thread(&Deque::enqueueBack, &deque, data));
                break;
            case 3: 
                threads.push_back(thread(&Deque::dequeueFront, &deque));
                break;
            case 4: 
                threads.push_back(thread(&Deque::dequeueBack, &deque));
                break;
            case 5: 
                threads.push_back(thread(&Deque::display, &deque));
                break;
            default: choice = 0;
        }
    } while(choice);
    for(vector<thread>::iterator i = threads.begin(); i != threads.end(); ++i)
        i->join();
    return 0;
}
