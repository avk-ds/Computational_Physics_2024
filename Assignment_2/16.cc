#include <iostream>
#include <cmath>

using namespace std;

// Function to compute the derivative y'(t)
double derivative(double t, double y) {
    return y - t * t + 1;
}

// Function to compute the exact solution y(t)
double exact_solution(double t) {
    return (t + 1) * (t + 1) - 0.5 * exp(t);
}

int main() {
    double t0 = 0;            // Initial value of t
    double y0 = 0.5;          // Initial value of y(t0)
    double tf = 2;            // Final value of t
    double h = 0.2;           // Step size
    double L = 1;             // Constant L
    double M = 1.69;         // Constant M

    // Compute the number of steps
    int num_steps = (tf - t0) / h;

    // Initialize variables
    double t = t0;
    double y = y0;
    double z;

    // Compute the solution using Euler's method
    for (int i = 0; i < num_steps; ++i) {
        // Compute the derivative at current (t, y)
        double dydt = derivative(t, y);

        // Compute the next value of y using Euler's method
        y = y + h * dydt;

        // Compute the exact solution at current t
        double y_exact = exact_solution(t);

        // Compute the error
        double error = fabs(y_exact - y);

        // Compute z at current step
        z = (h * M / (2 * L)) * (exp(t * L) - 1);

        // Output the results
        cout << "t = " << t << ", y = " << y << ", exact y = " << y_exact << ", error = " << error << ", z = " << z << endl;

        // Increment t for the next step
        t += h;
    }

    return 0;
}

