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

std::list<pGuitar> Inventory::search(GuitarSpec& searchGuitarSpec) {
    std::list<pGuitar> result;
    for (auto guitar : guitars) {
        GuitarSpec spec = guitar->getSpec();
        // We are not comparing Serial Number and Price because they are unique for each guitar.
        if (spec.matchSpec(searchGuitarSpec))
            result.push_back(guitar);
    }
    return result;
}
