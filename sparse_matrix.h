#ifndef _SPARSE_MATRIX_
#define _SPARSE_MATRIX_

#include <stddef.h>
#include <stdint.h>

typedef uint32_t sp_mat_size;

typedef struct _sp_mat sp_mat_t;
typedef sp_mat_t* sp_mat_ref;

sp_mat_ref sp_mat_create(const double **src, sp_mat_size width, sp_mat_size height);
double sp_mat_get_value(sp_mat_ref _mat, sp_mat_size i, sp_mat_size j);
// sp_mat_ref sp_mat_load(FILE *src);
// void sp_mat_save(sp_mat_ref _mat, FILE *dst);
void sp_mat_free(sp_mat_ref _mat);


#endif //_SPARSE_MATRIX_
