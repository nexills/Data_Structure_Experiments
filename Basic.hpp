# include "LinkedList.hpp"

// implementation of stacks and queues with a linked list
// all operations in O(1) time except search

class stack {
    private:
    LinkedList* lst;
    int size_stack;
    
    public:
    stack() { // constructor
        lst = new LinkedList;
        size_stack = 0;
    }

    // get # of elements in the stack
    int size() {
        return size_stack;
    }

    // push, pop and search functions
    void push(int val) {
        lst->insertFront(val);
        size_stack += 1;
    }

    int pop() {
        return lst->removeFront();
        size_stack -= 1;
    }

    bool search(int val) {
        if (lst->search(val)) return true;
        else return false;
    }

    ~stack() { // destructor
        delete lst;
    }
}; // class stack

class queue {
    private:
    LinkedList* lst;
    int size_queue;
    
    public:
    queue() { // constructor
        lst = new LinkedList;
        size_queue = 0;
    }

    // enqueue and dequeue and search functions
    void enqueue(int val) {
        lst->insertFront(val);
        size_queue += 1;
    }

    int dequeue() {
        return lst->removeBack();
        size_queue -= 1;
    }

    bool search(int val) {
        if (lst->search(val)) return true;
        else return false;
    }

    ~queue() { // destructor
        delete lst;
    }

}; // class queue