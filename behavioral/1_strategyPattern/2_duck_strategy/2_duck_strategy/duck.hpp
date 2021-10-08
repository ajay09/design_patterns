//
//  duck.hpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 23/05/21.
//

#ifndef duck_hpp
#define duck_hpp

#include <string>
#include "flybehavior.hpp"
#include "quackbehavior.hpp"

using std::string;

class Duck {
public:
    Duck();
    void swim();
    virtual void display();
    void setName(string);
    void performFlyBehavior();
    void performQuackBehavior();
    void setFlyBehavior(std::unique_ptr<FlyBehavior>);
    void setQuackBehavior(std::unique_ptr<QuackBehavior>);
private:
    string name;
    std::unique_ptr<FlyBehavior> flyBehavior;
    std::unique_ptr<QuackBehavior> quackBehavior;
};

#endif /* duck_hpp */
