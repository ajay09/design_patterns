//
//  guitar.cpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#include "guitar.hpp"


//Guitar::Guitar

Guitar::Guitar(string _serialNumber, double _price, Builder _builder, string _model, Type _type, Wood _backWood, Wood _topWood) : serialNumber(_serialNumber), price(_price), builder(_builder), model(_model), type(_type), backWood(_backWood), topWood(_topWood) {}


std::string Guitar::getSerialNumber() {
    return serialNumber;
}
double Guitar::getPrice() {
    return price;
}
void Guitar::setPrice(float _price) {
    price = _price;
}
Builder::Kind Guitar::getBuilder() {
    return builder.getKind();
}
std::string Guitar::getModel() {
    return model;
}
Type::Kind Guitar::getType() {
    return type.getKind();
}
Wood::Kind Guitar::getBackWood() {
    return backWood.getKind();
}
Wood::Kind Guitar::getTopWood() {
    return topWood.getKind();
}
