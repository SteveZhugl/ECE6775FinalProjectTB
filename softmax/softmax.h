//===========================================================================
// gemm.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef SOFTMAX
#define SOFTMAX

const float euler_number = 2.71828182845904523536028747135266249775724709369995 

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
        euler_sums[i] = euler_number * 
        euler_layer_sum += 
    }
}

#endif
