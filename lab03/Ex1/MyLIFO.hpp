//
// Created by arthur on 4/13/26.
//

#ifndef LAB03_MYLIFO_HPP
#define LAB03_MYLIFO_HPP

#include <iostream>
#include <ostream>


template<typename T>
void MyLIFO<T>::enqueue(T e) {
    _data.push_back(e);
}

template<typename T>
long int MyLIFO<T>::getSize() {
    return _data.size();
}

template<typename T>
T MyLIFO<T>::dequeue() {
    T v = _data.front();
    _data.pop_front();
    return v;
}

template<typename T>
bool MyLIFO<T>::empty() {
    return _data.empty();
}

template<typename T>
void MyLIFO<T>::visit() {
    for (auto it : _data) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

#endif // LAB03_MYLIFO_HPP
