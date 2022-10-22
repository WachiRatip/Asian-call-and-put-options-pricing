#include <iostream>
#include <cmath>
#include "BinModel.h"

using namespace std;

//generates a path with a number x from 0 to (2^N)-1
void GenPathByNumber(int x, int N, int* Path)
{
    //To get the array path from the given x.
    //It is the same as converting x to its binary form.
    //When 1 donotes "growing" and 0 denotes "falling"
    //in the path, e.g., (1,0,0) refers the price moved up
    //at N=1, moved down at N=2 and then moved down at N=3.
    //Note: N is the time step.
    for (int i=0; i<N; i++)
    {
        *(Path+i) = x%2;
        x = x/2;
    }
}

//generates an array of prices along the path and
//writes them into the array Prices of length N
void GenPricesByPath(double S0, double U, double D,
                     int* Path, int N, double* Prices)
{
    for (int i=0; i<N; i++)
    {
        if (*(Path+i)==1)
        {
            *(Prices+i) = S0*(1+U);
        }
        else
        {
            *(Prices+i) = S0*(1+D);
        }
        S0 = *(Prices+i);
    }

}
//generates a probability of the path
double GenProbabilityByPath(double U,double D, double R,
                            int* Path, int N)
{
    //Compute the risk-neutral probability q.
    double q = RiskNeutProb(U,D,R);

    //Calculate the path's probability
    //P(path) = (q)^{i}(1-q)^{N-i}
    //when i is the number of growing in the path,
    //e.g., (1,0,1) --> i=2
    int i = 0;
    for (int j=0; j<N; j++) i += *(Path+j);

    return pow(q, i)*pow(1-q, N-i);
}
//computing arithmetic average of the array of prices
double ArAverage(double* Prices, int N)
{
    double sum=0.0;
    for (int i = 0; i < N; i++)
    {
        sum += *(Prices+i);
    }

    return sum/N;
}

//computing geometric average of the array of prices
double GeAverage(double* Prices, int N)
{
    double pro=1;

    // compute the product.
    for (int i = 0; i < N; i++)
    {
        pro *= *(Prices+i);
    }

    // return N-th root of the product.
    return pow(pro, 1.0/N);
}
