//
//  builder.h
//  guitar_enum
//
//  Created by Ajay Singh on 18/04/21.
//

#ifndef builder_h
#define builder_h

#pragma once

#include <string>

class Builder {
public:
    enum Kind {
        FENDER, MARTIN, GIBSON, COLLINGS, OLSON, RYAN, PRS, ANY
    };
    
    Builder(Kind build) : _build(build) {}
    
    std::string to_string() {
        switch (_build) {
            case Builder::FENDER:   return "Fender";
            case Builder::MARTIN:   return "Martin";
            case Builder::GIBSON:   return "Gibson";
            case Builder::COLLINGS: return "Collings";
            case Builder::OLSON:    return "Olson";
            case Builder::RYAN:     return "Ryan";
            case Builder::PRS :     return "PRS";
            default:       return "Unspecified";
        }
    }
    
    Kind getKind() { return _build; }
private:
    Kind _build;
};

#endif /* builder_h */
