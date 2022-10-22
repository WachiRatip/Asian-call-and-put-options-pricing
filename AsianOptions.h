// This header file was provided as a part of Individual Project 1
// for the C++ Programming with Applications in Finance module.

#ifndef ASIANOPTIONS_H_INCLUDED
#define ASIANOPTIONS_H_INCLUDED

//inputting and displaying option data
int GetInputData(int& N, double& K);

// pricing Asian option by iterating over the paths x
// that change from 0 to (2^N)-1, for each x
// find the corresponding payoff and the probability using
// the functions from AvgPrices
double Price(double S0, double U, double D,
                double R, int N, double K,
                double (*Payoff)(double z, double K),
                double (*AvgType)(double* Prices, int N));

//computing asian call payoff
double AsianCallPayoff(double avgPrice, double K);

//computing asian put payoff
double AsianPutPayoff(double avgPrice, double K);

#endif // ASIANOPTIONS_H_INCLUDED
