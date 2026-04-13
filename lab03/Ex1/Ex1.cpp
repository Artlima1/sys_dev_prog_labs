//
// Created by arthur on 4/13/26.
//

#include <iostream>
#include <ostream>

#include "MyFIFO.h"
#include "MyLIFO.h"
#include "MyFIFO.hpp"
#include "MyLIFO.hpp"

int main() {
    int numbers[] = {1, 2, 4, 5, 6, 7, 8, 9};

    MyLIFO<int> stack{};
    MyFIFO<int> queue{};

    for (auto n: numbers) {
        stack.enqueue(n);
        queue.push(n);
    }

    std::cout << "Queue Size: " << queue.getSize() << std::endl;
    queue.visit();
    std::cout << "Stack Size: " << stack.getSize() << std::endl;
    stack.visit();

    stack.dequeue();
    queue.pop();

    std::cout << "Queue Size: " << queue.getSize() << std::endl;
    queue.visit();
    std::cout << "Stack Size: " << stack.getSize() << std::endl;
    stack.visit();

    return EXIT_SUCCESS;
}
