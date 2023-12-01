//===========================================================================
// softmax.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#include "typedefs.h"

#ifndef SOFTMAX
#define SOFTMAX

const float euler_number = 2.7182818284590;

template <int layer_size>
void softmax(dtype_in output_layer[layer_size], dtype_out probability_distribution[layer_size]) {
    float euler_layer_sum = 0;
    float euler_sums[layer_size];

    for (int i = 0; i < layer_size; ++i) {
        // Calculate power using Taylor series expansion
        euler_sums[i] = 1.0;
        for (int j = 1; j <= 100; ++j) {
            double term = 1.0;
            for (int k = 1; k <= j; ++k) {
                term *= output_layer[i] / k;
            }
            euler_sums[i] += term;
        }

        // Multiply by the base
        euler_sums[i] = euler_number * euler_sums[i];
        euler_layer_sum += euler_sums[i];
    }

    for (int j = 0; j < layer_size; ++j) {
        probability_distribution[j] = euler_sums[j] / euler_layer_sum;
    }
}

#endif
