#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

#define REAL_PART(z,i) ((z)[2*(i)])
#define IMAGINARY_PART(z,i) ((z)[2*(i)+1])
#define N_POINTS 200
#define X_LIMIT 50

double sinc_function(double x) {
    if (x == 0.0) {
        return 1.0;
    } else {
        return sin(x) / x;
    }
}

int main() {
    double Delta = (double) 2 * X_LIMIT / (N_POINTS - 1);
    double data[2 * N_POINTS];

    gsl_fft_complex_wavetable *wavetable;
    gsl_fft_complex_workspace *workspace;

    for (int i = 0; i < N_POINTS; i++) {
        double x = -X_LIMIT + i * Delta;
        REAL_PART(data, i) = sinc_function(x);  // Real Part
        IMAGINARY_PART(data, i) = 0.0;          // Imaginary Part
    }

    wavetable = gsl_fft_complex_wavetable_alloc(N_POINTS);
    workspace = gsl_fft_complex_workspace_alloc(N_POINTS);

    gsl_fft_complex_forward(data, 1, N_POINTS, wavetable, workspace);

    FILE *file = fopen("transformed_data2.csv", "w");

    for (int i = 0; i < N_POINTS; i++) {
        fprintf(file, "%g, %g\n", REAL_PART(data, i), IMAGINARY_PART(data, i));
    }

    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);
    fclose(file);

    printf("Fourier transform data has been written to 'transformed_data2.csv'.\n");

    return 0;
}
