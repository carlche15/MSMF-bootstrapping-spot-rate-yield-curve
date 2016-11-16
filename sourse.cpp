#include<iostream>
#include<math.h>
#include"bond.h"
using namespace std;
int main()
{
	double bondprice = 101.255;
	double facevalue = 1000.0;
	double coupon = 8.0+5.0/8.0;
	int cfrequency = 2;
	int paymentnum = cfrequency*(2031-1997);
	cout << "\t" << "\t" << "YTM of AT&T Bond" << endl;
	cout << "Bond Price: " << bondprice<<endl;
	cout << "Face Value: " << facevalue << endl;
	cout << "Coupon Rate: " << coupon<<endl;
	cout << "Duration(Years): " << paymentnum / cfrequency<<endl;
	cout << "Semi Compond" << endl;
	bond att(bondprice, facevalue, coupon, cfrequency, paymentnum);
	att.vtmcalculator();
	cout << " YTM is " << att.get_vtm() * 100 << "% " << endl;
	att.vtmcalculator2();
	cout << "the result of the other method is presented below¡G"<<endl<< att.get_vtm2() * 100 << "% ";
}