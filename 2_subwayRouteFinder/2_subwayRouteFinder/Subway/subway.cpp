//
//  subway.cpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#include "subway.hpp"
#include <algorithm> // find()
#include <queue>
#include <set>

void Subway::addStation(string name) {
    if (!hasStation(name))
        m_stations.push_back(Station(name));
}

bool Subway::hasStation(string name) {
    Station newStation(name);
    return std::find(m_stations.begin(), m_stations.end(), newStation) != m_stations.end();
}


void Subway::addConnection(string lineName, string station1Name, string station2Name) {
    if (hasStation(station1Name) && hasStation(station2Name)) {
        Station station1{station1Name}, station2{station2Name};
        m_connections.push_back(Connection(lineName, station1Name, station2Name));
        m_connections.push_back(Connection(lineName, station2Name, station1Name));
        addToNetwork(station1, station2);
        addToNetwork(station2, station1);
    }
}

void Subway::addToNetwork(Station station1, Station station2) {
    if (m_network.count(station1) > 0) {
        m_network[station1].push_back(station2);
    } else {
        m_network[station1] = {station2};
    }
}

void Subway::printSubway() {
    printStations();
    printConnections();
}

void Subway::printStations() {
    SubwayPrinter printer;
    printer.printIterableObject(m_stations);
}

void Subway::printConnections() {
    SubwayPrinter printer;
    printer.printIterableObject(m_connections);
}


void Subway::printNetwork() {
    SubwayPrinter printer;
    printer.printIterableObject(m_network);
}


list<Connection> Subway::searchRoute(string start, string destination) {
    list<Connection> route;
    Station startStation{start}, destinationStation{destination};
    std::queue<std::vector<Station>> bfsQueue;
    std::set<Station> visited;
    bfsQueue.push({startStation});
    bool found = false;
    
    std::vector<Station> path;
    
    while (!bfsQueue.empty() && !found) {
        path = bfsQueue.front();  bfsQueue.pop();
        Station current = *path.rbegin();
        if (current == destination) {
            found = true;
            break;
        }
        visited.insert(current);
        for (auto neighbour : m_network[current]) {
            if (visited.count(neighbour) == 0) {
                std::vector<Station> newPath{path};
                newPath.push_back(neighbour);
                bfsQueue.push(newPath);
            }
        }
    }
    
//    SubwayPrinter printer;
//    printer.printIterableObject(path);
    getRoute(path, route);
    
    return route;
}

void Subway::getRoute(std::vector<Station>& path, list<Connection>& route) {
    Station station1{path.front()};
    
    for (auto station2Iterator = path.begin() + 1; station2Iterator != path.end(); ++station2Iterator) {
        Station station2 = *station2Iterator;
        for (auto conn : m_connections) {
            if (conn.getStation1() == station1.getName() && conn.getStation2() == station2.getName()) {
                route.push_back(conn);
                break;
            }
        }
        station1 = station2;
    }
}
