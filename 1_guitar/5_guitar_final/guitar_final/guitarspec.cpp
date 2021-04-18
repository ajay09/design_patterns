//
//  guitarspec.cpp
//  guitar_encapsulated
//
//  Created by Ajay Singh on 18/04/21.
//

#include "guitarspec.hpp"


// Builder _builder, string _model, Type _type, Wood _backWood, Wood _topWood
GuitarSpec::GuitarSpec(Builder _builder, std::string _model, Type _type, int _numStrings, Wood _backWood, Wood _topWood) :
            builder(_builder),
            model(_model),
            type(_type),
            numStrings(_numStrings),
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

int GuitarSpec::getNumStrings() {
    return numStrings;
}

bool GuitarSpec::matchSpec(GuitarSpec& searchGuitar) {
    // GuitarSpec spec = guitar->getSpec();
    // We are not comparing Serial Number and Price because they are unique for each guitar.
    if (builder.getKind() != searchGuitar.getBuilder().getKind())
        return false;
    if (model != searchGuitar.getModel())
        return false;
    if (type.getKind() != searchGuitar.getType().getKind())
        return false;
    if (backWood.getKind() != searchGuitar.getBackWood().getKind())
        return false;
    if (topWood.getKind() != searchGuitar.getTopWood().getKind())
        return false;
    return true;
}
