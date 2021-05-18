//
//  station.cpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#include "station.hpp"

Station::Station(string name) : m_name(name) {}

string Station::getName() const {
    return m_name;
}

bool Station::equals(Station s) {
    return m_name == s.m_name;
}

std::ostream& operator<<(std::ostream& out, const Station& s) {
    out << s.m_name;
    return out;
}

// We defined this operator because
//  list container doesn't have an inbuild find function.
//  and for the find function defined in <algorithm> we need to define == operator
//
//  unordered_map  also needs this function to be defined for using custom type keys.
bool Station::operator==(const Station& st) const {
    return m_name == st.m_name;
}

// defined so that   set<Station>  could be used.
bool Station::operator<(const Station& st) const {
    return m_name < st.m_name;
}
