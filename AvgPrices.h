// This header file was provided as a part of Individual Project 1
// for the C++ Programming with Applications in Finance module.

#ifndef AVGPRICES_H_INCLUDED
#define AVGPRICES_H_INCLUDED

// generates a path with a number x from 0 to (2^N)-1
// returns a path with number according to convention
// and writes this path into the array Path of length N
void GenPathByNumber(int x, int N, int* Path);

// generates an array of prices along the path and writes them into the array Prices of length N
void GenPricesByPath(double S0, double U,double D, int* Path, int N, double* Prices);

// generates a probability of the path
double GenProbabilityByPath(double U,double D, double R, int* Path, int N);

//computing arithmetic average of the array of prices
double ArAverage(double* Prices, int N);

//computing geometric average of the array of prices
double GeAverage(double* Prices, int N);


#endif // AVGPRICES_H_INCLUDED
