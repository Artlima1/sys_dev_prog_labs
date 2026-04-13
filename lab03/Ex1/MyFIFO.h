//
// Created by arthur on 4/13/26.
//

#ifndef LAB03_MYFIFO_H
#define LAB03_MYFIFO_H
#include <vector>


template <typename T> class MyFIFO {
private:
    std::vector<T> _data;

public:
    MyFIFO() = default;
    void push(T e);
    T pop();
    void visit();
    long int getSize();
    bool empty();
};


#endif //LAB03_MYFIFO_H