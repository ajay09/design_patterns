//
//  guitar.hpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#ifndef guitar_hpp
#define guitar_hpp

#pragma once

#include "builder.hpp"
#include "type.hpp"
#include "wood.hpp"
#include <string>

using std::string;

class Guitar {
    public:
        // string _serialNumber, double _price, Builder _builder, string _model, Type _type, Wood _backWood, Wood _topWood
        Guitar(string, double, Builder, string, Type, Wood, Wood);
        std::string getSerialNumber();
        double getPrice();
        void setPrice(float);
        Builder getBuilder();
        std::string getModel();
        Type getType();
        Wood getBackWood();
        Wood getTopWood();
    private:
        std::string serialNumber, model;
        Builder builder;
        Type type;
        Wood backWood, topWood;
        double price;
};

typedef Guitar *pGuitar;

#endif /* guitar_hpp */
