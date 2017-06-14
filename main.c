#include "sparse_matrix.h"
#include <stdlib.h>
#include <stdio.h>

#define M 4
#define N 6

int main(int argc, char *argv[]) {
    // const double _mmat[N][N] = {
    //     {0, 0, 0, 0},
    //     {5, 8, 0, 0},
    //     {0, 0, 3, 0},
    //     {0, 6, 0, 0}
    // };


    // const double _mmat[N][N] = {
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 7}
    // };
    
    const double _mmat[M][N] = {
        {10, 20, 0, 0, 0, 0},
        {0, 30, 0, 40, 0, 0},
        {0, 0, 50, 60, 70, 0},
        {0, 0, 0, 0, 0, 80}
    };

    double **mmat = malloc(sizeof(double*) * N);
    for (size_t i = 0; i < N; ++i) {
        mmat[i] = malloc(sizeof(double) * N);
    }

    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            mmat[i][j] = _mmat[i][j];
        }
    }


    sp_mat_ref sp_mat = sp_mat_create(mmat, M, N);


    for (size_t i = 0; i < N; ++i) {
        free(mmat[i]);
    }
    free(mmat);

    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
           printf("%.1f ", sp_mat_get_value(sp_mat, i, j));
        }

        printf("\n");
    }
    
    sp_mat_free(sp_mat);


    return 0;
}
