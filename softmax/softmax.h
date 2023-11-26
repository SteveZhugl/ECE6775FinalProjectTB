//===========================================================================
// gemm.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef SOFTMAX
#define SOFTMAX

#include <cmath>  

const float euler_number = 2.7182818284590;

template <int layer_size>
void softmax
(
    float output_layer[layer_size], 
    float probability_distrubtion[layer_size]
)
{
    float euler_layer_sum = 0;
    float euler_sums[layer_size];
    for(int i = 0; i < layer_size; ++i) 
    {
        euler_sums[i] = std::pow(euler_number, output_layer[i]);
        euler_layer_sum += euler_sums[i];
    }

    for(int j = 0; j < layer_size; ++j) 
    {
        probability_distrubtion[j] = euler_sums[j] / euler_layer_sum;
    }
}

#endif
