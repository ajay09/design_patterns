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

enum class Builder {
    FENDER, MARTIN, GIBSON, COLLINGS, OLSON, RYAN, PRS, ANY
};

inline std::string to_string(Builder b) {
    switch (b) {
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

#endif /* builder_h */
