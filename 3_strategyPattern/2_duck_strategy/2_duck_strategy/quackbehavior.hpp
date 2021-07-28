//
//  quackbehavior.hpp
//  2_duck_strategy
//
//  Created by Ajay Singh on 23/05/21.
//

#ifndef quackbehavior_hpp
#define quackbehavior_hpp

class QuackBehavior {
public:
    virtual ~QuackBehavior() {}
    virtual void quack() = 0;
};

#endif /* quackbehavior_hpp */
