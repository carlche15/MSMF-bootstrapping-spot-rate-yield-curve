#include <iostream>
#include <cmath>

using namespace std;

#include "Bond.h"

Bond::Bond(string name, double coupon, long issueDate, long maturityDate, int compoundingFrequencyPerAnnum)
{
    this->name = name;
    this->coupon = coupon;
    this->issueDate = issueDate;
    this->maturityDate = maturityDate;
    this->compoundingFrequencyPerAnnum = compoundingFrequencyPerAnnum;
    this->numberOfCouponPayments = (name.compare("6m") == 0) ? 1 : (maturityDate - issueDate)/10000*compoundingFrequencyPerAnnum;
}

void Bond::SetPrice(double price, double faceValue)
{
    this->price = price;
    this->faceValue = faceValue;
}

void Bond::SetPrice(double price)
{
    SetPrice(price, 1000.0);
}

string Bond::GetName() const
{
    return name;
}

double Bond::ComputeYTM()
{
    // bisection parameters
    //
    double ytm = 0.0;
    double tolerance = 1.0e-4;
    double a = 0.0, b = 100.0, c = 0.0;     // note that starting range is from 0 to 100.0 percent.  should be fine for all bonds

    do
    {
        double fa = ComputePrice(faceValue, coupon/100.0/compoundingFrequencyPerAnnum,
                                 a/100.0/compoundingFrequencyPerAnnum, numberOfCouponPayments) - price/100.0*faceValue;
        double fb = ComputePrice(faceValue, coupon/100.0/compoundingFrequencyPerAnnum,
                                 b/100.0/compoundingFrequencyPerAnnum, numberOfCouponPayments) - price/100.0*faceValue;

        if (abs(fa) <= tolerance)
        {
            ytm = a;
            break;
        }
        else if (abs(fb) <= tolerance)
        {
            ytm = b;
            break;
        }
        else if ((fa*fb) < 0.0)
        {
            c = (a+b)/2.0;
            double fc = ComputePrice(faceValue, coupon/100.0/compoundingFrequencyPerAnnum,
                                     c/100.0/compoundingFrequencyPerAnnum, numberOfCouponPayments) - price/100.0*faceValue;
            if (abs(fc)<= tolerance)
            {
                ytm = c;
                break;
            }
            if (fa*fc < 0.0) b = c;
            else a = c;
        }
        else
        {
            cout << "Problem:  Lower and upper bounds of the starting range does not have a root." << endl;
            return -1.0;
        }

    }
    while(true);

    return ytm;
}

double Bond::ComputePrice(double faceValue, double coupon, double ytm, int numberOfCouponPayments)
{
    double price = 0.0;

    // discount the coupon payments
    //
    for (int i = 0; i < numberOfCouponPayments; ++i)
    {
        price += coupon*faceValue/pow(1.0 + ytm, i+1);
    }

    // discount the bond face value
    //
    price += faceValue/pow(1.0 + ytm, numberOfCouponPayments);

    return price;
}

double Bond::BootstrappingSpotRate(vector<double>& vectSpotRates, int spotRatesLength,
                                   int interpolatedTenorStart, int interpolatedTenorEnd)
{
    // bisection parameters
    //
    double ytm = 0.0;
    double tolerance = 1.0e-4;
    double a = 0.0, b = 100.0, c = 0.0;

    vector<double> vectSpotRatesA(spotRatesLength, 0.0);
	vector<double> vectSpotRatesB(spotRatesLength, 0.0);
	vector<double> vectSpotRatesC(spotRatesLength, 0.0);

    do
    {
        for (int i = 0; i <= interpolatedTenorStart; ++i)
        {
            vectSpotRatesA[i] = vectSpotRates[i];
            vectSpotRatesB[i] = vectSpotRates[i];
        }

        for (int i = interpolatedTenorStart+1; i <= interpolatedTenorEnd; ++i)
        {
            vectSpotRatesA[i] = vectSpotRates[interpolatedTenorStart] + (a-vectSpotRates[interpolatedTenorStart])
                            *(i-interpolatedTenorStart)/(interpolatedTenorEnd-interpolatedTenorStart);
            vectSpotRatesB[i] = vectSpotRates[interpolatedTenorStart] + (b-vectSpotRates[interpolatedTenorStart])
                            *(i-interpolatedTenorStart)/(interpolatedTenorEnd-interpolatedTenorStart);
        }

        for (int i = 0; i < spotRatesLength; ++i)
        {
            vectSpotRatesA[i] = vectSpotRatesA[i]/100.0/compoundingFrequencyPerAnnum;
            vectSpotRatesB[i] = vectSpotRatesB[i]/100.0/compoundingFrequencyPerAnnum;
        }

        double fa = ComputePrice(faceValue, coupon/100.0/compoundingFrequencyPerAnnum, vectSpotRatesA, spotRatesLength,
                                 numberOfCouponPayments) - price/100.0*faceValue;
        double fb = ComputePrice(faceValue, coupon/100.0/compoundingFrequencyPerAnnum, vectSpotRatesB, spotRatesLength,
                                 numberOfCouponPayments) - price/100.0*faceValue;

        if (abs(fa) <= tolerance)
        {
            for (int i = interpolatedTenorStart+1; i <= interpolatedTenorEnd; ++i)
            {
                vectSpotRates[i] = vectSpotRates[interpolatedTenorStart] + (a-vectSpotRates[interpolatedTenorStart])
                               *(i-interpolatedTenorStart)/(interpolatedTenorEnd-interpolatedTenorStart);
            }
            break;
        }
        else if (abs(fb) <= tolerance)
        {
            for (int i = interpolatedTenorStart+1; i <= interpolatedTenorEnd; ++i)
            {
                vectSpotRates[i] = vectSpotRates[interpolatedTenorStart] + (b-vectSpotRates[interpolatedTenorStart])
                               *(i-interpolatedTenorStart)/(interpolatedTenorEnd-interpolatedTenorStart);
            }
            break;
        }
        else if ((fa*fb) < 0.0)
        {
            c = (a+b)/2.0;

            for (int i = 0; i <= interpolatedTenorStart; ++i)
            {
                vectSpotRatesC[i] = vectSpotRates[i];
            }

            for (int i = interpolatedTenorStart+1; i <= interpolatedTenorEnd; ++i)
            {
                vectSpotRatesC[i] = vectSpotRates[interpolatedTenorStart] + (c-vectSpotRates[interpolatedTenorStart])
                                *(i-interpolatedTenorStart)/(interpolatedTenorEnd - interpolatedTenorStart);
            }
            for (int i = 0; i < spotRatesLength; ++i)
            {
                vectSpotRatesC[i] = vectSpotRatesC[i]/100.0/compoundingFrequencyPerAnnum;
            }

            double fc = ComputePrice(faceValue, coupon/100.0/compoundingFrequencyPerAnnum, vectSpotRatesC, spotRatesLength,
                                     numberOfCouponPayments) - price/100.0*faceValue;
            if (abs(fc)<= tolerance)
            {
                for (int i = interpolatedTenorStart+1; i <= interpolatedTenorEnd; ++i)
                {
                    vectSpotRates[i] = vectSpotRates[interpolatedTenorStart] + (c-vectSpotRates[interpolatedTenorStart])
                                   *(i-interpolatedTenorStart)/(interpolatedTenorEnd-interpolatedTenorStart);
                }
                break;
            }
            if (fa*fc < 0.0) b = c;
            else a = c;
        }
        else
        {
            cout << "Problem:  Lower and upper bounds of the starting range does not have a root." << endl;
            return -1.0;
        }

    }
    while(true);

    return ytm;
}

double Bond::ComputePrice(double faceValue, double coupon, vector<double> vectSpotRates, int spotRatesLength, int numberOfCouponPayments)
{
    double price = 0.0;

    // discount the coupon payments
    //
    for (int i = 0; i < numberOfCouponPayments; ++i)
    {
        price += coupon*faceValue/pow(1.0 + vectSpotRates[i], i+1);
    }

    // discount the bond face value
    //
    price += faceValue/pow(1.0 + vectSpotRates[numberOfCouponPayments-1], numberOfCouponPayments);

    return price;
}

