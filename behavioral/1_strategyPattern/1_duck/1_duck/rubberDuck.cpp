//
//  rubberDuck.cpp
//  1_duck
//
//  Created by Ajay Singh on 23/05/21.
//

#include "rubberDuck.hpp"
#include <iostream>

using std::cout;
using std::endl;

void RubberDuck::display() {
    cout << "I'm no ordinary duck. I'm a Rubber duck!!" << endl;
}

void RubberDuck::fly() {
    cout << "I'm not a real duck. Sorry, but I can't fly!!" << endl;
}

void RubberDuck::quack() {
    cout << "Squeeek" << endl;
}
