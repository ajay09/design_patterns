//
//  duck.cpp
//  1_duck
//
//  Created by Ajay Singh on 18/05/21.
//

#include "duck.hpp"
#include <iostream>

using std::cout;
using std::endl;

Duck::Duck() {}

void Duck::setName(string n) {
    name = n;
}

void Duck::display() {
    cout << "I'm a Duck!" << endl;
}

void Duck::quack() {
    cout << "quack quack!!" << endl;
}

void Duck::swim() {
    cout << "let's swim!!" << endl;
}

void Duck::fly() {
    cout << "Enough of swimming. I'm going flying now!!" << endl;
}
