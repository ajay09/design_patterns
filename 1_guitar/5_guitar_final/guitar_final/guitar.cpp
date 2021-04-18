//
//  guitar.cpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#include "guitar.hpp"


//Guitar::Guitar

Guitar::Guitar(string _serialNumber, double _price, pGuitarSpec _spec) :
        serialNumber(_serialNumber),
        price(_price), spec(_spec) {}


std::string Guitar::getSerialNumber() {
    return serialNumber;
}

double Guitar::getPrice() {
    return price;
}

void Guitar::setPrice(float _price) {
    price = _price;
}

GuitarSpec& Guitar::getSpec() {
    return *spec;
}
