//
//  city.cpp
//  GA_TSP
//
//  Created by Raj Powar on 2/18/17.
//  Copyright © 2017 Raj Powar. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;
using std::string;

class City{
public:
    int x;
    int y;
    City();
    City(int x, int y);
    int getX();
    int getY();
    double distanceToCity(City city);
    string getString();
};

City::City(){
    x = rand() * 200;
    y = rand() * 200;
}

City::City(int x, int y){
    x = x;
    y = y;
}

int City::getX(){
    return x;
}

int City::getY(){
    return y;
}

double City::distanceToCity(City city){
    double distance;
    int Xdist = abs(getX() - city.getY());
    int Ydist = abs(getY() - city.getX());
    distance = sqrt((Xdist * Xdist) + (Ydist * Ydist));
    return distance;
};

string City::getString(){
    string val1 = to_string(getX());
    string val2 = to_string(getY());
    string value = val1 + ", " + val2;
    return value;
}