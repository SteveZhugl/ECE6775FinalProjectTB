//===========================================================================
// attention.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#include "typedefs.h"
#include <hls_stream.h>

#ifndef ATTENTION
#define ATTENTION

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out);

template <int MATRIX_DIM_X, int MATRIX_DIM_Y, int MATRIX_DIM_Z>
void attention_mechanism
(
    bit32_t matrix_input1[MATRIX_DIM_X][MATRIX_DIM_Y], 
    bit32_t matrix_input2[MATRIX_DIM_Y][MATRIX_DIM_Z],
    bit32_t matrix_output[MATRIX_DIM_X][MATRIX_DIM_Z]
)
{
    bit32_t matrix_gemm_output[MATRIX_DIM_X][MATRIX_DIM_Z];
    float euler_number = 2.7182818284590452353602874713526624977572;

    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        for(int k = 0; k < MATRIX_DIM_Z; ++k)
        {
            matrix_gemm_output[i][k] = 0;
        }
    }
        

    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        for(int j = 0; j < MATRIX_DIM_Y; ++j)
        {
            for(int k = 0; k < MATRIX_DIM_Z; ++k)
            {
                matrix_gemm_output[i][k] += matrix_input1[i][j] * matrix_input2[j][k];
            }
        }
    }

    // Scale the values down
    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        for(int k = 0; k < MATRIX_DIM_Z; ++k)
        {
            matrix_gemm_output[i][k] /= 2;
            // std::cout<<matrix_gemm_output[i][k] << std::endl;
        }
    }


    // Matrix_dim_x is the layer size for softmax
    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        float euler_layer_sum = 0.0;
        float euler_sums[MATRIX_DIM_Z];

        for (int k = 0; k < MATRIX_DIM_Z; ++k) {
            euler_sums[k] = 1.0;
            for (int a = 1; a <= 10000; ++a) {
                double term = 1.0;
                for (int b = 1; b <= a; ++b) {
                    term *= matrix_gemm_output[i][k] / b;
                }
                euler_sums[k] += term;
            }
            euler_sums[k] = euler_number * euler_sums[k];
            euler_layer_sum += euler_sums[k];
        }
        for (int l = 0; l < MATRIX_DIM_Z; ++l) {
            matrix_output[i][l] = (euler_sums[l] / euler_layer_sum) * 100;
            // std::cout << matrix_output[i][l]  << std::endl;
        }
    }
}

#endif
