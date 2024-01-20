// assignment1.cpp

#include <iostream>
#include <iomanip>	// Required to set precision of cout apparently
#include <string>
#include <vector>
#include <cmath>	// Need Pi and trig.
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

// Calculate range by driving RK4 with constant step size. It would be
// nice to use adaptive step size, but I don't want to work that hard.
double get_range(const double v, const double th, const double dt)
{
	const double g=9.8;
	double t=0.0;
	vector<double> y = {0.0, 0.0};	// x(t) and y(t)
	vector<double> dydx = {0.0, 0.0};	// dxdt and dydt
	
	// Initialize derivatives
	derivs(t, y, dydx, v, g, th);
	
	// Take RK4 steps until we're on the ground again
	do{
		// Take a Runge-Kutta 4 step
		rk4(y, dydx, t, dt, y, v, g, th, derivs);
		// Update time
		t += dt;
		// Update derivatives
		derivs(t, y, dydx, v, g, th);
	} while (y[1] >= 0.0);
	
	// Take a linear backstep because we always overshoot by a bit.
	return (y[0] - y[1]/dydx[1]*dydx[0]);
}

// Dump results to the console.
void dump(const double x, const double th, const double v)
{
	const double g=9.8;
	
	cout << "Theoretical best angle: 45 deg.\n";
	cout << "Calculated best angle: " << th << " deg.\n";
	cout << setprecision(15) << "Theoretical range: " << v*v*sin(M_PI_2)/g <<" m.\n";
	cout << "Calculated range: " << x << " m.\n";
}

// Convert degrees to radians
double deg2rad(double var)
{
	return var * M_PI / 180.0;
}

// Converts radians to degrees
double rad2deg(double var)
{
	return var * 180.0 / M_PI;
}

int main()
{
	// Time step size seems to be the precision limiting factor. That
	// sucks, but I already got RK4 working, and I don't want to redo it.
	const double dt=0.0001;	// Time step size. Keep <= 0.001.
	const double R=0.618, C=1.-R;	// Golden ratio
	double tol=1.0E-7;	// Error tolerance for angle. (In radians)
	double x1, x2, xmax;	// Ranges
	double th0=0.0, th1=20.0, th2, th3=90.0, thmax;	// Angles
	double v;	// Velocity
	
	// Get velocity from user
	v = get_double("Please enter an initial velocity (0<v<c): ", 0.0, 3.0E8);
	
	// Convert starting angles to radians
	th0 = deg2rad(th0);	th1 = deg2rad(th1); th3 = deg2rad(th3);
	
	// Figure out which pair is closer so we get the order correct.
	if (abs(th3-th1) > abs(th0-th1)) {
		th2 = th1 + C*(th3-th1);
	} else {
		th2 = th1;
		th1 = th2 - C*(th2-th1);
	}
	// Initialize max ranges
	x1 = get_range(v, th1, dt);
	x2 = get_range(v, th2, dt);
	
	// Perform bracket search
	// Keep doing the search until we're within some tolerance.
	while (abs(th3-th0) > tol*(abs(th1)+abs(th2))){
	// Tightening the bracket and updating Ranges. Stare at drawing or
	// check Numerical Recipes to see why this makes sense.
		if (x2 > x1){
			th0 = th1;
			th1 = th2;
			x1 = x2;
			th2 = R*th1 + C*th3;
			x2 = get_range(v, th2, dt);
		} else {
			th3 = th2;
			th2 = th1;
			x2 = x1;
			th1 = C*th0 + R*th2;
			x1 = get_range(v, th1, dt);
		}
	}
	// Pick best result
	if (x1 > x2) {
		xmax = x1;
		thmax = rad2deg(th1);
	} else {
		xmax = x2;
		thmax = rad2deg(th2);
	}
	
	// Dump results to console
	dump(xmax, thmax, v);
}
