#ifndef TERMSTRUCTURE_H
#define TERMSTRUCTURE_H

#include <vector>

#include "Bond.h"

class TermStructure
{
    public:
        TermStructure();

        void SetBonds(vector<Bond> vectBonds);
        double GetSpotRate(int index) const;
        double GetForward6mRate(int index) const;
        double GetDiscountFactor(int index) const;

        void ComputeSpotRates();
        void ComputeForward6mRates();
        void ComputeDiscountFactors();

    private:
        vector<Bond> vectBonds;
        vector<double> vectSpotRates;
        vector<double> vectForward6mRates;
        vector<double> vectDiscountFactors;
};

#endif // TERMSTRUCTURE_H
