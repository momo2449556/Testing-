#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const double g  = 9.81;
const double PI = 3.14159265358979323846;

double l;   // pendulum length

// Angular accelerations for equal masses and equal lengths
double a1(double th1, double w1, double th2, double w2) {
    double delta = th1 - th2;
    double denom = 2.0 - cos(2.0 * delta);

    return (
        -g * (2.0 * sin(th1) + sin(th1 - 2.0 * th2))
        - 2.0 * sin(delta) * (w2 * w2 + w1 * w1 * cos(delta))
    ) / (l * denom);
}

double a2(double th1, double w1, double th2, double w2) {
    double delta = th1 - th2;
    double denom = 2.0 - cos(2.0 * delta);

    return (
        2.0 * sin(delta) * (
            2.0 * w1 * w1
            + 2.0 * g * cos(th1)
            + w2 * w2 * cos(delta)
        )
    ) / (l * denom);
}

// One RK4 integration step
void rk4_step(double &theta1, double &w1,
              double &theta2, double &w2,
              double h)
{
    // k1
    double k1_th1 = w1;
    double k1_w1  = a1(theta1, w1, theta2, w2);
    double k1_th2 = w2;
    double k1_w2  = a2(theta1, w1, theta2, w2);

    // k2
    double th1_2 = theta1 + 0.5 * h * k1_th1;
    double w1_2  = w1     + 0.5 * h * k1_w1;
    double th2_2 = theta2 + 0.5 * h * k1_th2;
    double w2_2  = w2     + 0.5 * h * k1_w2;

    double k2_th1 = w1_2;
    double k2_w1  = a1(th1_2, w1_2, th2_2, w2_2);
    double k2_th2 = w2_2;
    double k2_w2  = a2(th1_2, w1_2, th2_2, w2_2);

    // k3
    double th1_3 = theta1 + 0.5 * h * k2_th1;
    double w1_3  = w1     + 0.5 * h * k2_w1;
    double th2_3 = theta2 + 0.5 * h * k2_th2;
    double w2_3  = w2     + 0.5 * h * k2_w2;

    double k3_th1 = w1_3;
    double k3_w1  = a1(th1_3, w1_3, th2_3, w2_3);
    double k3_th2 = w2_3;
    double k3_w2  = a2(th1_3, w1_3, th2_3, w2_3);

    // k4
    double th1_4 = theta1 + h * k3_th1;
    double w1_4  = w1     + h * k3_w1;
    double th2_4 = theta2 + h * k3_th2;
    double w2_4  = w2     + h * k3_w2;

    double k4_th1 = w1_4;
    double k4_w1  = a1(th1_4, w1_4, th2_4, w2_4);
    double k4_th2 = w2_4;
    double k4_w2  = a2(th1_4, w1_4, th2_4, w2_4);

    // Update state
    theta1 += h / 6.0 * (k1_th1 + 2.0*k2_th1 + 2.0*k3_th1 + k4_th1);
    w1     += h / 6.0 * (k1_w1  + 2.0*k2_w1  + 2.0*k3_w1  + k4_w1);
    theta2 += h / 6.0 * (k1_th2 + 2.0*k2_th2 + 2.0*k3_th2 + k4_th2);
    w2     += h / 6.0 * (k1_w2  + 2.0*k2_w2  + 2.0*k3_w2  + k4_w2);
}

int main() {
    const double h = 0.001;  // smaller step = better stability
    double t = 0.0, tf;
    double theta1, theta2, w1, w2;
    double x1, y1, x2, y2;

    cout << "Enter pendulum length (m): ";
    cin >> l;

    cout << "Enter final time tf (s): ";
    cin >> tf;

    cout << "Enter initial conditions (deg): theta1 w1 theta2 w2: ";
    cin >> theta1 >> w1 >> theta2 >> w2;

    // Convert degrees to radians
    theta1 *= PI / 180.0;
    theta2 *= PI / 180.0;

    ofstream myfile("C:/Users/Mohammed/Testing-/CP.DAT");
    myfile << setprecision(16);

    if (!myfile) {
        cerr << "Error opening output file.\n";
        return 1;
    }

    while (t <= tf) {
        x1 =  l * sin(theta1);
        y1 = -l * cos(theta1);
        x2 = x1 + l * sin(theta2);
        y2 = y1 - l * cos(theta2);

        myfile << t << " "
             << x1 << " " << y1 << " "
             << x2 << " " << y2 << "\n";

        rk4_step(theta1, w1, theta2, w2, h);
        t += h;
    }

    myfile.close();
    return 0;
}
