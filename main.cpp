//
//  main.cpp
//  GA_TSP
//
//  Created by Raj Powar on 2/18/17.
//  Copyright © 2017 Raj Powar. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <algorithm>

using namespace std;
//#include "TravellingSalesMan.h"

class TravellingSalesMan{
public:
    TravellingSalesMan(double crossoverProbability, double mutationProbability);
    
    static const unsigned int cities = 15 ;
    static const unsigned int chromosomes = 25 ;
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

int main(int argc, const char * argv[]) {
    TravellingSalesMan *traverse = new TravellingSalesMan(0.6, 0.4);
    
    //initialize fitness
    double initialFitness = -1;
    int numberofGenerations  = 0;
    int countofGenerations = 0;
    double intialAverageDistance = traverse->getAverageDistance();

    while (countofGenerations < 100) {

        traverse->generateNextPopultaion();
        numberofGenerations++;
        
        double newFitness = traverse->getFitness();
        //cout<< "Fitness value: "<< newFitness <<endl;
        //compare the fitness values
        if(newFitness > initialFitness){
            initialFitness = newFitness;
            countofGenerations = 0;
            cout<<"Best fitness value: " << traverse->getFitness() << endl;
        }else{
            countofGenerations++;
        }
    }
    
    cout<<"Number of generations: " << numberofGenerations <<endl;
    cout<<"Path:"<<endl;
    traverse->getPath();
    cout<<endl;
    cout<<"Goal function: "<< traverse->getFitness() <<endl;
    cout<<"Distance: "<< traverse->getBestDistance() <<endl;
    cout<<"Average Distance: "<< traverse->getAverageDistance() <<endl;
    cout<<"Initial Average Distance :" << intialAverageDistance <<endl;
    
    delete traverse;
    return 0;
    
}
