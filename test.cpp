#include <iostream>
#include <cmath>
#include "BinModel.h"
#include "AvgPrices.h"
#include "AsianOptions.h"

using namespace std;

// Unit tests
void test_risk_neutral_prob(int* pass, int* fail)
{
    if (RiskNeutProb(1.0,0.0,0.5)==0.5
        && RiskNeutProb(3.0,1.0,1.5)==0.25
        && RiskNeutProb(0.5,-0.5,0.0)==0.5
        )
    {
        cout << "Test for RiskNeutProb function has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for RiskNeutProb function has been FAILED."
             << endl;
        *(fail)+=1;
    }

}

void test_average_functions(int* pass, int* fail)
{
    int N=10;
    double Prices[N] = {1,2,3,4,5,6,7,8,9,10};

    if (ArAverage(Prices, N)==5.5)
    {
        cout << "Test for ArAverage function has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for ArAverage function has been FAILED."
             << endl;
        *(fail)+=1;
    }

    if (fabs(GeAverage(Prices, N)-4.52872868812) < 1e-11)
    {
        cout << "Test for GeAverage function has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for GeAverage function has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

void test_asian_options_payoff(int* pass, int* fail)
{
    if (AsianCallPayoff(10.5,5.0)==5.5
        && AsianCallPayoff(10.5,15.0)==0.0
        )
    {
        cout << "Test for AsianCallPayoff function has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for AsianCallPayoff function has been FAILED."
             << endl;
        *(fail)+=1;
    }

    if (AsianPutPayoff(10.5,15.0)==4.5
        && AsianPutPayoff(10.5,5.0)==0.0
        )
    {
        cout << "Test for AsianPutPayoff function has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for AsianPutPayoff function has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

void test_gen_path_by_number(int* pass, int* fail)
{
    //Mutable path.
    int path[3];

    //Set all acutal paths
    int paths[8][3] = {
        {0,0,0}, {1,0,0}, {0,1,0}, {1,1,0},
        {0,0,1}, {1,0,1}, {0,1,1}, {1,1,1}
    };

    //Count the correct results from GenPathByNumber.
    int count=0;
    for (int i=0; i<8; i++)
    {
        GenPathByNumber(i, 3, path);
        if (path[0]==paths[i][0]
            && path[1]==paths[i][1]
            && path[2]==paths[i][2])
            count+=1;
    }

    if (count==8)
    {
        cout << "Test for GenPathByNumber function has been PASSED."
            << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for GenPathByNumber function has been FAILED."
            << endl;
        *(fail)+=1;
    }
}

void test_gen_prices_by_path(int* pass, int* fail)
{
    //Mutable prices
    double price[3];

    //Set all paths and all acutal prices
    int paths[8][3] = {
        {0,0,0}, {1,0,0}, {0,1,0}, {1,1,0},
        {0,0,1}, {1,0,1}, {0,1,1}, {1,1,1}
    };
    double prices[8][3] = {
        {1,1,1}, {2,2,2}, {1,2,2}, {2,4,4},
        {1,1,2}, {2,2,4}, {1,2,4}, {2,4,8}
    };

    //Count the correct results from GenPricesByPath.
    int count=0;
    for (int i=0; i<8; i++)
    {
        GenPricesByPath(1,1,0,paths[i],3,price);
        if (price[0]==prices[i][0]
            && price[1]==prices[i][1]
            && price[2]==prices[i][2])
            count+=1;
    };

    if (count==8)
    {
        cout << "Test for GenPricesByPath function has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for GenPricesByPath function has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

void test_gen_prob_by_path(int* pass, int* fail)
{
    //Set all paths
    int paths[8][3] = {
        {0,0,0}, {1,0,0}, {0,1,0}, {1,1,0},
        {0,0,1}, {1,0,1}, {0,1,1}, {1,1,1}
    };

    //Count the correct results from GenProbabilityByPath.
    int count=0;
    for (int i=0; i<8; i++)
    {
        if (GenProbabilityByPath(1,0,0.5,paths[i],3)==0.125) count+=1;
    }
    if (count==8)
    {
        cout << "Test for GenProbabilityByPath function has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for GenProbabilityByPath function has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

// Integration tests
void test_call_option_with_ari_avg(int* pass, int* fail)
{
    //Parameters settings
    int N=3;
    double S0[6]={1,1,1,2,2,2}, U[6]={1,1,1,1,0.75,0.75}, D[6]={0,0.25,0.25,0.25,0.25,-0.25}, R[6]={0.5,0.5,0.5,0.5,0.5,0.5}, K[6]={2,2,1.5,4.5,4.5,4.5};

    //The exact results
    double exact[6] = {0.185185185, 0.148148148, 0.259259259, 0.21399177, 0.168981481, 0.295138889};

    //Count the correct results.
    int count=0;
    for (int i=0; i<6; i++)
    {
        if (fabs(Price(S0[i],U[i],D[i],R[i],N,K[i], AsianCallPayoff, ArAverage)-exact[i]) < 1e-9) count+=1;
    }
    if (count==6)
    {
        cout << "Test for AsianCallPayoff with ArAverage has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for AsianCallPayoff with ArAverage has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

void test_put_option_with_ari_avg(int* pass, int* fail)
{
    //Parameters settings
    int N=3;
    double S0[6]={1,1,1,2,2,2}, U[6]={1,1,1,1,0.75,0.75}, D[6]={0,0.25,0.25,0.25,0.25,-0.25}, R[6]={0.5,0.5,0.5,0.5,0.5,0.5}, K[6]={2,2,1.5,4.5,4.5,4.5};

    //The exact results
    double exact[6] = {0.074074074, 0.037037037, 0.0, 0.139917695, 0.094907407, 0.221064815};

    //Count the correct results.
    int count=0;
    for (int i=0; i<6; i++)
    {
        if (fabs(Price(S0[i],U[i],D[i],R[i],N,K[i], AsianPutPayoff, ArAverage)-exact[i]) < 1e-9) count+=1;
    }
    if (count==6)
    {
        cout << "Test for AsianPutPayoff with ArAverage has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for AsianPutPayoff with ArAverage has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

void test_call_option_with_geo_avg(int* pass, int* fail)
{
    //Parameters settings
    int N=3;
    double S0[6]={1,1,1,2,2,2}, U[6]={1,1,1,1,0.75,0.75}, D[6]={0,0.25,0.25,0.25,0.25,-0.25}, R[6]={0.5,0.5,0.5,0.5,0.5,0.5}, K[6]={2,2,1.5,4.5,4.5,4.5};

    //The exact results
    double exact[6] = {0.136838674, 0.11234918, 0.214517019, 0.152273015, 0.110904566, 0.20803867};

    //Count the correct results.
    int count=0;
    for (int i=0; i<6; i++)
    {
        if (fabs(Price(S0[i],U[i],D[i],R[i],N,K[i], AsianCallPayoff, GeAverage)-exact[i]) < 1e-9) count+=1;
    }
    if (count==6)
    {
        cout << "Test for AsianCallPayoff with GeAverage has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for AsianCallPayoff with GeAverage has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

void test_put_option_with_geo_avg(int* pass, int* fail)
{
    //Parameters settings
    int N=3;
    double S0[6]={1,1,1,2,2,2}, U[6]={1,1,1,1,0.75,0.75}, D[6]={0,0.25,0.25,0.25,0.25,-0.25}, R[6]={0.5,0.5,0.5,0.5,0.5,0.5}, K[6]={2,2,1.5,4.5,4.5,4.5};

    //The exact result
    double exact[6] = {0.079728811, 0.045980309, 0, 0.167683422, 0.119195151, 0.239009949};

    //Count the correct results.
    int count=0;
    for (int i=0; i<6; i++)
    {
        if (fabs(Price(S0[i],U[i],D[i],R[i],N,K[i], AsianPutPayoff, GeAverage)-exact[i]) < 1e-9) count+=1;
    }
    if (count==6)
    {
        cout << "Test for AsianPutPayoff with GeAverage has been PASSED."
             << endl;
        *(pass)+=1;
    }
    else
    {
        cout << "Test for AsianPutPayoff with GeAverage has been FAILED."
             << endl;
        *(fail)+=1;
    }
}

int main()
{
    int pass, fail;

    //Unit tests
    pass=0, fail=0;
    cout << "--Unit tests--" << endl;

    test_risk_neutral_prob(&pass, &fail);
    test_average_functions(&pass, &fail);
    test_asian_options_payoff(&pass, &fail);
    test_gen_path_by_number(&pass, &fail);
    test_gen_prices_by_path(&pass, &fail);
    test_gen_prob_by_path(&pass, &fail);

    cout << endl;
    cout << "The Unit tests passed "
         << pass << " of " << pass+fail
         << endl << endl;

    //Integration tests
    pass=0, fail=0;
    cout << "--Integration tests--" << endl;

    test_call_option_with_ari_avg(&pass, &fail);
    test_put_option_with_ari_avg(&pass, &fail);
    test_call_option_with_geo_avg(&pass, &fail);
    test_put_option_with_geo_avg(&pass, &fail);

    cout << endl;
    cout << "The Integration tests passed "
         << pass << " of " << pass+fail
         << endl << endl;

    return 0;
}
