//
//  duck.hpp
//  1_duck
//
//  Created by Ajay Singh on 18/05/21.
//

#ifndef duck_hpp
#define duck_hpp

#include <string>

using std::string;

class Duck {
public:
    Duck();
    void quack();
    void swim();
    void display();
    void fly();          // Putting the fly method in the superclass gave flying ability to all the ducks.
                         // even to those that shouldn't fly.
    void setName(string);
private:
    string name;
};

#endif /* duck_hpp */
