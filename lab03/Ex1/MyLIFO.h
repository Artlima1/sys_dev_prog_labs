//
// Created by arthur on 4/13/26.
//

#ifndef LAB03_MYLIFO_H
#define LAB03_MYLIFO_H
#include <list>


template <typename T> class MyLIFO {
private:
    std::list<T> _data;

public:
    MyLIFO() = default;
    void enqueue(T e);
    T dequeue();
    void visit();
    long int getSize();
    bool empty();
};


#endif //LAB03_MYLIFO_H