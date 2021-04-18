//
//  guitarSimulator.cpp
//  guitar
//
//  Created by Ajay Singh on 17/04/21.
//

#include <iostream>
#include "guitar.hpp"
#include "inventory.hpp"
#include "guitarspec.hpp"

using namespace std;

void initializeInventory(Inventory& inventory);

int main() {
    cout << "Welcome to Guitar World!!!\n";
    Inventory inventory;
    initializeInventory(inventory);
    
    // string _serialNumber, double _price, string _builder, string _model, string _type, string _backWood, string _topWood
    pGuitarSpec whatErinLikes = new GuitarSpec(Builder::Kind::FENDER, "Stratocastor", Type::Kind::ELECTRIC, Wood::Kind::ALDER, Wood::Kind::ALDER);
    
    std::list<pGuitar> guitarsMatched = inventory.search(*whatErinLikes);
    if (!guitarsMatched.empty()) {
        cout << "You might like these guitars ... \n";
        for (auto guitar : guitarsMatched) {
            GuitarSpec spec = guitar->getSpec();
            cout << "> We have a " +
            spec.getBuilder().to_string() + " " + spec.getModel() +  " " +
            spec.getType().to_string() + " guitar:\n   " +
            spec.getBackWood().to_string() + " back and sides,\n   " +
            spec.getTopWood().to_string() + " top.\nYou can have it for only $" +
            to_string(guitar->getPrice()) + "!\n ---\n";
        }
    } else {
        cout << "Sorry that won't be available right now!\n";
    }
    
    
    
    return 0;
}

void initializeInventory(Inventory& inventory) {
    inventory.addGuitar("11277", 3999.95, new GuitarSpec(Builder::Kind::COLLINGS,
                            "CJ", Type::Kind::ACOUSTIC,
                            Wood::Kind::INDIAN_ROSEWOOD, Wood::Kind::SITKA));
    inventory.addGuitar("V95693", 1499.95, new GuitarSpec(Builder::Kind::FENDER,
                            "Stratocastor", Type::Kind::ELECTRIC,
                            Wood::Kind::ALDER, Wood::Kind::ALDER));
    inventory.addGuitar("V9512", 1549.95, new GuitarSpec(Builder::Kind::FENDER,
                            "Stratocastor", Type::Kind::ELECTRIC,
                            Wood::Kind::ALDER, Wood::Kind::ALDER));
    inventory.addGuitar("122784", 5495.95, new GuitarSpec(Builder::Kind::MARTIN,
                            "D-18", Type::Kind::ACOUSTIC,
                            Wood::Kind::MAHOGANY, Wood::Kind::ADIRONDACK));
    inventory.addGuitar("76531", 6295.95, new GuitarSpec(Builder::Kind::MARTIN,
                            "OM-28", Type::Kind::ACOUSTIC,
                            Wood::Kind::BRAZILIAN_ROSEWOOD, Wood::Kind::ADIRONDACK));
    inventory.addGuitar("70108276", 2295.95, new GuitarSpec(Builder::Kind::GIBSON,
                            "Les Paul", Type::Kind::ELECTRIC,
                            Wood::Kind::MAHOGANY, Wood::Kind::MAHOGANY));
    inventory.addGuitar("82765501", 1890.95, new GuitarSpec(Builder::Kind::GIBSON,
                            "SG '61 Reissue", Type::Kind::ELECTRIC,
                            Wood::Kind::MAHOGANY, Wood::Kind::MAHOGANY));
    inventory.addGuitar("77023", 6275.95, new GuitarSpec(Builder::Kind::MARTIN,
                            "D-28", Type::Kind::ACOUSTIC,
                            Wood::Kind::BRAZILIAN_ROSEWOOD, Wood::Kind::ADIRONDACK));
    inventory.addGuitar("1092", 12995.95, new GuitarSpec(Builder::Kind::OLSON,
                            "SJ", Type::Kind::ACOUSTIC,
                            Wood::Kind::INDIAN_ROSEWOOD, Wood::Kind::CEDAR));
    inventory.addGuitar("566-62", 8999.95, new GuitarSpec(Builder::Kind::RYAN,
                            "Cathedral", Type::Kind::ACOUSTIC,
                            Wood::Kind::COCOBOLO, Wood::Kind::CEDAR));
    inventory.addGuitar("6 29584", 2100.95, new GuitarSpec(Builder::Kind::PRS,
                            "Dave Navarro Signature", Type::Kind::ELECTRIC,
                            Wood::Kind::MAHOGANY, Wood::Kind::MAPLE));
}
