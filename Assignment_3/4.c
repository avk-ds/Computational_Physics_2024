#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#define NUM_POINTS 1001
#define X_LIMIT 100

double gaussian_function(double x) {
    return exp(-x*x);
}

int main() {
    fftw_complex input[NUM_POINTS], output[NUM_POINTS];
    fftw_plan plan;
    double delta = (double) 2 * X_LIMIT / (NUM_POINTS - 1);

    plan = fftw_plan_dft_1d(NUM_POINTS, input, output, FFTW_FORWARD, FFTW_ESTIMATE);

    for (int i = 0; i < NUM_POINTS; i++) {
        input[i] = gaussian_function(-X_LIMIT + i * delta) + I * 0.0;
    }

    fftw_execute(plan);

    FILE *file = fopen("transformed_data3.csv","w");

    for (int i = 0; i < NUM_POINTS; i++) {
        fprintf(file, "%g, %g\n", creal(output[i]), cimag(output[i]));
    }

    fclose(file);

    fftw_destroy_plan(plan);
    fftw_cleanup();

    printf("Fourier transform data has been written to 'transformed_data3.csv'.\n");

    return 0;
}
