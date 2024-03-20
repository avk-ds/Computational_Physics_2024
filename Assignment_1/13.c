#include <stdio.h>
#include <gsl/gsl_linalg.h>

int main() {
    // Define the matrix dimensions
    const int N = 3;

    // Define the original matrix
    double matrix_data[N][N] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    // Initialize GSL matrix and vector views
    gsl_matrix_view mat = gsl_matrix_view_array(&matrix_data[0][0], N, N);

    // Perform LU decomposition
    gsl_permutation *p = gsl_permutation_alloc(N);
    int signum;
    gsl_linalg_LU_decomp(&mat.matrix, p, &signum);

    // Reconstruct the original matrix from LU factors
    gsl_matrix *L = gsl_matrix_alloc(N, N);
    gsl_matrix *U = gsl_matrix_alloc(N, N);
    gsl_matrix_memcpy(L, &mat.matrix);
    gsl_matrix_memcpy(U, &mat.matrix);
    gsl_linalg_LU_decomp(&mat.matrix, p, &signum);
    gsl_matrix_set_identity(L); // Set L to an identity matrix
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i > j) {
                gsl_matrix_set(U, i, j, 0.0); // Zero out lower triangular part for U
            } else if (i == j) {
                gsl_matrix_set(L, i, j, 1.0); // Set diagonal of L to 1
            } else {
                gsl_matrix_set(L, i, j, gsl_matrix_get(&mat.matrix, i, j)); // Copy values for lower triangular part from original matrix
            }
        }
    }

    // Output the original matrix
    printf("Original Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.3f ", matrix_data[i][j]);
        }
        printf("\n");
    }

    // Output the reconstructed matrix
    printf("\nReconstructed Matrix (L*U):\n");
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, L, U, 0.0, &mat.matrix);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.3f ", gsl_matrix_get(&mat.matrix, i, j));
        }
        printf("\n");
    }

    // Free memory
    gsl_permutation_free(p);
    gsl_matrix_free(L);
    gsl_matrix_free(U);

    return 0;
}

