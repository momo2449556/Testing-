#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

const double PI = 3.1415926535897932;
const double g = 9.81;

int main(){

    double l, x, y, vx, vy, t, t0, tf, dt;
    double theta, theta0, theta_dot, omega;
    string buf;


    cout << "Enter the length, l\n";
    cin >> l;       getline(cin,buf);

    cout << "Enter theta(0)\n";
    cin >> theta0;           getline(cin, buf);

    cout << "Enter t0, tf, and dt:\n";

    cin >> t0 >> tf >> dt;  getline(cin,buf);

    cout << "# Theta(0) = " << theta0 << " l =" << l << endl;
    cout << "# t0 =" << t0 << " tf = " << tf << " dt = " << dt 
        << " theta0 =" << theta0 << endl;

omega = sqrt (g/l);
    ofstream myfile("C:/Users/Mohammed/Testing-/SP.DAT");
if (!myfile.is_open()) {
    cerr << "Error: Could not open file for writing!\n";
    return 1; // Exit program
}

t = t0;
while(t <= tf){
    theta = theta0 * cos(omega*(t-t0));
    theta_dot = -omega *sin(omega*(t-t0));
    x = l*sin(theta);
    y= -l*cos(theta);
    vx = l*theta_dot*cos(theta);
    vy = -l*theta_dot*sin(theta);


    myfile << t << " " << x << " " << y << " " << vx << " "
            << vy << " " << theta << " " << theta_dot << endl;


    t = t + dt;
}
}