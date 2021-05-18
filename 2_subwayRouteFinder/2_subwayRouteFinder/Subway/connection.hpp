//
//  connection.hpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#ifndef connection_hpp
#define connection_hpp

#include "station.hpp"
#include <ostream>

using std::ostream;

using std::string;

class Connection {
public:
    Connection(string, string, string); // line-name, station 1, station 2
    string getStation1();
    string getStation2();
    string getLineName();
    friend ostream& operator<<(ostream& out, const Connection&);
private:
    Station m_station1, m_station2;
    string m_lineName;
};

#endif /* connection_hpp */
