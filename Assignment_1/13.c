#include <stdio.h>
#include <gsl/gsl_linalg.h>

void lu_decomposition(double A[], int size, double L[], double U[]) {
    gsl_matrix_view gsl_A = gsl_matrix_view_array(A, size, size);
    gsl_permutation *p = gsl_permutation_alloc(size);
    int signum;

    gsl_linalg_LU_decomp(&gsl_A.matrix, p, &signum);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i > j)
                L[i * size + j] = gsl_matrix_get(&gsl_A.matrix, i, j);
            else if (i == j)
                L[i * size + j] = 1.0;
            else
                L[i * size + j] = 0.0;

            if (i <= j)
                U[i * size + j] = gsl_matrix_get(&gsl_A.matrix, i, j);
            else
                U[i * size + j] = 0.0;
        }
    }

    gsl_permutation_free(p);
}

int main() {
    // Example matrices
    double A1[] = {3, -1, 1, 3, 6, 2, 3, 3, 7};
    double A2[] = {10, -1, 0, -1, 10, -2, 0, -2, 10};
    double A3[] = {10, 5, 0, 0, 5, 10, -4, 0, 0, -4, 8, -1, 0, 0, -1, 5};
    double A4[] = {4, 1, 1, 0, 1, -1, -3, 1, 1, 0, 2, 1, 5, -1, -1, -1, -1, 4, 0, 0, 2, -1, 1, 4};
    int sizes[] = {3, 3, 4, 5};

    for (int k = 0; k < 4; k++) {
        int size = sizes[k];
        double *A;
        switch (k) {
            case 0:
                A = A1;
                break;
            case 1:
                A = A2;
                break;
            case 2:
                A = A3;
                break;
            case 3:
                A = A4;
                break;
            default:
                continue;
        }

        // Allocate space for L and U matrices
        double L[size * size];
        double U[size * size];

        // Perform LU decomposition
        lu_decomposition(A, size, L, U);

        // Print the results
        printf("Matrix A%d:\n", k + 1);
        printf("Matrix L:\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%8.5f ", L[i * size + j]);
            }
            printf("\n");
        }

        printf("\nMatrix U:\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%8.5f ", U[i * size + j]);
            }
            printf("\n");
        }

        // Reconstruct the original matrix A
        double A_reconstructed[size * size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double sum = 0.0;
                for (int k = 0; k < size; k++) {
                    sum += L[i * size + k] * U[k * size + j];
                }
                A_reconstructed[i * size + j] = sum;
            }
        }

        // Print the reconstructed matrix A
        printf("\nReconstructed Matrix A%d:\n", k + 1);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%8.5f ", A_reconstructed[i * size + j]);
            }
            printf("\n");
        }

        // Verify the correctness of LU decomposition
        int correct = 1;
        for (int i = 0; i < size * size; i++) {
            if (A[i] != A_reconstructed[i]) {
                correct = 0;
                break;
            }
        }

        if (correct)
            printf("\nLU decomposition is correct for Matrix A%d.\n", k + 1);
        else
            printf("\nLU decomposition is incorrect for Matrix A%d.\n", k + 1);

        printf("-------------------------------------------------------\n");
    }

    return 0;
}

