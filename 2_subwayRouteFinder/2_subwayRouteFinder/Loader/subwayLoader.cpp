//
//  subwayLoader.cpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#include "subwayLoader.hpp"
#include <iostream>

Subway SubwayLoader::loadFromFile(ifstream& file) {
    Subway newSubway;
    getStations(file, newSubway);
    string lineName;
    while (getline(file, lineName)) {
//        std::cout << "\n  ### " << lineName << " ***\n";
        getConnections(file, newSubway, lineName);
    }
    return newSubway;
}

void SubwayLoader::getStations(ifstream& file, Subway& subway) {
    string station;
    while (getline(file, station) && station.size() > 0) {
        subway.addStation(station);
    }
//    std::cout << "\n  *** " << station << " ***\n";
}

void SubwayLoader::getConnections(ifstream& file, Subway& subway, string lineName) {
    string station1, station2;
    getline(file, station1);
    getline(file, station2);
    subway.addConnection(lineName, station1, station2);
//    std::cout << "\n  --------  " << station1 << " -- " << station2 << " ***\n";
    string nextStation;
    while (getline(file, nextStation) && nextStation.size() > 0) {
        station1 = station2;
        station2 = nextStation;
        subway.addConnection(lineName, station1, station2);
    }
}



/*
 1  Ajax Rapids
 2  UML Walk
 3  The Tikibean Lounge
 4  Head First Lounge
 5  Objectville Diner
 6  Servlet Springs
 7  Mighty Gumball, Inc.
 8  Java Ranch
 9  SRP Square
 10  JSP Junction
 11  GoF Gardens
 12  Break Neck Pizza
 13  Design Patterns Plaza
 14  OCP Orchard
 15  EJB Estates
 16  Boards 'R' Us
 17  HTML Heights
 18  Objectville Pizza Store
 19  JavaBeans Boulevard
 20  Weather-O-Rama, Inc.
 21  XHTML Expressway
 22  Infinite Circle
 23  LSP Lane
 24  Head First Labs
 25  Algebra Avenue
 26  Choc-O-Holic, Inc.
 27  Head First Theater
 28  DRY Drive
 29  PMP Place
 30  CSS Center
 31  Web Design Way
 32  OOA&D Oval
 33  SimUDuck Lake

 1  Booch Line : Ajax Rapids -> UML Walk
 2  Booch Line : UML Walk -> Ajax Rapids
 3  Booch Line : UML Walk -> Objectville Pizza Store
 4  Booch Line : Objectville Pizza Store -> UML Walk
 5  Booch Line : Objectville Pizza Store -> Head First Labs
 6  Booch Line : Head First Labs -> Objectville Pizza Store
 7  Booch Line : Head First Labs -> LSP Lane
 8  Booch Line : LSP Lane -> Head First Labs
 9  Booch Line : LSP Lane -> JavaBeans Boulevard
 10  Booch Line : JavaBeans Boulevard -> LSP Lane
 11  Booch Line : JavaBeans Boulevard -> HTML Heights
 12  Booch Line : HTML Heights -> JavaBeans Boulevard
 13  Booch Line : HTML Heights -> Ajax Rapids
 14  Booch Line : Ajax Rapids -> HTML Heights
 15  Gamma Line : Head First Lounge -> OOA&D Oval
 16  Gamma Line : OOA&D Oval -> Head First Lounge
 17  Gamma Line : OOA&D Oval -> Head First Lounge
 18  Gamma Line : Head First Lounge -> OOA&D Oval
 19  Jacobson Line : Servlet Springs -> Mighty Gumball, Inc.
 20  Jacobson Line : Mighty Gumball, Inc. -> Servlet Springs
 21  Jacobson Line : Mighty Gumball, Inc. -> Java Ranch
 22  Jacobson Line : Java Ranch -> Mighty Gumball, Inc.
 23  Jacobson Line : Java Ranch -> JSP Junction
 24  Jacobson Line : JSP Junction -> Java Ranch
 25  Jacobson Line : JSP Junction -> GoF Gardens
 26  Jacobson Line : GoF Gardens -> JSP Junction
 27  Jacobson Line : GoF Gardens -> Servlet Springs
 28  Jacobson Line : Servlet Springs -> GoF Gardens
 29  Liskov Line : JSP Junction -> SRP Square
 30  Liskov Line : SRP Square -> JSP Junction
 31  Liskov Line : SRP Square -> OCP Orchard
 32  Liskov Line : OCP Orchard -> SRP Square
 33  Liskov Line : OCP Orchard -> EJB Estates
 34  Liskov Line : EJB Estates -> OCP Orchard
 35  Liskov Line : EJB Estates -> Design Patterns Plaza
 36  Liskov Line : Design Patterns Plaza -> EJB Estates
 37  Liskov Line : Design Patterns Plaza -> JSP Junction
 38  Liskov Line : JSP Junction -> Design Patterns Plaza
 39  Meyer Line : OOA&D Oval -> SimUDuck Lake
 40  Meyer Line : SimUDuck Lake -> OOA&D Oval
 41  Meyer Line : SimUDuck Lake -> Web Design Way
 42  Meyer Line : Web Design Way -> SimUDuck Lake
 43  Meyer Line : Web Design Way -> DRY Drive
 44  Meyer Line : DRY Drive -> Web Design Way
 45  Meyer Line : DRY Drive -> Head First Theater
 46  Meyer Line : Head First Theater -> DRY Drive
 47  Meyer Line : Head First Theater -> CSS Center
 48  Meyer Line : CSS Center -> Head First Theater
 49  Meyer Line : CSS Center -> OOA&D Oval
 50  Meyer Line : OOA&D Oval -> CSS Center
 51  Rumbaugh Line : Choc-O-Holic, Inc. -> XHTML Expressway
 52  Rumbaugh Line : XHTML Expressway -> Choc-O-Holic, Inc.
 53  Rumbaugh Line : XHTML Expressway -> Infinite Circle
 54  Rumbaugh Line : Infinite Circle -> XHTML Expressway
 55  Rumbaugh Line : Infinite Circle -> Head First Theater
 56  Rumbaugh Line : Head First Theater -> Infinite Circle
 57  Rumbaugh Line : Head First Theater -> Choc-O-Holic, Inc.
 58  Rumbaugh Line : Choc-O-Holic, Inc. -> Head First Theater
 59  Wirfs-Brock Line : XHTML Expressway -> Weather-O-Rama, Inc.
 60  Wirfs-Brock Line : Weather-O-Rama, Inc. -> XHTML Expressway
 61  Wirfs-Brock Line : Weather-O-Rama, Inc. -> HTML Heights
 62  Wirfs-Brock Line : HTML Heights -> Weather-O-Rama, Inc.
 63  Wirfs-Brock Line : HTML Heights -> UML Walk
 64  Wirfs-Brock Line : UML Walk -> HTML Heights
 65  Wirfs-Brock Line : UML Walk -> The Tikibean Lounge
 66  Wirfs-Brock Line : The Tikibean Lounge -> UML Walk
 67  Wirfs-Brock Line : The Tikibean Lounge -> Head First Lounge
 68  Wirfs-Brock Line : Head First Lounge -> The Tikibean Lounge
 69  Wirfs-Brock Line : Head First Lounge -> Objectville Diner
 70  Wirfs-Brock Line : Objectville Diner -> Head First Lounge
 71  Wirfs-Brock Line : Objectville Diner -> Servlet Springs
 72  Wirfs-Brock Line : Servlet Springs -> Objectville Diner
 73  Wirfs-Brock Line : Servlet Springs -> SRP Square
 74  Wirfs-Brock Line : SRP Square -> Servlet Springs
 75  Wirfs-Brock Line : SRP Square -> Break Neck Pizza
 76  Wirfs-Brock Line : Break Neck Pizza -> SRP Square
 77  Wirfs-Brock Line : Break Neck Pizza -> EJB Estates
 78  Wirfs-Brock Line : EJB Estates -> Break Neck Pizza
 79  Wirfs-Brock Line : EJB Estates -> Boards 'R' Us
 80  Wirfs-Brock Line : Boards 'R' Us -> EJB Estates
 81  Wirfs-Brock Line : Boards 'R' Us -> Web Design Way
 82  Wirfs-Brock Line : Web Design Way -> Boards 'R' Us
 83  Wirfs-Brock Line : Web Design Way -> PMP Place
 84  Wirfs-Brock Line : PMP Place -> Web Design Way
 85  Wirfs-Brock Line : PMP Place -> DRY Drive
 86  Wirfs-Brock Line : DRY Drive -> PMP Place
 87  Wirfs-Brock Line : DRY Drive -> Algebra Avenue
 88  Wirfs-Brock Line : Algebra Avenue -> DRY Drive
 89  Wirfs-Brock Line : Algebra Avenue -> LSP Lane
 90  Wirfs-Brock Line : LSP Lane -> Algebra Avenue
 91  Wirfs-Brock Line : LSP Lane -> XHTML Expressway
 92  Wirfs-Brock Line : XHTML Expressway -> LSP Lane
 
 */
