//
//  main.cpp
//  2_subwayRouteFinder
//
//  Created by Ajay Singh on 17/05/21.
//

#include "subwayLoader.hpp"
#include "subwayPrinter.hpp"
#include <iostream>
#include <list>

int main() {
    SubwayLoader loader;
    ifstream file("/Users/ajay/Desktop/toDo/dataScience/Interview/Design_Patterns/code/2_subwayRouteFinder/2_subwayRouteFinder/Loader/ObjectvilleSubway", std::ios::in);
    if (!file.is_open()) {
        std::cout << "could not open file" << std::endl;
        return -1;
    }
    Subway objectvilleSubway = loader.loadFromFile(file);
    SubwayPrinter printer;
//    objectvilleSubway.printSubway();
//    objectvilleSubway.printNetwork();
    list<Connection> route = objectvilleSubway.searchRoute("Mighty Gumball, Inc.", "Choc-O-Holic, Inc.");
    printer.printIterableObject(route);
    
    
    return 0;
}


/*
 objectvilleSubway.searchRoute("Mighty Gumball, Inc.", "Choc-O-Holic, Inc.");
 
 Start out at Mighty Gumball, Inc..
 Get on the Jacobson Line heading towards Servlet Springs.
 When you get to Servlet Springs, get off the Jacobson Line.
 Switch over to the Wirfs-Brock Line, heading towards Objectville Diner. Continue past Objectville Diner...
 When you get to Head First Lounge, get off the Wirfs-Brock Line. Switch over to the Gamma Line, heading towards OOA&D Oval.
 When you get to OOA&D Oval, get off the Gamma Line.
 Switch over to the Meyer Line, heading towards CSS Center.
 Continue past CSS Center...
 When you get to Head First Theater, get off the Meyer Line.
 Switch over to the Rumbaugh Line, heading towards Choc-O-Holic, Inc.. Get off at Choc-O-Holic, Inc. and enjoy yourself!
 */
