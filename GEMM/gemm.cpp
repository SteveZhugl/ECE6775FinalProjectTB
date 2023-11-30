#include <iostream> 
#include <hls_stream.h>
#include "attention_layer.h"
#include "gemm.h"


// const int MATRIX_DIM_X = 10; 
// const int MATRIX_DIM_Y = 10; 
// const int MATRIX_DIM_Z = 10; 

void dut(hls::stream<float> &strm_in_a, hls::stream<float> &strm_in_b, 
    hls::stream<float> &strm_out
) 
{
    dtype_in input1[MATRIX_DIM_X][MATRIX_DIM_Y];
    dtype_in input2[MATRIX_DIM_Y][MATRIX_DIM_Z];
    float stream_input1;
    float stream_input2;
    dtype_out output[MATRIX_DIM_X][MATRIX_DIM_Z];

    // read stream 1
    for (int i = 0; i < MATRIX_DIM_X; ++i) {
        for(int j = 0; j < MATRIX_DIM_Y; ++j) {
            stream_input1 = strm_in_a.read();
            input1[i][j] = stream_input1;
        }
    }

    // read stream 2
    for (int j = 0; j < MATRIX_DIM_Y; ++j) {
        for(int k = 0; k < MATRIX_DIM_Z; ++k) {
            stream_input2 = strm_in_b.read();
            input2[j][k] = stream_input2;
        }
    }

    // call GEMM
    matrix_multiply<MATRIX_DIM_X, MATRIX_DIM_Y, MATRIX_DIM_Z>(input1, input2, output);

    // write out the result
    for (int i = 0; i < MATRIX_DIM_X; ++i) {
        for(int k = 0; k < MATRIX_DIM_Z; ++k) {
            strm_out.write(output[i][k]);
        }
    }
}


