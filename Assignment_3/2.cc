#include <iostream>
#include <cmath>
#include <fftw3.h>
#include <vector>

int main() {
    const int N = 100; // Number of samples so that the results match with the earlier result
    double dx = 0.1; // Sampling interval so that the results match with the earlier result
    double *in; // Input array
    fftw_complex *out; // Output array
    fftw_plan plan;

    // Allocate memory for input and output arrays
    in = (double*) fftw_malloc(sizeof(double) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    // Generate input data
    for (int i = 0; i < N; i++) {
        double x = (i - N / 2) * dx; // Centering the input data
        if (x == 0) {
            in[i] = 1.0;
        } else {
            in[i] = std::sin(x) / x;
        }
    }

    // Create FFTW plan
    plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

    // Perform Fourier transform
    fftw_execute(plan);

    // Create vectors to store frequencies and amplitudes
    std::vector<double> frequencies;
    std::vector<double> amplitudes;

    // Calculate and store the results
    for (int i = 0; i < N; i++) {
        double freq = i / (N * dx);
        double amp = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        frequencies.push_back(freq);
        amplitudes.push_back(amp);
    }

    // Print the arrays
    std::cout << "Frequencies: ";
    for (double freq : frequencies) {
        std::cout << freq << " ";
    }
    std::cout << std::endl;

    std::cout << "Amplitudes: ";
    for (double amp : amplitudes) {
        std::cout << amp << " ";
    }
    std::cout << std::endl;

    // Clean up
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return 0;
}
