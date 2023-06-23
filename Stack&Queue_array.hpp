
// implementating Stacks and Queues with arrays

class arrayStack {
    private:
    int array[20];
    int tail;

    public:
    // constructor
    arrayStack() {
        tail = 0;
    }

    // get # of elements
    int size() {
        return tail;
    }

    void push(int x) {
        if (tail >= 20) return;
        array[tail] = x;
        tail += 1;
    }

    int pop() {
        if (tail == 0) return -1;
        tail -= 1;
        int temp = array[tail];
        array[tail] = 0;
        return temp;
    }

    // empty destructor
    ~arrayStack() {}

}; // class arrayStack

class arrayQueue {
    private:
    int array[20];
    int head; // place to dequeue
    int tail; // place to enqueue
    // empty queue: head == tail == -1
    // full queue: head == tail

    public:
    arrayQueue() {
        head = -1;
        tail = -1;
    }

    void enqueue(int x) {
        if (head != -1 && head == tail) return; // full queue
        if (tail == -1) tail += 1; // add to empty queue
        array[tail] = x;
        tail += 1;
        if (tail >= 20) tail = 0;
    }

    int dequeue() {
        if (tail == -1) return -1; //empty queue
        if (head == -1) head += 1;
        int temp = array[head];
        array[head] = 0;
        head += 1;
        if (head >= 20) head = 0;
        return temp;
    }

    // empty destructor
    ~arrayQueue() {}

}; // class arrayQueue