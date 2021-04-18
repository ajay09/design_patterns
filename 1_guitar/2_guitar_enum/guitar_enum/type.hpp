//
//  type.hpp
//  guitar_enum
//
//  Created by Ajay Singh on 18/04/21.
//

#ifndef type_hpp
#define type_hpp

#include <string>

enum class Type {
    ACOUSTIC,
    ELECTRIC
};

inline std::string to_string(Type t) {
    switch (t) {
        case Type::ACOUSTIC: return "Acoustic";
        case Type::ELECTRIC: return "Electric";
        default:
            return "unspecified";
    }
}

#endif /* type_hpp */
