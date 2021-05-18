//
//  station.hpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#ifndef station_hpp
#define station_hpp

#include <string>
#include <ostream>

using std::string;

class Station {
public:
    Station(string);
    
    string getName() const;
    
    bool equals(Station);
    
    friend std::ostream& operator<<(std::ostream& out, const Station&);
    
    // We defined this operator because
    //  list container doesn't have an inbuild find function.
    //  and for the find function defined in <algorithm> we need to define == operator
    //
    //  unordered_map  also needs this function to be defined for using custom type keys.
    bool operator==(const Station&) const;
    
    bool operator<(const Station&) const;
private:
    string m_name;
};

// this is defined so that  "Station"  can be used as a key in unordered_map
namespace std {
    template<>
    struct hash<Station> {
        std::size_t operator()(const Station& st) const {
            return hash<string>()(st.getName());
        }
    };
}

#endif /* station_hpp */
