# include <string>

// an implementation of doubly-linked linked list

struct node {
    int value;
    node* next;
    node* prev;
};

class LinkedList {
    private:
    node* head;
    node* tail;

    public:
    // default constructor creates a empty list
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // two inserts: front(head) and back(tail)
    // both runs in O(1)
    void insertFront(int val) {
        node* newnode = new node;
        newnode->value = val;
        if (!head) {
            // inserting to an empty list
            newnode->next = nullptr;
            newnode->prev = nullptr;

            head = newnode;
            tail = newnode;
            return;
        } else {
            newnode->next = head;
            newnode->prev = nullptr;
            newnode->next->prev = newnode;

            head = newnode;
            return;
        }
    }

    void insertEnd(int val) {
        if (!head) {
            // does the samething anyway
            insertFront(val);
            return;
        } else {
            node* newnode = new node;
            newnode->value = val;
            tail->next = newnode;
            newnode->prev = tail;
            newnode->next = nullptr;
            tail = newnode;
            return;
        }
    }

    // two removes: both runs in O(1)
    // returns the value contained by node
    int removeFront() {
        // return -1 when list is empty
        if (!head) return -1;
        // sets the pointers and return
        int val = head->value;
        node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        return val;
    }

    int removeBack() {
        // return -1 when list is empty
        if (!head) return -1;
        // sets the pointers and return
        int val = tail->value;
        node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        return val; 
    }


}; // class LinkedList
