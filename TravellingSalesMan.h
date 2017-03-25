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
    
    static const unsigned int cities = 20 ;
    static const unsigned int chromosomes = 30 ;
    int xMax = 100;
    int Xmin = 0;
    int Ymax = 50;
    int Ymin = 0 ;
    
    void generateRandomPopulation();
    void generateNextPopultaion();
    double getFitness();
    double getBestDistance();
    double getAverageDistance();
    void getCurrPopulation();
    double sumDistance(int * val);
    void copyNewPopulation(int *val, int j);
    void crossover(int * parentOne, int *parentTwo, int *childOne, int *childTwo);
    void mutation(int *val);
    void getPath();
    int getMaximum(double *val);
    void setRandomPopulation(int *val);
    
private:
    double crossoverProbability, mutationProbability;
    int *bestChromosome;
    
    double coordinateX[cities];
    double coordinateY[cities];
    
    int(*currPopultaion)[cities];
    int(*newPopulation)[cities];
    
    double estimateFitness(int *val);
    
    int * selectionAlgorithm(double *val);
    void rectifyVal(int *childOne, int value, int *childTwo);
    bool checkforDuplicate(int *chromosomes, int count);
    
};

#endif /* TravellingSalesMan_hpp */
