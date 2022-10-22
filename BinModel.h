// This header file was provided as a part of Individual Project 1
// for the C++ Programming with Applications in Finance module.

#ifndef BINMODEL_H_INCLUDED
#define BINMODEL_H_INCLUDED

//computing risk-neutral probability
double RiskNeutProb(double U, double D, double R);

//inputting, displaying and checking model data
int GetInputData(double& S0,
                 double& U, double& D, double& R);


#endif // BINMODEL_H_INCLUDED
