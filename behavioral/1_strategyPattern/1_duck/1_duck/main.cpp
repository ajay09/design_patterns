//
//  main.cpp
//  1_duck
//
//  Created by Ajay Singh on 18/05/21.
//

#include <iostream>
#include "duck.hpp"
#include "mallardDuck.hpp"
#include "redheadDuck.hpp"
#include "rubberDuck.hpp"

int main(int argc, const char * argv[]) {
    Duck ordinaryDuck;
    MallardDuck mDuck{};  // We explicitly declared the mallard duck default constructor.
    RedheadDuck rDuck;    // We used the auto generated default constructor for redhead duck.
    
    ordinaryDuck.display();
    mDuck.display();
    rDuck.display();
    
    std::cout << "RedheadDuck : ";
    rDuck.fly();
    
    std::cout << "RubberDuck : ";
    RubberDuck rubDuck;
    rubDuck.fly();
}
