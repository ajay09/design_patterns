//
//  flynoway.hpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 25/05/21.
//

#pragma once
#include "flybehavior.hpp"

class FlyNoWay : public FlyBehavior {
public:
    ~FlyNoWay() {};
    virtual void fly() override;
};
