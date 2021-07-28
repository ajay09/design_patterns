//
//  quack.hpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 25/05/21.
//

#pragma once
#include "quackbehavior.hpp"

class Quack : public QuackBehavior {
public:
    virtual void quack() override;
};
