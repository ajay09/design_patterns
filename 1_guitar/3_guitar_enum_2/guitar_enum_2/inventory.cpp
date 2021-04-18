//
//  inventory.cpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#include "inventory.hpp"

Inventory::Inventory() {}

void Inventory::addGuitar(string _serialNumber, double _price, Builder _builder, string _model, Type _type, Wood _backWood, Wood _topWood) {
    Guitar* newGuitar = new Guitar(_serialNumber, _price, _builder, _model, _type, _backWood, _topWood);
    guitars.push_back(newGuitar);
}

pGuitar Inventory::getGuitar(string serial) {
    for (auto guitar : guitars) {
        if (guitar->getSerialNumber() == serial)
            return guitar;
    }
    return nullptr;
}

std::list<pGuitar> Inventory::search(Guitar& searchGuitar) {
    std::list<pGuitar> result;
    for (auto guitar : guitars) {
        // We are not comparing Serial Number and Price because they are unique for each guitar.
        if (guitar->getBuilder().getKind() != searchGuitar.getBuilder().getKind())
            continue;
        if (guitar->getModel() != searchGuitar.getModel())
            continue;
        if (guitar->getType().getKind() != searchGuitar.getType().getKind())
            continue;
        if(guitar->getBackWood().getKind() != searchGuitar.getBackWood().getKind())
            continue;
        if(guitar->getTopWood().getKind() != searchGuitar.getTopWood().getKind())
            continue;
        result.push_back(guitar);
    }
    return result;
}
