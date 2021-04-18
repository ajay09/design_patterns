//
//  inventory.cpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#include "inventory.hpp"

Inventory::Inventory() {}

void Inventory::addGuitar(string _serialNumber, double _price, pGuitarSpec _spec) {
    Guitar* newGuitar = new Guitar(_serialNumber, _price, _spec);
    guitars.push_back(newGuitar);
}

pGuitar Inventory::getGuitar(string serial) {
    for (auto guitar : guitars) {
        if (guitar->getSerialNumber() == serial)
            return guitar;
    }
    return nullptr;
}

std::list<pGuitar> Inventory::search(GuitarSpec& searchGuitar) {
    std::list<pGuitar> result;
    for (auto guitar : guitars) {
        GuitarSpec spec = guitar->getSpec();
        // We are not comparing Serial Number and Price because they are unique for each guitar.
        if (spec.getBuilder().getKind() != searchGuitar.getBuilder().getKind())
            continue;
        if (spec.getModel() != searchGuitar.getModel())
            continue;
        if (spec.getType().getKind() != searchGuitar.getType().getKind())
            continue;
        if (spec.getBackWood().getKind() != searchGuitar.getBackWood().getKind())
            continue;
        if (spec.getTopWood().getKind() != searchGuitar.getTopWood().getKind())
            continue;
        result.push_back(guitar);
    }
    return result;
}
