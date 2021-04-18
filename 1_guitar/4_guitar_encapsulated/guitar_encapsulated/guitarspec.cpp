//
//  guitarspec.cpp
//  guitar_encapsulated
//
//  Created by Ajay Singh on 18/04/21.
//

#include "guitarspec.hpp"


// Builder _builder, string _model, Type _type, Wood _backWood, Wood _topWood
GuitarSpec::GuitarSpec(Builder _builder, std::string _model, Type _type, Wood _backWood, Wood _topWood) :
            builder(_builder),
            model(_model),
            type(_type),
            backWood(_backWood),
            topWood(_topWood)
            {}


Builder GuitarSpec::getBuilder() {
    return builder;
}
std::string GuitarSpec::getModel() {
    return model;
}
Type GuitarSpec::getType() {
    return type;
}
Wood GuitarSpec::getBackWood() {
    return backWood;
}
Wood GuitarSpec::getTopWood() {
    return topWood;
}


