//===========================================================================
// gemm.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#include "typedefs.h"
#include <hls_stream.h>

#ifndef GEMM
#define GEMM

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out);

template <int MATRIX_DIM_X, int MATRIX_DIM_Y, int MATRIX_DIM_Z>
void matrix_multiply
(
    bit32_t matrix_A[MATRIX_DIM_X][MATRIX_DIM_Y], 
    bit32_t matrix_B[MATRIX_DIM_Y][MATRIX_DIM_Z],
    bit32_t matrix_C[MATRIX_DIM_X][MATRIX_DIM_Z]
)
{
    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        for(int k = 0; k < MATRIX_DIM_Z; ++k)
        {
            matrix_C[i][k] = 0;
        }
    }
        

    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        for(int j = 0; j < MATRIX_DIM_Y; ++j)
        {
            for(int k = 0; k < MATRIX_DIM_Z; ++k)
            {
                matrix_C[i][k] += matrix_A[i][j] * matrix_B[j][k];
            }
        }
    }
}

#endif
