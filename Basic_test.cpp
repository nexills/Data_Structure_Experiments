# include "Basic.hpp"
# include "Stack&Queue_array.hpp"
# include <iostream>

int main() {
    arrayQueue s1;
    for (int i = 0; i < 20; i++) {
        s1.enqueue(i);
    }
    std::cout << s1.dequeue() << std::endl;
    std::cout << s1.dequeue() << std::endl;
    s1.enqueue(100);
    std::cout << s1.dequeue() << std::endl;
    
}