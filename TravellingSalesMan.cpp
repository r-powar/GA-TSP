//
//  TravellingSalesMan.cpp
//  GA_TSP
//
//  Created by Raj Powar on 2/20/17.
//  Copyright © 2017 Raj Powar. All rights reserved.
//

//#include "TravellingSalesMan.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <algorithm>

using namespace std;

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

double randomNumber(double value){
    double randomVal = ((double)rand() * value)/(double)RAND_MAX;
    return randomVal;

}

double randomize(double val){
    double randomVal = ((double)rand() * val)/((double)RAND_MAX+1);
    return randomVal;
}


void TravellingSalesMan::getPath(){
    for(int i = 0; i < cities; i++){
        cout<< bestChromosome[i]<<",";
    }
}

double TravellingSalesMan::getFitness(){
    return estimateFitness(bestChromosome);
}

double TravellingSalesMan::getBestDistance(){
    return sumDistance(bestChromosome);
}

int *TravellingSalesMan::selectionAlgorithm(double *val){
    double total = 0;
    
    //total sum of all chromosomes in the population
    for(int i = 0; i < chromosomes; i++){
        total+= val[i];
    }
    
    double randomVal = randomNumber(total);
    
    total = 0;
    
    for(int i = 0; i < chromosomes; i++){
        total += val[i];
        if(total >= randomVal){
            return currPopultaion[i];
        }
    }
    
    return 0;
}

double TravellingSalesMan::sumDistance(int *val){
    double distance = 0;
    
    for(int i = 0; i < cities - 1; i++){

        double x = coordinateX[val[i]] - coordinateX[val[i + 1]];
        double y = coordinateY[val[i]] - coordinateY[val[i + 1]];

        distance += sqrt(pow(x, 2.0) + pow(y, 2.0));
    }
    
    double x = coordinateX[val[cities - 1]] - coordinateX[val[0]];
    double y = coordinateY[val[cities - 1]] - coordinateY[val[0]];
    
    distance += sqrt(pow(x, 2.0) + pow(y, 2.0));
    
    return distance;
}

double TravellingSalesMan::estimateFitness(int *val){
    return 1/sumDistance(val);
}

void TravellingSalesMan::setRandomPopulation(int *val){
    
    for(int i = 0; i < cities; i++){
        val[i] = i;
    }
    for(int i = cities-1; i > 0; i--){
        int random = (int)randomNumber(i);
        int temp = val[i];
        val[i] = val[random];
        val[random] = temp;
    }
    
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
        setRandomPopulation(currPopultaion[chromosomeVal]);
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


void TravellingSalesMan::rectifyVal(int *childOne, int value, int *childTwo){
    
    for(int i = 0; i < cities; i++){
        int *comparedVal = find(childOne, childOne + cities, childTwo[i]);
        
        if(comparedVal == (childOne + cities)){
            childOne[value] = childTwo[i];
            break;
        }
        
    }
}

bool TravellingSalesMan::checkforDuplicate(int *chromosome , int count){
    
    for(int i = 0; i < count; i++){
        int comparedValues = 0;
        
        for(int j = 0; j < cities; j++){
            if(chromosome[j] != newPopulation[i][j]){
                break;
            }
            comparedValues++;
        }
        
        if(comparedValues == cities){
            return true;
        }
    }
    return false;
}

void TravellingSalesMan::crossover(int *parentOne, int *parentTwo, int *childOne, int *childTwo){
    //in case if there is no crossover
    double random = randomNumber(1);
    if(random > crossoverProbability){
        //copy over the parents to child
        
        memcpy(childOne, parentOne, sizeof(int) * cities);
        memcpy(childTwo, parentTwo, sizeof(int) * cities);
        return;
    }
    
    //Preforming corssover
    int cutoff1 = (int)randomNumber(cities);
    int cutoff2 = (int)randomNumber(cities);
    while(cutoff2 == cutoff1){
        cutoff2 = (int)randomize(cities);
    }
    
    int start;
    int end;
    
    if(cutoff1 < cutoff2){
        start = cutoff1;
        end = cutoff2;
    }else{
        start = cutoff2;
        end = cutoff1;
    }
    
    memcpy(childOne, parentOne, sizeof(int) *cities);
    memcpy(childTwo, parentTwo, sizeof(int) *cities);
    
    memcpy(childOne + start, parentTwo + start, sizeof(int) * (end - start));
    memcpy(childTwo + start, parentOne + start, sizeof(int) * (end - start));
    
    for(int i = 0; i < cities; i++){
        if(!(i < end && i >= start)){
            for(int j = start; j < end; j++){
                if(childOne[i] == childOne[j]){
                    childOne[i] = -1;
                }
                
                if(childTwo[i] == childTwo[j]){
                    childTwo[i] = -1;
                }
            }
        }
    }
    
    for(int checkVal = 0; checkVal < cities; checkVal++){
        if(childOne[checkVal] == -1){
            //rectify value
            rectifyVal(childOne, checkVal, childTwo);
        }
        if(childTwo[checkVal] == -1){
            //recitfy value
            rectifyVal(childTwo, checkVal, childOne);
        }
    }
    
    
    
}

void TravellingSalesMan::mutation(int *val){
    //mutation did not occur
    double random = randomNumber(1);
    if(random > mutationProbability){
        return;
    }
    
    int temp;
    int mutate1 = (int)randomize(cities);
    int mutate2 = (int)randomize(cities);
    while(mutate1 == mutate2){
        mutate2 = (int)randomize(cities);
    }
    
    temp = val[mutate1];
    val[mutate1] = val[mutate2];
    val[mutate2] = temp;
    
}

int TravellingSalesMan::getMaximum(double *arr){
    double temp = arr[0];
    int maxIndex = 0;
    for(int i = 1; i < chromosomes; i++){
        if(arr[i] > temp){
            temp = arr[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

void TravellingSalesMan::generateNextPopultaion(){
    
    //Set set a fitness for each chromosome
    double bestFitness[chromosomes];
    
    for(int i = 0; i < chromosomes; i++){
        bestFitness[i] = estimateFitness(currPopultaion[i]);
    }
    
    //Find the best two chromosomes
    int best1 = 0;
    int best2 = 0;
    //best1 = std::distance(bestFitness, max_element(bestFitness, bestFitness + chromosomes));
    //best1 = max_element(bestFitness, bestFitness + chromosomes) - bestFitness;
    
    //Get the maximum value
    best1 = getMaximum(bestFitness);
    this->bestChromosome = currPopultaion[best1];
    
    double maxFitness = 0;
    for(int i = 0; i < chromosomes; i++){
        if(i != best1 && bestFitness[i] > maxFitness){
            maxFitness = bestFitness[i];
            best2 = i;
        }
    }
    
    
    //copy the calculated two best solutions to the new population
    int count = 0;
    copyNewPopulation(currPopultaion[best1], count);
    count++;
    copyNewPopulation(currPopultaion[best2], count);
    count++;
    //Fill up the rest of the new population
    while(true){
        int *chromosome1;
        int *chromosome2;
        
        chromosome1 = selectionAlgorithm(bestFitness);
        chromosome2 = selectionAlgorithm(bestFitness);
        
        while(chromosome2 == chromosome1){
            chromosome2 = selectionAlgorithm(bestFitness);
        }
        
        int offspring1[cities];
        int offspring2[cities];
        crossover(chromosome1, chromosome2, offspring1, offspring2);
        mutation(offspring1);
        mutation(offspring2);
        

        if(!checkforDuplicate(offspring1, count)){
            copyNewPopulation(offspring1, count);
            count++;
        }

        if(count == chromosomes){
            break;
        }
            
        if(!checkforDuplicate(offspring2, count)){
            copyNewPopulation(offspring2, count);
            count++;
        }
        
        if(count == chromosomes){
            break;
        }
        
        
    }
    
    //replacing the old population with the new population
    for(int i = 0; i < chromosomes; i++){
        memcpy(currPopultaion[i], newPopulation[i], sizeof(int) * cities);
    }
    
    
    
}
