//
//  guitarspec.hpp
//  guitar_encapsulated
//
//  Created by Ajay Singh on 18/04/21.
//

#ifndef guitarspec_hpp
#define guitarspec_hpp

#include "builder.hpp"
#include "wood.hpp"
#include "type.hpp"
#include <string>

class GuitarSpec {
public:
    // Builder _builder, string _model, Type _type, Wood _backWood, Wood _topWood
    GuitarSpec(Builder, std::string, Type, int, Wood, Wood);
    
    Builder getBuilder();
    std::string getModel();
    Type getType();
    Wood getBackWood();
    Wood getTopWood();
    int getNumStrings();
    bool matchSpec(GuitarSpec&);
    
private:
    std::string model;
    Builder builder;
    Type type;
    int numStrings;
    Wood backWood, topWood;
};

typedef GuitarSpec *pGuitarSpec;

#endif /* guitarspec_hpp */
