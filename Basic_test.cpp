# include "Stack&Queue.hpp"
# include "Stack&Queue_array.hpp"
# include "BST_AVL.hpp"
# include "Hash_table.hpp"
# include <iostream>
# include <cassert>

int main() {
    // tests for the Linked Lists
    LinkedList t1;
    t1.insertFront(3);
    t1.insertFront(6);
    t1.insertEnd(9);
    assert(t1.search(3)->value == 3);
    assert(!t1.search(4)->value);
    t1.removeBack();
    assert(!t1.search(9)->value);
    assert(t1.removeFront() == 3);
    t1.removeFront();
    t1.removeBack();
    // tests for the Stacks & Queues
    stack S1;
    S1.push(4);
    S1.push(8);
    assert(!S1.search(12));
    assert(S1.pop() == 8);
    assert(S1.size() == 1);

    queue Q1;
    Q1.enqueue(2);
    Q1.enqueue(4);
    Q1.enqueue(6);
    assert(Q1.dequeue() == 2);
    assert(Q1.search(4));
    
}