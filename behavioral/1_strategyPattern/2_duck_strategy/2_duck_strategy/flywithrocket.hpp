//
//  flywithrocket.hpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 25/05/21.
//

#ifndef flywithrocket_hpp
#define flywithrocket_hpp

#include "flybehavior.hpp"

class FlyWithRocket : public FlyBehavior {
public:
    virtual void fly() override;
};

#endif /* flywithrocket_hpp */
