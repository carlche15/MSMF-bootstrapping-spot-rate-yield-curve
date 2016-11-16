#include <iostream>
#include <iomanip>
#include <vector>

#include "TermStructure.h"

TermStructure::TermStructure()
{
    for (int i=0; i < 20; ++i)
    {
		vectSpotRates.push_back(0.0);
        vectForward6mRates.push_back(0.0);
		vectDiscountFactors.push_back(0.0);
    }
}

void TermStructure::SetBonds(vector<Bond> vectBonds)
{
    this->vectBonds = vectBonds;
}

double TermStructure::GetSpotRate(int index) const
{
    return vectSpotRates[index];
}

double TermStructure::GetForward6mRate(int index) const
{
    return vectForward6mRates[index];
}

double TermStructure::GetDiscountFactor(int index) const
{
    return vectDiscountFactors[index];
}

void TermStructure::ComputeSpotRates()
{
    for (vector<Bond>::iterator iter = vectBonds.begin(); iter != vectBonds.end(); ++iter)
    {
        if (iter->GetName() == "6m")
        {
            vectSpotRates[0] = iter->ComputeYTM();
        }
        else if (iter->GetName() == "1y")
        {
            iter->BootstrappingSpotRate(vectSpotRates, 20, 0, 1);
        }
        else if (iter->GetName() == "2y")
        {
            iter->BootstrappingSpotRate(vectSpotRates, 20, 1, 3);
        }
        else if (iter->GetName() == "3y")
        {
            iter->BootstrappingSpotRate(vectSpotRates, 20, 3, 5);
        }
        else if (iter->GetName() == "5y")
        {
            iter->BootstrappingSpotRate(vectSpotRates, 20, 5, 9);
        }
        else if (iter->GetName() == "7y")
        {
            iter->BootstrappingSpotRate(vectSpotRates, 20, 9, 13);
        }
        else if (iter->GetName() == "10y")
        {
            iter->BootstrappingSpotRate(vectSpotRates, 20, 13, 19);
        }
    }
}

void TermStructure::ComputeDiscountFactors()
{
    for (int i = 0; i < vectSpotRates.size(); ++i)
    {
        vectDiscountFactors[i] = pow(1.0 + vectSpotRates[i]/100.0/2.0, -(i+1)/2.0);
    }
}

void TermStructure::ComputeForward6mRates()
{
    for (int i = 0; i < vectSpotRates.size()-1; ++i)
    {
        vectForward6mRates[i] = (pow((pow(1.0 + vectSpotRates[i+1]/100.0/2.0, (i+2)/2.0)/
			pow(1.0 + vectSpotRates[i]/100.0/2.0, (i+1)/2.0)), 1.0/0.5) - 1.0) * 100.0 * 2.0;
	}
}
