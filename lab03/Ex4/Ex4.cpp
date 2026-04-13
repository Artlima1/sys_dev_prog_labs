
#include <functional>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

/*
    Suppose you run the following program.
    Which ones, when, and how many of the following copy control functions
    - constructor
    - copy constructor
    - copy assignment operator
    - move constructor
    - move assignment operator
    - destructor
    are called?
*/

class C {
private:
    int i;
public:
    C () {
        cout << "[C]";
    }
    ~C() {
        cout << "[D]";
    }
    C (const C &n) {
        cout << "[CC]";
    }
    C &operator=(const C &n) {
        cout << "[CAO]";
        return *this;
    }
    C (C&& n) noexcept {
        cout << "[MC]";
    }
    C &operator=(C&&n) noexcept {
        cout << "[MAO]";
        return *this;
    }
    void set(int n)  {
        i = n;
    };
    int get () {
        return i;
    }
};

void swap (C &e1, C &e2) {
    C tmp;  // Constructor
    tmp=e1; // Copy Assignment
    e1=e2;  // Copy Assignment
    e2=tmp; // Copy Assignment
    return; // Destructor (tmp)
}

int main() {
    cout << endl << "{01}"; C e1; // constructor
    cout << endl << "{02}"; C e2[5]; // constructor 5x (array)
    cout << endl << "{03}"; C e3 = *new (std::nothrow) C; // Constructor | Copy Constructor
    cout << endl << "{04}"; C *e4 = new C; // Constructor
    cout << endl << "{05}"; C *e5 = new C[10];   // Constructor 10x

    cout << endl << "{06}"; C v1 = e1; // Copy Constructor
    cout << endl << "{07}"; C v2 = (std::move(e1)); // Move Constructor
    cout << endl << "{08}"; C v3; // Constructor
    cout << endl << "{09}"; v3 = (std::move(e1)); // Move assignment operator

    cout << endl << "{10}"; swap (e1, v3);

    cout << endl << "{11}"; return 0; // Detructor 10x ? Why
}