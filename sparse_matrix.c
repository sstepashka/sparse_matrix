#include "sparse_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _metrics {
    sp_mat_size values_count;
    sp_mat_size width;
    sp_mat_size height;
} metrics_t;

typedef metrics_t* metrics_ref;

struct _sp_mat {
    double* values;
    sp_mat_size* i_values;
    sp_mat_size* j_values;
    metrics_ref metrics;
};


sp_mat_ref sp_mat_create(const double **src, sp_mat_size height, sp_mat_size width) {
    assert(src != NULL);
    assert(height > 0);
    assert(width > 0);

    sp_mat_ref mat = malloc(sizeof(sp_mat_t));
    mat->metrics = malloc(sizeof(metrics_t));
    mat->metrics->width = width;
    mat->metrics->height = height;

    sp_mat_size non_zero_count = 0;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            double value = src[i][j];
            if (value > 0.0) {
                ++ non_zero_count;
            }
        }
    }

    mat->metrics->values_count = non_zero_count;

    mat->values = malloc(sizeof(double) * non_zero_count);
    sp_mat_size* i_values = malloc(sizeof(sp_mat_size) * height + 1);
    i_values[0] = 0;
    sp_mat_size* j_values = malloc(sizeof(sp_mat_size) * non_zero_count);

    sp_mat_size value_index = 0;
    for (sp_mat_size i = 0; i < height; ++i) {
        sp_mat_size non_zero_in_row = 0;
        for (sp_mat_size j = 0; j < width; ++j) {
            double value = src[i][j];
            if (value > 0.0) {
                mat->values[value_index] = value;
                j_values[value_index] = j;
                ++non_zero_in_row;
                ++value_index;
            }
        }

        i_values[i + 1] = i_values[i] + non_zero_in_row;
    }

    mat->i_values = i_values;
    mat->j_values = j_values;

    return mat;
}

double sp_mat_get_value(sp_mat_ref _mat, sp_mat_size i, sp_mat_size j) {
    sp_mat_size left  = _mat->i_values[i + 0];
    sp_mat_size right = _mat->i_values[i + 1]; 

    double value = 0.0;

    size_t count = right - left;
    for (sp_mat_size i = left; i < right; ++i) {
        if (_mat->j_values[i] == j) {
            value = _mat->values[i];
        }
    }

    return value;
}

// sp_mat_ref sp_mat_load(FILE *src);
// void sp_mat_save(sp_mat_ref _mat, FILE *dst);

void sp_mat_free(sp_mat_ref _mat) {
    free(_mat->values);
    free(_mat->i_values);
    free(_mat->j_values);
    free(_mat->metrics);
    free(_mat);
}
