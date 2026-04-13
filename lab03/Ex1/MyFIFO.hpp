//
// Created by arthur on 4/13/26.
//

#ifndef LAB03_MYFIFO_HPP
#define LAB03_MYFIFO_HPP

#include <iostream>
#include <ostream>


template<typename T>
void MyFIFO<T>::push(T e) {
    _data.push_back(e);
}

template<typename T>
long int MyFIFO<T>::getSize() {
    return _data.size();
}

template<typename T>
T MyFIFO<T>::pop() {
    T v = _data[_data.size()-1];
    _data.pop_back();
    return v;
}

template<typename T>
bool MyFIFO<T>::empty() {
    return _data.empty();
}

template<typename T>
void MyFIFO<T>::visit() {
    for (auto it : _data) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

#endif // LAB03_MYFIFO_HPP