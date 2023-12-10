#include <iostream>
#include <string>
#include <fstream> 
#include <sstream>
#include <cstdlib>

#include "attention.h"
#include "attention_layer.h"
#include "typedefs.h"

void read_matrices
(
    bit32_t input_matrix1[MATRIX_DIM_X][MATRIX_DIM_Y], 
    bit32_t input_matrix2[MATRIX_DIM_Y][MATRIX_DIM_Z]
) 
{
    std::ifstream infile_a("data/input_matrix1.dat");
    if (infile_a.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_X; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Y; b++) 
            {
                bit32_t i;
                infile_a >> i;
                input_matrix1[a][b] = i;
            }
        }
        infile_a.close();
    }

    std::ifstream infile_b("data/input_matrix2.dat");
    if (infile_b.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_Y; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Z; b++) 
            {
                bit32_t i;
                infile_b >> i;
                input_matrix2[a][b] = i;
            }
        }
        infile_b.close();
    }
}

void verify_output(bit32_t output[MATRIX_DIM_X][MATRIX_DIM_Z])
{
    float difference = 0.0;
    std::ifstream infile_c("data/output_matrix.dat");
    if (infile_c.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_X; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Z; b++) 
            {
                float i;
                infile_c >> i;
                std::cout << "Python Output: " << i << " Calculated Output: " << output[a][b] << std::endl;
                difference = abs((float)output[a][b] - i);
                std::cout << "Difference: " << difference << std::endl;
            }
        }
        infile_c.close();
    }
}


int main() 
{
    bit32_t input_1[MATRIX_DIM_X][MATRIX_DIM_Y];
    bit32_t input_2[MATRIX_DIM_Y][MATRIX_DIM_Z];
    bit32_t output[MATRIX_DIM_X][MATRIX_DIM_Z];

    read_matrices(input_1, input_2);

    hls::stream<bit32_t> strm_in;
    hls::stream<bit32_t> strm_out;
    for(int i=0; i<MATRIX_DIM_X; i++){
        for(int j=0; j<MATRIX_DIM_Y; j++){
            strm_in.write(input_1[i][j]);
        }
    }

    for(int i=0; i<MATRIX_DIM_Y; i++){
        for(int j=0; j<MATRIX_DIM_Z; j++){
            strm_in.write(input_2[i][j]);
        }
    }

    dut(strm_in, strm_out);

    for(int i=0; i<MATRIX_DIM_X; i++){
        for(int j=0; j<MATRIX_DIM_Z; j++){
            output[i][j] = strm_out.read();
        }
    }

    // attention_mechanism<MATRIX_DIM_X, MATRIX_DIM_Y, MATRIX_DIM_Z>(input_1, input_2, output);
    verify_output(output);
}