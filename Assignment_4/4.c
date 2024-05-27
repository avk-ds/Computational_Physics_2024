#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double generate_exponential(double lambda) {
    double uniform_random = ((double) rand() / (RAND_MAX));
    return -log(1 - uniform_random) / lambda;
}

int main() {
    const int num_samples = 10000;
    const double rate_parameter = 2.0;
    double samples[num_samples];

    srand((unsigned) time(NULL));
    for (int index = 0; index < num_samples; ++index) {
        samples[index] = generate_exponential(rate_parameter);
    }

    FILE *output_file = fopen("exponential_distribution.txt", "w");
    if (output_file == NULL) {
        perror("Unable to open file for writing");
        return 1;
    }

    for (int index = 0; index < num_samples; ++index) {
        fprintf(output_file, "%f\n", samples[index]);
    }

    fclose(output_file);

    return 0;
}
