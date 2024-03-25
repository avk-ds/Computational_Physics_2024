#include <stdio.h>
#include <gsl/gsl_linalg.h>

// Function to print a matrix
void print_matrix(const gsl_matrix *m) {
    for (size_t i = 0; i < m->size1; ++i) {
        for (size_t j = 0; j < m->size2; ++j) {
            printf("%10.6f ", gsl_matrix_get(m, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Define the four matrices
    double data1[] = {3, -1, 1, 3, 6, 2, 3, 3, 7};
    double data2[] = {10, -1, 0, -1, 10, -2, 0, -2, 10};
    double data3[] = {10, 5, 0, 0, 5, 10, -4, 0, 0, -4, 8, -1, 0, 0, -1, 5};
    double data4[] = {4, 1, 1, 0, 1, -1, -3, 1, 1, 0, 2, 1, 5, -1, -1, -1, -1, 4, 0, 0, 2, -1, 1, 4};

    gsl_matrix_view A1 = gsl_matrix_view_array(data1, 3, 3);
    gsl_matrix_view A2 = gsl_matrix_view_array(data2, 3, 3);
    gsl_matrix_view A3 = gsl_matrix_view_array(data3, 4, 4);
    gsl_matrix_view A4 = gsl_matrix_view_array(data4, 5, 5);

    // Perform LU decomposition for each matrix
    gsl_permutation *p1 = gsl_permutation_alloc(3);
    gsl_permutation *p2 = gsl_permutation_alloc(3);
    gsl_permutation *p3 = gsl_permutation_alloc(4);
    gsl_permutation *p4 = gsl_permutation_alloc(5);

    gsl_matrix *LU1 = gsl_matrix_alloc(3, 3);
    gsl_matrix *LU2 = gsl_matrix_alloc(3, 3);
    gsl_matrix *LU3 = gsl_matrix_alloc(4, 4);
    gsl_matrix *LU4 = gsl_matrix_alloc(5, 5);

    gsl_matrix_memcpy(LU1, &A1.matrix);
    gsl_matrix_memcpy(LU2, &A2.matrix);
    gsl_matrix_memcpy(LU3, &A3.matrix);
    gsl_matrix_memcpy(LU4, &A4.matrix);

    gsl_linalg_LU_decomp(LU1, p1, NULL);
    gsl_linalg_LU_decomp(LU2, p2, NULL);
    gsl_linalg_LU_decomp(LU3, p3, NULL);
    gsl_linalg_LU_decomp(LU4, p4, NULL);

    // Display LU decompositions
    printf("LU Decomposition of Matrix 1:\n");
    print_matrix(LU1);
    printf("Permutation Matrix of Matrix 1:\n");
    gsl_permutation_fprintf(stdout, p1, " %u");

    printf("LU Decomposition of Matrix 2:\n");
    print_matrix(LU2);
    printf("Permutation Matrix of Matrix 2:\n");
    gsl_permutation_fprintf(stdout, p2, " %u");

    printf("LU Decomposition of Matrix 3:\n");
    print_matrix(LU3);
    printf("Permutation Matrix of Matrix 3:\n");
    gsl_permutation_fprintf(stdout, p3, " %u");

    printf("LU Decomposition of Matrix 4:\n");
    print_matrix(LU4);
    printf("Permutation Matrix of Matrix 4:\n");
    gsl_permutation_fprintf(stdout, p4, " %u");

    // Free memory
    gsl_permutation_free(p1);
    gsl_permutation_free(p2);
    gsl_permutation_free(p3);
    gsl_permutation_free(p4);
    gsl_matrix_free(LU1);
    gsl_matrix_free(LU2);
    gsl_matrix_free(LU3);
    gsl_matrix_free(LU4);

    return 0;
}

