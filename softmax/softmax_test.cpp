#include <iostream>
#include <string>
#include <fstream> 
#include <sstream>
#include <cstdlib>

#include "softmax.h"
#include "vector.h"

void read_matrices
(
    float input_matrix1[MATRIX_DIM_X][MATRIX_DIM_Y], 
    float input_matrix2[MATRIX_DIM_Y][MATRIX_DIM_Z]
) 
{
    std::ifstream infile_a("data/matrix_a_dat.dat");
    if (infile_a.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_X; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Y; b++) 
            {
                float i;
                infile_a >> i;
                input_matrix1[a][b] = i;
            }
        }
        infile_a.close();
    }

    std::ifstream infile_b("data/matrix_b_dat.dat");
    if (infile_b.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_Y; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Z; b++) 
            {
                float i;
                infile_b >> i;
                input_matrix2[a][b] = i;
            }
        }
        infile_b.close();
    }
}

void verify_output(float output[MATRIX_DIM_X][MATRIX_DIM_Z])
{
    float difference = 0;
    std::ifstream infile_c("data/matrix_c_dat.dat");
    if (infile_c.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_X; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Z; b++) 
            {
                float i;
                infile_c >> i;
                // std::cout << "Python Output: " << i << " Calculated Output: " << output[a][b] << std::endl;
                difference = abs(output[a][b] - i);
                // std::cout << "Difference: " << difference << std::endl;
            }
        }
        infile_c.close();
    }
}


int main() 
{
    float input_1[MATRIX_DIM_X][MATRIX_DIM_Y];
    float input_2[MATRIX_DIM_Y][MATRIX_DIM_Z];
    float output[MATRIX_DIM_X][MATRIX_DIM_Z];

    read_matrices(input_1, input_2);
    matrix_multiply<MATRIX_DIM_X, MATRIX_DIM_Y, MATRIX_DIM_Z>(input_1, input_2, output);
    // dut(input_1, input_2, output);
    verify_output(output);
}