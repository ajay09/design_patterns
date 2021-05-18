//
//  subwayPrinter.hpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#ifndef subwayPrinter_hpp
#define subwayPrinter_hpp

#include <iostream>
#include <list>
#include "station.hpp"
#include "connection.hpp"


// added this to support printing for the  Network  which is stored as an unordered_map<Station, list<Station>>
template<typename T, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<T, S>& p) {
    out << p.first << "\n\t";
    for (auto item : p.second)
        out << item << "  ";
    out << "\n";
    return out;
}

class SubwayPrinter {
public:
    SubwayPrinter(std::ostream& out = std::cout);

    // a template member function should be declared inside the header file because the compiler needs it to generate code for the supplied type.
    template<typename T>
    void printIterableObject(const T& object) {
        int i = 0;
        m_out << "\n";
        for (auto item : object) {
            m_out << "\t" << ++i << "  " << item << std::endl;
        }
    }
    
//    void printRoute(const std::list<Connection>&);
    
private:
    std::ostream& m_out; //
    
};

#endif /* subwayPrinter_hpp */
