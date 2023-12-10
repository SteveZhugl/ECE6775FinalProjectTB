#include <iostream> 
#include "attention_layer.h"
#include "gemm.h"
#include "typedefs.h"

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out) 
{
    bit32_t input1[MATRIX_DIM_X][MATRIX_DIM_Y];
    bit32_t input2[MATRIX_DIM_Y][MATRIX_DIM_Z];
    bit32_t output[MATRIX_DIM_X][MATRIX_DIM_Z];
    bit32_t stream_input1;
    bit32_t stream_input2;

    // read stream 1
    int input_index = 0;
    for (int i = 0; i < MATRIX_DIM_X; ++i) 
    {
        for(int j = 0; j < MATRIX_DIM_Y; ++j) 
        {
            stream_input1 = strm_in.read();
            input_index = i * MATRIX_DIM_X + j;
            input1[i][j] = stream_input1; // Assuming you want to read each bit into the matrix
        }
    }

    // read stream 2
    for (int j = 0; j < MATRIX_DIM_Y; ++j) {
        for(int k = 0; k < MATRIX_DIM_Z; ++k) {
            stream_input2 = strm_in.read();
            input_index = j * MATRIX_DIM_Y + k;
            input2[j][k] = stream_input2; // Assuming you want to read each bit into the matrix
        }
    }

    // call GEMM
    matrix_multiply<MATRIX_DIM_X, MATRIX_DIM_Y, MATRIX_DIM_Z>(input1, input2, output);

    // write out the result
    for (int i = 0; i < MATRIX_DIM_X; ++i) {
        for(int k = 0; k < MATRIX_DIM_Z; ++k) {
            std::cout << output[i][k] << std::endl;
            strm_out.write(output[i][k]);
        }
    }
}


