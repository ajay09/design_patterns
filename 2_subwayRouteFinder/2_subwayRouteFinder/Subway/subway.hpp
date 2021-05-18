//
//  subway.hpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#ifndef subway_hpp
#define subway_hpp


#include <list>
#include "station.hpp"
#include "connection.hpp"
#include "subwayPrinter.hpp"
#include <unordered_map>
#include <vector>

using std::list;
using std::unordered_map;

class Subway {
public:
    Subway() {}
    void addStation(string);
    void addConnection(string, string, string);
    bool hasStation(string);
    void printSubway();
    void printNetwork();
    list<Connection> searchRoute(string, string);
private:
    list<Station> m_stations;
    list<Connection> m_connections;
    /*
     // This works the other way is to define a hash<Station> in the std namespace then unordered_map will automatically pick it.
     // Defined   struct hash<Station>   in the station.hpp
    class HashFunc{
    public:
        std::size_t operator()(const Station& st) const {
            return std::hash<string>()(st.getName());
        }
    };
    unordered_map<Station, list<Station>, HashFunc> m_network;
     */
    
    // for unordered_map to take custom type as key we need to define    struct hash<custom_type>  with operator() overloaded.
    // for this specific case I've defined it in the station.hpp file
    unordered_map<Station, list<Station>> m_network;
    
    void getRoute(std::vector<Station>&, list<Connection>&);
//    Connection& getConnection(Station&, Station&);
    void printStations();
    void printConnections();
    void addToNetwork(Station, Station);
};


#endif /* subway_hpp */
