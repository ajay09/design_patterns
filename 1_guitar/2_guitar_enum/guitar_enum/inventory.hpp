//
//  inventory.hpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#ifndef inventory_hpp
#define inventory_hpp

#pragma once

#include <list>
#include <initializer_list>
#include <string>
#include "guitar.hpp"



using std::string;
using std::initializer_list;

class Inventory{
    public:
        Inventory();
        // string _serialNumber, double _price, string _builder, string _model, string _type, string _backWood, string _topWood
        void addGuitar(string, double, Builder, string, Type, Wood, Wood);
    
        // We can't return reference here because if guitar is not found then we have to return null and reference can't be null in c++.
        pGuitar getGuitar(string); // serial number
        pGuitar search(Guitar&);
    private:
        std::list<pGuitar> guitars;
};


#endif /* inventory_hpp */
