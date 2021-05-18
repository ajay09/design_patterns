//
//  subwayLoader.hpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#ifndef subwayLoader_hpp
#define subwayLoader_hpp

#include "subway.hpp"
#include <fstream>

using std::string;
using std::ifstream;

class SubwayLoader {
public:
    SubwayLoader() {}
    Subway loadFromFile(ifstream&);
private:
    void getStations(ifstream&, Subway&);
    void getConnections(ifstream&, Subway&, string);
};

#endif /* subwayLoader_hpp */
