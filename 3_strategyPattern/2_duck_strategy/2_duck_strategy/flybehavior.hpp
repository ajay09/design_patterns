//
//  flybehavior.hpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 23/05/21.
//

#ifndef flybehavior_hpp
#define flybehavior_hpp

class FlyBehavior {
public:
    virtual ~FlyBehavior() {}
    virtual void fly() = 0;
};

#endif /* flybehavior_hpp */
