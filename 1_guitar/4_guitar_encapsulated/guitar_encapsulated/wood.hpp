//
//  wood.h
//  guitar_enum
//
//  Created by Ajay Singh on 18/04/21.
//

#ifndef wood_h
#define wood_h

#include <string>

class Wood {
public:
    enum Kind {
        INDIAN_ROSEWOOD, BRAZILIAN_ROSEWOOD, MAHOGANY, MAPLE,
          COCOBOLO, CEDAR, ADIRONDACK, ALDER, SITKA
    };
    
    Wood(Kind w) : _wood(w) {}

    std::string to_string() {
        switch (_wood) {
            case Wood::INDIAN_ROSEWOOD:    return "Indian Rosewood";
            case Wood::BRAZILIAN_ROSEWOOD: return "Brazilian Rosewood";
            case Wood::MAHOGANY:           return "Mahogany";
            case Wood::MAPLE:              return "Maple";
            case Wood::COCOBOLO:           return "Cocobolo";
            case Wood::CEDAR:              return "Cedar";
            case Wood::ADIRONDACK:         return "Adirondack";
            case Wood::ALDER:              return "Alder";
            case Wood::SITKA:              return "Sitka";
            default:  return "unspecified";
        }
    }
    
    Kind getKind() { return _wood; }
private:
    Kind _wood;
};

#endif /* wood_h */
