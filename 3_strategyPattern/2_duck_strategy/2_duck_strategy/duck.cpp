//
//  duck.cpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 23/05/21.
//

#include "duck.hpp"
#include <iostream>

using std::cout;
using std::endl;

Duck::Duck() {}

void Duck::swim() {
    cout << "Swimming!" << endl;
}

void Duck::display() {
    cout << "I'm a Duck!" << endl;
}

void Duck::setName(string name) {
    this->name = name;
}

void Duck::performFlyBehavior() {
    flyBehavior->fly();
}

void Duck::performQuackBehavior() {
    quackBehavior->quack();
}

void Duck::setFlyBehavior(std::unique_ptr<FlyBehavior> flyB) {
    flyBehavior = std::move(flyB);
}

void Duck::setQuackBehavior(std::unique_ptr<QuackBehavior> quackB) {
    quackBehavior = std::move(quackB);
}
