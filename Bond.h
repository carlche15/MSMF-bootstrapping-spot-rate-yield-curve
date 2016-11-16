#ifndef BOND_H
#define BOND_H

#include <string>
#include <vector>

using namespace std;

class Bond
{
    public:
        Bond(string name, double coupon, long issueDate, long maturityDate, int compoundingFrequencyPerAnnum);
        void SetPrice(double price, double faceValue);
        void SetPrice(double price);
        double ComputeYTM();

        string GetName() const;

        double ComputePrice(double faceValue, double coupon, double ytm, int numberOfCouponPayments);
        double ComputePrice(double faceValue, double coupon, vector<double> vectSpotRates, int spotRatesLength, int numberOfCouponPayments);
        double BootstrappingSpotRate(vector<double>& vectSpotRates, int spotRatesLength, int interpolatedTenorStart, int interpolatedTenorEnd);

    private:
        string name;
        double coupon;
        long issueDate;
        long maturityDate;
        int compoundingFrequencyPerAnnum;
        int numberOfCouponPayments;

        double price;
        double faceValue;
};

#endif // BOND_H
