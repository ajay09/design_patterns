//
//  guitarSimulator.cpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#include <iostream>
#include "guitar.hpp"
#include "inventory.hpp"

using namespace std;

//std::string to_string(Wood w) {
//    switch (w) {
//        case Wood::INDIAN_ROSEWOOD:    return "Indian Rosewood";
//        case Wood::BRAZILIAN_ROSEWOOD: return "Brazilian Rosewood";
//        case Wood::MAHOGANY:           return "Mahogany";
//        case Wood::MAPLE:              return "Maple";
//        case Wood::COCOBOLO:           return "Cocobolo";
//        case Wood::CEDAR:              return "Cedar";
//        case Wood::ADIRONDACK:         return "Adirondack";
//        case Wood::ALDER:              return "Alder";
//        case Wood::SITKA:              return "Sitka";
//        default:  return "unspecified";
//    }
//}

//std::string to_string(Builder b) {
//    switch (b) {
//        case Builder::FENDER:   return "Fender";
//        case Builder::MARTIN:   return "Martin";
//        case Builder::GIBSON:   return "Gibson";
//        case Builder::COLLINGS: return "Collings";
//        case Builder::OLSON:    return "Olson";
//        case Builder::RYAN:     return "Ryan";
//        case Builder::PRS :     return "PRS";
//        default:       return "Unspecified";
//    }
//}

//std::string to_string(Type t) {
//    switch (t) {
//        case Type::ACOUSTIC: return "Acoustic";
//        case Type::ELECTRIC: return "Electric";
//        default:
//            return "unspecified";
//    }
//}

void initializeInventory(Inventory& inventory) {
    inventory.addGuitar("11277", 3999.95, Builder::COLLINGS,
                            "CJ", Type::ACOUSTIC,
                            Wood::INDIAN_ROSEWOOD, Wood::SITKA);
        inventory.addGuitar("V95693", 1499.95, Builder::FENDER,
                            "Stratocastor", Type::ELECTRIC,
                            Wood::ALDER, Wood::ALDER);
        inventory.addGuitar("V9512", 1549.95, Builder::FENDER,
                            "Stratocastor", Type::ELECTRIC,
                            Wood::ALDER, Wood::ALDER);
        inventory.addGuitar("122784", 5495.95, Builder::MARTIN,
                            "D-18", Type::ACOUSTIC,
                            Wood::MAHOGANY, Wood::ADIRONDACK);
        inventory.addGuitar("76531", 6295.95, Builder::MARTIN,
                            "OM-28", Type::ACOUSTIC,
                            Wood::BRAZILIAN_ROSEWOOD, Wood::ADIRONDACK);
        inventory.addGuitar("70108276", 2295.95, Builder::GIBSON,
                            "Les Paul", Type::ELECTRIC,
                            Wood::MAHOGANY, Wood::MAHOGANY);
        inventory.addGuitar("82765501", 1890.95, Builder::GIBSON,
                            "SG '61 Reissue", Type::ELECTRIC,
                            Wood::MAHOGANY, Wood::MAHOGANY);
        inventory.addGuitar("77023", 6275.95, Builder::MARTIN,
                            "D-28", Type::ACOUSTIC,
                            Wood::BRAZILIAN_ROSEWOOD, Wood::ADIRONDACK);
        inventory.addGuitar("1092", 12995.95, Builder::OLSON,
                            "SJ", Type::ACOUSTIC,
                            Wood::INDIAN_ROSEWOOD, Wood::CEDAR);
        inventory.addGuitar("566-62", 8999.95, Builder::RYAN,
                            "Cathedral", Type::ACOUSTIC,
                            Wood::COCOBOLO, Wood::CEDAR);
        inventory.addGuitar("6 29584", 2100.95, Builder::PRS,
                            "Dave Navarro Signature", Type::ELECTRIC,
                            Wood::MAHOGANY, Wood::MAPLE);
}

int main() {
    cout << "Welcome to Guitar World!!!\n";
    Inventory inventory;
    initializeInventory(inventory);
    
    // string _serialNumber, double _price, string _builder, string _model, string _type, string _backWood, string _topWood
    pGuitar whatErinLikes = new Guitar("", 0, Builder::FENDER, "Stratocastor", Type::ELECTRIC, Wood::ALDER, Wood::ALDER);
    
    pGuitar guitar = inventory.search(*whatErinLikes);
    if (guitar) {
        cout << "You might like this " +
        to_string(guitar->getBuilder()) + " " + guitar->getModel() +  " " +
        to_string(guitar->getType()) + " guitar:\n   " +
        to_string(guitar->getBackWood()) + " back and sides,\n   " +
        to_string(guitar->getTopWood()) + " top.\nYou can have it for only $" +
        to_string(guitar->getPrice()) + "!";
    } else {
        cout << "Sorry that won't be available right now!\n";
    }
    
    
    
    return 0;
}
