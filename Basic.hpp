# include "LinkedList.hpp"

// implementation stacks and queues with a linked list
// all operations in O(1) time except search

class stack {
    private:
    LinkedList* lst;
    
    public:
    stack() { // constructor
        lst = new LinkedList;
    }

    // push, pop and search functions
    void push(int val) {
        lst->insertFront(val);
    }

    int pop() {
        return lst->removeFront();
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
    
    public:
    queue() { // constructor
        lst = new LinkedList;
    }

    // enqueue and dequeue and search functions
    void enqueue(int val) {
        lst->insertFront(val);
    }

    int dequeue() {
        return lst->removeBack();
    }

    bool search(int val) {
        if (lst->search(val)) return true;
        else return false;
    }

    ~queue() { // destructor
        delete lst;
    }

}; // class queue