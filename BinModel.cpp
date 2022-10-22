// Code was taken from "Numerical Methods in Finance with C++" Textbook
// (section 1.3, p11) By Maciej J. Capinski and Tomasz Zastawniak

#include <iostream>

using namespace std;


// Compute and return the risk-neutral probability (q).
double RiskNeutProb(double U, double D, double R)
{
    return (R-D)/(U-D);
}

// Get user's inputs and return 0 if the inputs are valid, otherwise return 1.
int GetInputData(double& S0, double& U, double& D, double& R)
{
    //entering data
    cout << "Enter S0: ";
    cin >> S0;
    cout << "Enter U: ";
    cin >> U;
    cout << "Enter D: ";
    cin >> D;
    cout << "Enter R: ";
    cin >> R;
    cout << endl;

    //making sure that 0<S0, -1<D<U, -1<R
    if (S0<=0.0 || U<=-1.0 || D<=-1.0 || U<=D || R<=-1.0)
    {
        cout << "Illegal data ranges" << endl;
        cout << "Terminating program" << endl;
        return 1;
    }

    //checking for arbitrage
    if (R>=U || R<=D)
    {
        cout << "Arbitrage exists" << endl;
        cout << "Terminating program" << endl;
        return 1;
    }

    cout << "Input data checked" << endl;
    cout << "There is no arbitrage" << endl << endl;

    return 0;
}
