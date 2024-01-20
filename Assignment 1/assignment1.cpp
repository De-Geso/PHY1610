// assignment1.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


// Simple command line input as shown in class.
string getword(const string& prompt)
{
	string result;
	cout << prompt;
	cin >> result;
	return result;
}


// Get a double precision number between two values. 3 Tries to get it.
double getdouble(const string& prompt, double min, double max)
{
	int i=3; double val;
	while(i > 0){
		string word = getword(prompt);
		try{
			val = stod(word);
			if (val > min and val < max)
				return val;
			else 
				i = i-1;
				cout << "Error: value out of bounds, (" << i << " attempts remaining)\n";
		} catch(invalid_argument& e){
			i = i-1;
			cout << "Error: invalid input, (" << i << " attempts remaining)\n";
			if (cin.eof()) return -1;
		}
	}
	cout << "Aborting program.\n";
	return -1;
}


// Derivatives of x(t), and y(t)
void derivs(const double t, const vector<double> y, vector<double> dydt,
	const double v, const double g, const double th)
{	
	dydt[0] = v*cos(th);
	dydt[1] = v*sin(th) - g*t;
}


void rk4(const double t, vector<double> y, const double dt,
	const double v, const double g, const double th)
{
	vector<double> dydt
	derivs(t, y, dydt, v, g, th);
}


int main()
{
	double v;
	const double g=9.8;
	double t=0.0;
	double th=M_PI_4;
	vector<double> y = {0.0, 0.0};
	vector<double> dydt = {0.0, 0.0};
	
	v = getdouble("Please enter an initial velocity (0<v<c): ", 0.0, 3.0E8);
	
	derivs(t, y, dydt, v, g, th);
}

