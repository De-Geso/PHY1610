// assignment1.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


// Simple command line input as shown in class.
string get_word(const string& prompt)
{
	string result;
	cout << prompt;
	cin >> result;
	return result;
}

// Get a double precision number between two values. 3 Tries to get it.
double get_double(const string& prompt, double min, double max)
{
	int i=3; double val;
	while(i > 0){
		string word = get_word(prompt);
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
void derivs(const double x, const vector<double> &y, vector<double> &dydx,
	const double v, const double g, const double th)
{	
	dydx[0] = v*cos(th);
	dydx[1] = v*sin(th) - g*x;
}

// Runge-Kutta 4 stepper adapted from Numerical Recipes.
void rk4(const vector<double> &y, const vector<double> &dydx,
	const double x, const double h, vector<double> &yout,
	const double v, const double g, const double th,
	void derivs(const double, const vector<double> &, vector<double> &, 
		const double, const double, const double))
{
	int n=y.size();
	vector<double> dym(n), dyt(n), yt(n);
	double hh = h*0.5;
	double h6 = h/6.0;
	double xh = x+hh;
	
	for (int i=0; i<n; i++) yt[i] = y[i] + hh*dydx[i];	// First step
	derivs(xh, yt, dyt, v, g, th);
	for (int i=0; i<n; i++)	yt[i] = y[i] + hh*dyt[i];	// Second step
	derivs(xh, yt, dym, v, g, th);
	for (int i=0; i<n; i++){	// Third step
		yt[i] = y[i] + h*dym[i];
		dym[i] += dyt[i];
	}
	derivs(x+h, yt, dyt, v, g, th);	// Fourth step
	for (int i=0; i<n; i++)
		yout[i] = y[i] + h6*(dydx[i]+dyt[i]+2.0*dym[i]);
}

// Runge-Kutta 4 driver.
void rk4_dumb()
{
}

// Dump all our information to the console.
void dump(const vector<double> y, const double v, const double g,
	const double th)
{
	cout << "Theoretical best angle: 45 deg.\n";
	cout << "Theoretical range: " << v*v*sin(2.0*th)/g << " m.\n";
	cout << "Calculated range: " << y[0] << " m.\n";
}

int main()
{
	const double dt=0.00001;
	const double g=9.8;
	double v;
	double t=0.0;
	vector<double> y = {0.0, 0.0};
	vector<double> dydx = {0.0, 0.0};
	double th=M_PI_4;
	
	// Get the velocity.
	v = get_double("Please enter an initial velocity (0<v<c): ", 0.0, 3.0E8);
	
	// Initialize derivatives
	derivs(t, y, dydx, v, g, th);
	
	do{
		// Take a Runge-Kutta 4 step
		rk4(y, dydx, t, dt, y, v, g, th, derivs);
		// Update time
		t += dt;
		// Update derivatives
		derivs(t, y, dydx, v, g, th);
	} while (y[1] >= 0.0);
	derivs(t, y, dydx, v, g, th);
	cout << t << " " << y[1] << " " << dydx[1] << "\n";
	
	dump(y, v, g, th);
}

