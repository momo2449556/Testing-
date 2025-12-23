#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

const double PI =  3.1415926535897932;

int main(){

    double x, y, vx, vy, A, t, tf, dt;
    double w1, w2;
    string buf;


    cout << "Enter value of omegas (w1, and w2)\n";
    cin >> w1 >> w2; getline(cin,buf);

    cout << "Enter value of A\n";
    cin >> A; getline(cin,buf);

    cout << "enter value of final time and dt\n";
    cin >> tf >> dt; getline(cin, buf);

    cout << "# w1= " << w1 << " w2= " << w2 << " A= " << A << endl;
    cout << "# tf= " << tf << " dt= " << dt << endl;

ofstream myfile("C:/Users/Mohammed/Testing-/Lissajoux.DAT");
myfile.precision(17);


t = 0.0;
while(t <= tf ){

    x = A*cos(w1*t);
    y = A*sin(w2*t);
    vx = -w1*A*sin(w1*t);
    vy = w2*A*cos(w2*t);

    myfile << t << " " << x << " " << y << " " << vx << " " << vy << endl;
   




    t = t + dt;
}

}