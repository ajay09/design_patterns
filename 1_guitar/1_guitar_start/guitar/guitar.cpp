//
//  guitar.cpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#include "guitar.hpp"

//Guitar::Guitar

Guitar::Guitar(string _serialNumber, double _price, string _builder, string _model, string _type, string _backWood, string _topWood) : serialNumber(_serialNumber), price(_price), builder(_builder), model(_model), type(_type), backWood(_backWood), topWood(_topWood) {}


std::string Guitar::getSerialNumber() {
    return serialNumber;
}
double Guitar::getPrice() {
    return price;
}
void Guitar::setPrice(float _price) {
    price = _price;
}
std::string Guitar::getBuilder() {
    return builder;
}
std::string Guitar::getModel() {
    return model;
}
std::string Guitar::getType() {
    return type;
}
std::string Guitar::getBackWood() {
    return backWood;
}
std::string Guitar::getTopWood() {
    return topWood;
}
