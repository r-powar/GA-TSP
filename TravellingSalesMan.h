//
//  TravellingSalesMan.hpp
//  GA_TSP
//
//  Created by Raj Powar on 2/20/17.
//  Copyright © 2017 Raj Powar. All rights reserved.
//

#ifndef TravellingSalesMan_hpp
#define TravellingSalesMan_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TravellingSalesMan{
public:
    TravellingSalesMan(double crossoverProbability, double mutationProbability);
    
    static const  int cities = 15;
    static const  int chromosomes = 20;
    int xMax = 1000;
    int Xmin = 0;
    int Ymax = 500;
    int Ymin = 0 ;
    
    void generateRandomPopulation();
    void generateNextPopultaion();
    double getFitness();
    string getBestPath();
    double getBestDistance();
    double getAverageDistance();
    void getCurrPopulation();
    double sumDistance(int * val);
    void copyNewPopulation(int *val, int j);
    
private:
    double crossoverProbability, mutationProbability;
    int *bestChromosome;
    
    double coordinateX[cities];
    double coordinateY[cities];
    
    int(*currPopultaion)[cities];
    int(*newPopulation)[cities];
    
    double estimateFitness(int *val);
    
    
};

#endif /* TravellingSalesMan_hpp */
