#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#define N 200
#define XLIMIT 50

double sinc_func(double x) {
    if (x == 0.0){
        return 1.0;
    } else {
        return sin(x)/x;
    }
}

int main() {
    double delta = (double) 2 * XLIMIT / (N - 1);

    fftw_complex input[N], output[N];
    fftw_plan plan;
    
    for (int i=0; i < N; i++) {
        input[i] = sinc_func(-XLIMIT + i * delta) + I * 0.0;
    }

    plan = fftw_plan_dft_1d(N, input, output, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);

    FILE *file = fopen("transformed_data.csv","w");

    for (int i = 0; i < N; i++) {
        fprintf(file, "%g, %g\n", creal(output[i]), cimag(output[i]));
    }

    fclose(file);

    fftw_destroy_plan(plan);
    fftw_cleanup();

    printf("Fourier transform data has been written to 'transformed_data.csv'.\n");

    return 0;
}
