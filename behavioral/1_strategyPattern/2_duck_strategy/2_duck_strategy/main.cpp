//
//  main.cpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 23/05/21.
//

#include <iostream>
#include "mallardduck.hpp"
#include "flywithrocket.hpp"

int main(int argc, const char * argv[]) {
    Duck* mallard = new MallardDuck();
    mallard->display();
    mallard->performFlyBehavior();
    mallard->performQuackBehavior();
    
    mallard->setFlyBehavior(std::make_unique<FlyWithRocket>());
    mallard->performFlyBehavior();
    
}
