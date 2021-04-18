//
//  guitar.hpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#ifndef guitar_hpp
#define guitar_hpp

#pragma once

#include <string>

using std::string;

class Guitar {
    public:
        Guitar(string, double, string, string, string, string, string);
        std::string getSerialNumber();
        double getPrice();
        void setPrice(float);
        std::string getBuilder();
        std::string getModel();
        std::string getType();
        std::string getBackWood();
        std::string getTopWood();
    private:
        std::string serialNumber, builder, model, type, backWood, topWood;
        double price;
};

typedef Guitar *pGuitar;

#endif /* guitar_hpp */
