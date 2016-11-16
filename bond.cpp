#include"bond.h"
#include<iostream>
#include<math.h>
using namespace std;
bond::bond(double bp, double fv, double cp, double cf, double pn)
{   
	bondprice = bp * 10;
	facevalue = fv;
	coupon = cp / 100.0 / cf;
	cfrequency = cf;
	paymentnum = pn;
}
double bond::expression_value(double ytm_tester)
{
	double bondvalue = 0;
	double den = 1.0 + ytm_tester / cfrequency;
	for (int i = 0; i <paymentnum; i++)
	{
		bondvalue += coupon*facevalue / pow(den, i + 1);
	}
	bondvalue += facevalue / pow(den, paymentnum);
	double expression = (bondvalue - bondprice);
	return expression;
}
double bond::derivative(double root_tester)
{
	double expression_increase = expression_value(root_tester + mini) - expression_value(root_tester);
	double root_increase = mini;
	double deriv = expression_increase / root_increase;
	return deriv;
}
int  bond::check(double a, double b){
	double m = abs(a - b);
	if (m <= epsi)
		return 1;
	else
		return 0;

}
void bond::vtmcalculator()
{
	while (1)
	{
		ytm = ytm0 - expression_value(ytm0) / derivative(ytm0);
		if (check(ytm, ytm0))
			break;
		ytm0 = ytm;
	}
}
void bond::vtmcalculator2(){
	while (1)
	{
		ytm = ytm0 - expression_value(ytm0) / derivative(ytm0);
		if (check(ytm, ytm0))
			break;
		ytm0 = ytm;
	}
}
double bond::get_vtm()
{
	return ytm;
}
double bond::get_vtm2()
{
	return ytm;
}
void bond::set_parameters(){
	cout << "in put three numbers accordingly  for mini, epsi, ytm0(starting point)!" << endl;
	cin >> mini >> epsi >> ytm0;
}