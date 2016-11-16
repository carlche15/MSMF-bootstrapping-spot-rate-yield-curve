#include <iostream>
#include <iomanip>
#include <vector>
#include<fstream>
#include "TermStructure.h"
#include "Bond.h"

using namespace std;

int main()
{
    vector<Bond> vectBonds;
	ifstream infile;
	bool controler=true;
	vector<double> datas;
	infile.open("yields.txt");
	double readFromInfile;
	while (controler)
	{
		infile >> readFromInfile;
		if (infile)
		{
			datas.push_back(readFromInfile);
		}
		else
		{
			controler=false;
			if (infile.eof())
			{
				cout << endl;
				cout<< "data input is completed! :)" << endl;
			}
			else
				cout << "Wrong File :(  " << endl;
		}
	}
	vector<double>::iterator it = datas.begin();
    string name = "6m";
    double coupon = (*it);
    long issueDate =*(++it);
	long maturityDate = *(++it);
	int compoundingFrequencyPerAnnum = *(++it);
	double price = *(++it);;
    Bond* bond = new Bond(name, coupon, issueDate, maturityDate, compoundingFrequencyPerAnnum);
    bond->SetPrice(price);
    vectBonds.push_back(*bond);

    // 1y bond
    //
    name = "1y";
	coupon = *(++it);
	issueDate = *(++it);
	maturityDate = *(++it);
	compoundingFrequencyPerAnnum = *(++it);;
	price = *(++it);

    bond = new Bond(name, coupon, issueDate, maturityDate, compoundingFrequencyPerAnnum);
    bond->SetPrice(price);
    vectBonds.push_back(*bond);

    // 2y bond
    //
    name = "2y";
	coupon = *(++it);
	issueDate = *(++it);
	maturityDate = *(++it);
	compoundingFrequencyPerAnnum = *(++it);
	price = *(++it);

    bond = new Bond(name, coupon, issueDate, maturityDate, compoundingFrequencyPerAnnum);
    bond->SetPrice(price);
    vectBonds.push_back(*bond);

    // 3y bond
    //
    name = "3y";
	coupon = *(++it);
	issueDate = *(++it);
	maturityDate = *(++it);
	compoundingFrequencyPerAnnum = *(++it);
	price = *(++it);

    bond = new Bond(name, coupon, issueDate, maturityDate, compoundingFrequencyPerAnnum);
    bond->SetPrice(price);
    vectBonds.push_back(*bond);

    // 5y bond
    //
    name = "5y";
	coupon = *(++it);
	issueDate = *(++it);
	maturityDate = *(++it);
	compoundingFrequencyPerAnnum = *(++it);
	price = *(++it);

    bond = new Bond(name, coupon, issueDate, maturityDate, compoundingFrequencyPerAnnum);
    bond->SetPrice(price);
    vectBonds.push_back(*bond);

    // 7y bond
    //
    name = "7y";
	coupon = *(++it);
	issueDate = *(++it);
	maturityDate = *(++it);
	compoundingFrequencyPerAnnum = *(++it);
	price = *(++it);

    bond = new Bond(name, coupon, issueDate, maturityDate, compoundingFrequencyPerAnnum);
    bond->SetPrice(price);
    vectBonds.push_back(*bond);

    // 10y bond
    //
    name = "10y";
	coupon = *(++it);
	issueDate = *(++it);
	maturityDate = *(++it);
	compoundingFrequencyPerAnnum = *(++it);
	price = *(++it);

    bond = new Bond(name, coupon, issueDate, maturityDate, compoundingFrequencyPerAnnum);
    bond->SetPrice(price);
    vectBonds.push_back(*bond);

    // term structure
    //
    TermStructure* termStructure = new TermStructure();
    termStructure->SetBonds(vectBonds);
    termStructure->ComputeSpotRates();
    termStructure->ComputeDiscountFactors();
    termStructure->ComputeForward6mRates();

    static string TENORS[20] = {"6m", "1y", "18m", "2y", "2.5y", "3y", "3.5y", "4y", "4.5y", "5y",
                                "5.5y", "6y", "6.5y", "7y", "7.5y", "8y", "8.5y", "9y", "9.5y", "10y"};

	cout << "Tenor" << "\t" << setw(10) << "Spot(%)" << "\t" << setw(10) << "DF(%)" << "\t" << setw(10) << "6mFwd(%)" << endl;
    for (int i = 0; i < 20; ++i)
    {
        cout << TENORS[i] 
			<< "\t" << fixed << setw(10) << setprecision(5) << termStructure->GetSpotRate(i) 
			<< "\t" << fixed << setw(10) << setprecision(5) << termStructure->GetDiscountFactor(i)
			<< "\t" << fixed << setw(10) << setprecision(5) << termStructure->GetForward6mRate(i)
			<< endl;
    }

    return 0;
}

