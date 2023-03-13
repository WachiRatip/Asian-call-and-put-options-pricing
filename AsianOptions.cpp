#include <iostream>
#include <cmath>
#include "BinModel.h"
#include "AvgPrices.h"

using namespace std;

// Return 0 if the inputs are valid, otherwise return 1.
int GetInputData(int& N, double& K)
{
    //entering data
    cout << "Enter N: ";
    cin >> N;
    cout << "Enter K: ";
    cin >> K;
    cout << endl;

    //check if N and K is greater than 0;
    if (N<=0 || N<=0)
    {
        cout << "The number of time steps and the strike price"
             << "must greater than 0"
             << endl;
        cout << "Terminating program"
             << endl;
        return 1;
    }

    return 0;
}

//pricing Asian option
double Price(double S0, double U, double D,
                double R, int N, double K,
                double (*Payoff)(double z, double K),
                double (*AvgType)(double* Prices, int N))
{
    //Mutable path and prices.
    int* path = new int[N];
    double* prices = new double[N];

    //The placeholder for the expected payoff.
    double Price=0;

    //Get the total number of paths
    int total = pow(2, N);

    //Iterate over the paths x from 0 to 2^{N}-1
    for (int x=0; x<total; x++)
    {
        //Get the path corresponding to the given paths number
        GenPathByNumber(x, N, path);
        //Get the price's scenario corresponding to the path
        GenPricesByPath(S0, U, D, path, N, prices);
        //Compute the average price corresponding to the path
        double avg = AvgType(prices, N);
        //Calculate the payoff with the given strike price
        double payoff = Payoff(avg, K);
        //Compute probability q of the path
        double p = GenProbabilityByPath(U, D, R, path, N);
        //Calculate the expected value of the payoff:
        //SUM(p_x*payoff_x)
        Price += p*payoff;
    }

    //Deallocate the memory
    delete[] path;
    delete[] prices;

    //Return the discounted expected payoff (the Asian option price)
    //which is E(payoff)/(1+R)^{N}
    return Price/pow(1+R, N);
}

//computing asian call payoff
double AsianCallPayoff(double avgPrice, double K)
{
    return fmax(avgPrice-K, 0.0);
}

//computing asian put payoff
double AsianPutPayoff(double avgPrice, double K)
{
    return fmax(K-avgPrice, 0.0);
}
