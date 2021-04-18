//
//  type.hpp
//  guitar_enum
//
//  Created by Ajay Singh on 18/04/21.
//

#ifndef type_hpp
#define type_hpp

#include <string>

class Type {
public:
    enum Kind {
        ACOUSTIC,
        ELECTRIC
    };
    
    Type(Kind t) : _type(t) {}
    
    std::string to_string(Type t) {
        switch (_type) {
            case Type::ACOUSTIC: return "Acoustic";
            case Type::ELECTRIC: return "Electric";
            default:
                return "unspecified";
        }
    }
    
    Kind getKind() { return _type; }
private:
    Kind _type;
};

#endif /* type_hpp */
