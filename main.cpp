#include <iostream>
#include <cmath>
#include "BinModel.h"
#include "AvgPrices.h"
#include "AsianOptions.h"

using namespace std;

int main()
{
    double S0;          //intial stock price
    double U;           //move up factor
    double D;           //move down factor
    double R;           //risk-free factor
    int N;              //number of steps to expiry
    double K;           //strike price

    //Set parameters inputs.
    if (GetInputData(S0,U,D,R)==1) return 1;

    //Set strike price and steps to expiry.
    if (GetInputData(N,K)==1) return 1;

    //In case of arithmetic mean
    cout << "In case of arithmetic mean" << endl;
    cout << "Asian call option price = "
         << Price(S0,U,D,R,N,K, AsianCallPayoff, ArAverage)
         << endl << endl;

    cout << "Asian put option price = "
         << Price(S0,U,D,R,N,K, AsianPutPayoff, ArAverage)
         << endl << endl;

    //In case of geometric mean
    cout << "In case of geometric mean" << endl;
    cout << "Asian call option price = "
         << Price(S0,U,D,R,N,K, AsianCallPayoff, GeAverage)
         << endl << endl;

    cout << "Asian put option price = "
         << Price(S0,U,D,R,N,K, AsianPutPayoff, GeAverage)
         << endl << endl;

    return 0;
}
