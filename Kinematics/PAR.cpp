#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

const double PI = 3.1415926535897932;
const double g = 9.81;

int main(){
    double x, y, vx, vy, t, t0, tf, dt;
    double x0, y0, v0x, v0y, v0, theta, k;
    string buf;


    cout << " Input v0, k and launch angle theta (degrees):\n";
    cin >> v0 >> k >> theta ;  getline(cin, buf);

    cout << " Input t0, tf, and dt:\n";
    cin >> t0 >> tf >> dt; getline(cin, buf);

    cout << "# tf= "<< tf << " dt = " << dt << endl;
    cout << "# theta= " << theta << " v0= " << v0 << endl;

    
     ofstream myfile("C:/Users/Mohammed/Testing-/Projectile.DAT");
if (!myfile.is_open()) {
    cerr << "Error: Could not open file for writing!\n";
    return 1; 
}

myfile.precision(17);


    x0 = 0.0;
    y0 = 0.0;
    t = 0.0;
    theta = theta * PI/180;
    v0x = v0*cos(theta);
    v0y = v0*sin(theta);

    while( t <= tf){

        x = v0x/k * (1- exp(-k*t));
        y = 1/k * (v0y + g/k) * (1 - exp(-k*t)) - g/k*t;
        vx = v0x*exp(-k*t);
        vy = (v0y+g/k)*exp(-k*t) - g/k;


        if (y < 0) break;

        myfile << t << " " << x << " " << y << " " << vx << " " << vy
         << endl;


        t += dt;
    }



}