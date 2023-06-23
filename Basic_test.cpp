# include "Basic.hpp"
# include <iostream>

int main() {
    stack s1;
    s1.push(3);
    s1.push(6);
    s1.push(9);
    std::cout << s1.pop() << std::endl;
    std::cout << s1.pop() << std::endl;
}