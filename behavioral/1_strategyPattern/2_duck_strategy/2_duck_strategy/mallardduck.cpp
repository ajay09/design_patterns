//
//  mallardduck.cpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 25/05/21.
//

#include "mallardduck.hpp"
#include <iostream>
#include "flywithwings.hpp"
#include "quack.hpp"

using std::cout;
using std::endl;

MallardDuck::MallardDuck() {
    setFlyBehavior(std::make_unique<FlyWithWings>());
    setQuackBehavior(std::make_unique<Quack>());
}

void MallardDuck::display() {
    cout << "I'm no ordinary duck. I'm a Mallard duck!!" << endl;
}
