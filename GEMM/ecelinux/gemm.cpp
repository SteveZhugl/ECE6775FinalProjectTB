#include <iostream> 
#include "attention_layer.h"
#include "gemm.h"


// const int MATRIX_DIM_X = 10; 
// const int MATRIX_DIM_Y = 10; 
// const int MATRIX_DIM_Z = 10; 

const int BUS_WIDTH = 32;

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out) 
{
    bit32_t input1[MATRIX_DIM_X][MATRIX_DIM_Y];
    bit32_t input2[MATRIX_DIM_Y][MATRIX_DIM_Z];
    bit32_t output[MATRIX_DIM_X][MATRIX_DIM_Z];
    bit32_t stream_input1;
    bit32_t stream_input2;

    // read stream 1
    int bitcount = 0;
    for (int i = 0; i < MATRIX_DIM_X; ++i) {
        for(int j = 0; j < MATRIX_DIM_Y / BUS_WIDTH; ++j) {
            stream_input1 = strm_in.read();
            for (int k = 0; k < BUS_WIDTH; k++) {
                int bit_pos = j * BUS_WIDTH + k;
                if (bit_pos < MATRIX_DIM_Y) {
                    input1[i][bit_pos] = input_l(k, k); // Assuming you want to read each bit into the matrix
                }
            }
        }
    }

    // read stream 2
    for (int j = 0; j < MATRIX_DIM_Y; ++j) {
        for(int k = 0; k < MATRIX_DIM_Z / BUS_WIDTH; ++k) {
            stream_input2 = strm_in.read();
            for (int k = 0; k < BUS_WIDTH; k++) {
                int bit_pos = j * BUS_WIDTH + k;
                if (bit_pos < MATRIX_DIM_Z) {
                    input2[i][bit_pos] = input_l(k, k); // Assuming you want to read each bit into the matrix
                }
            }
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


