#include <iostream> 
#include "attention_layer.h"
#include "gemm.h"


// const int MATRIX_DIM_X = 10; 
// const int MATRIX_DIM_Y = 10; 
// const int MATRIX_DIM_Z = 10; 

void dut(hls::stream<dtype_in> &strm_in, hls::stream<dtype_out> &strm_out) 
{
    dtype_in input1[MATRIX_DIM_X][MATRIX_DIM_Y];
    dtype_in input2[MATRIX_DIM_Y][MATRIX_DIM_Z];
    dtype_out output[MATRIX_DIM_X][MATRIX_DIM_Z];
    float stream_input1;
    float stream_input2;

    // read stream 1
    for (int i = 0; i < MATRIX_DIM_X; ++i) {
        for(int j = 0; j < MATRIX_DIM_Y; ++j) {
            stream_input1 = strm_in.read();
            input1[i][j] = stream_input1;
        }
    }

    // read stream 2
    for (int j = 0; j < MATRIX_DIM_Y; ++j) {
        for(int k = 0; k < MATRIX_DIM_Z; ++k) {
            stream_input2 = strm_in.read();
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


