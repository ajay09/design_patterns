//
//  connection.cpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#include "connection.hpp"

Connection::Connection(string line_name, string station1, string station2) : m_lineName(line_name), m_station1(station1), m_station2(station2) {}

string Connection::getLineName() {
    return m_lineName;
}

string Connection::getStation1() {
    return m_station1.getName();
}

string Connection::getStation2() {
    return m_station2.getName();
}

// to print a connection using out operator
ostream& operator<<(ostream& out, const Connection& con) {
    out << con.m_lineName << " : " << con.m_station1 << " -> " << con.m_station2;
    return out;
}
