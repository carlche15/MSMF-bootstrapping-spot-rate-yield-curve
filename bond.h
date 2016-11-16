#ifndef BOND_H
#define BOND_H
class bond
{
public:
	bond();
	bond(double bp, double fv, double cp, double cf, double pn);
	double expression_value(double ytm_tester);
	double derivative(double root_tester);
	int check(double a, double b);
	void vtmcalculator();
	void vtmcalculator2();
	double get_vtm();
	double get_vtm2();
	void set_parameters();
	
private:
	double bondprice;
	double facevalue;
	double coupon;
	double cfrequency;
	double paymentnum;
	double mini = 0.0000000001;
	double epsi = 0.0000001;
	double ytm0 = 0.259;
	double ytm;
};
#endif
