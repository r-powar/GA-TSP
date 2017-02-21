//
//  TravellingSalesMan.cpp
//  GA_TSP
//
//  Created by Raj Powar on 2/20/17.
//  Copyright © 2017 Raj Powar. All rights reserved.
//

#include "TravellingSalesMan.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

double randomNumber(double value){
    double randomVal = ((double)rand() * value)/(double)RAND_MAX;
    return randomVal;

}


double TravellingSalesMan::sumDistance(int *val){
    double distance = 0;
    
    for(int i = 0; i < cities - 1; i++){
        double x = coordinateX[val[i]] - coordinateX[val[i + 1]];
        double y = coordinateY[val[i]] - coordinateY[val[i + 1]];
        
        distance += sqrt(pow(x, 2.0) + pow(y, 2.0));
    }
    
    double x = coordinateX[cities - 1] - coordinateX[val[0]];
    double y = coordinateY[cities - 1] - coordinateY[val[0]];
    
    distance += sqrt(pow(x, 2.0) + pow(y, 2.0));
    return distance;
}

double TravellingSalesMan::estimateFitness(int *val){
    return 1/sumDistance(val);
}

TravellingSalesMan::TravellingSalesMan(double crossProbab, double mutProbab){
    crossoverProbability = crossProbab;
    mutationProbability = mutProbab;
    currPopultaion = new int[chromosomes][cities];
    newPopulation = new int[chromosomes][cities];
    
    
    for(int cordinates = 0; cordinates < cities; cordinates++){
        coordinateX[cordinates] = randomNumber(xMax);
        coordinateY[cordinates] = randomNumber(Ymax);
        
    }
    
    generateRandomPopulation();
    
}

void TravellingSalesMan::generateRandomPopulation(){
    
    for(int chromosomeVal = 0; chromosomeVal < chromosomes; chromosomeVal++){
        
        for(int i = 0; i < cities; i++){
            *currPopultaion[i] = i;
        }
        
        for(int i = cities-1; i > 0; i--){
            int random = (int)randomNumber(i);
            int temp = *currPopultaion[i];
            *currPopultaion[i] = *currPopultaion[random];
            *currPopultaion[random] = temp;
        }
    }
}

double TravellingSalesMan::getAverageDistance(){
    double distance = 0;
    
    for(int i = 0; i < chromosomes; i++){
        distance += sumDistance(currPopultaion[i]);
    }
    double average = distance/chromosomes;
    return average;
}

void TravellingSalesMan::copyNewPopulation(int *val, int offset){
    
    for(int i = 0; i < cities; i++){
        newPopulation[offset][i] = val[i];
    }
}

void TravellingSalesMan::generateNextPopultaion(){
    
    //Set set a fitness for each chromosome
    double bestFitness[chromosomes];
    
    for(int i = 0; i < chromosomes; i++){
        bestFitness[i] = estimateFitness(currPopultaion[i]);
    }
    
    //Find the best two chromosomes
    int best1 = 0, best2 = 0;
    
    best1 = max_element(bestFitness, bestFitness + chromosomes) - bestFitness;
    this->bestChromosome = currPopultaion[best1];
    
    double maxFitness = 0;
    for(int i = 0; i < chromosomes; i++){
        if(i != best1 && bestFitness[i] > maxFitness){
            maxFitness = bestFitness[i];
            best2 = i;
        }
    }
    
    //copy the calculated two best solutions to the new population
    int j = 0;
    copyNewPopulation(currPopultaion[best1], j);
    j++;
    copyNewPopulation(currPopultaion[best2], j);
    j++;
    
    //Fill up the rest of the new population
    
    
    
}
