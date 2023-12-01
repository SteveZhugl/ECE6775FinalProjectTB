#include <iostream>
#include <string>
#include <fstream> 
#include <sstream>
#include <cstdlib>

#include "gemm.h"
#include "attention_layer.h"

void read_matrices
(
    dtype_in input_matrix1[MATRIX_DIM_X][MATRIX_DIM_Y], 
    dtype_in input_matrix2[MATRIX_DIM_Y][MATRIX_DIM_Z]
) 
{
    std::ifstream infile_a("data/matrix_a_dat.dat");
    std::ofstream outfile_a("data/draft_a.txt");
    if (infile_a.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_X; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Y; b++) 
            {
                dtype_in i;
                infile_a >> i;
                input_matrix1[a][b] = i;
                outfile_a << input_matrix1[a][b] << ", ";
            }
            outfile_a << std::endl;
        }
        infile_a.close();
        outfile_a.close();
    }

    std::ifstream infile_b("data/matrix_b_dat.dat");
    if (infile_b.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_Y; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Z; b++) 
            {
                dtype_in i;
                infile_b >> i;
                input_matrix2[a][b] = i;
            }
        }
        infile_b.close();
    }
}

void verify_output(dtype_out output[MATRIX_DIM_X][MATRIX_DIM_Z])
{
    float difference = 0;
    std::ifstream infile_c("data/matrix_c_dat.dat");
    std::ofstream outfile_c("data/draft_c.txt", std::ios::out);
    float accerr = 0;
    float avgerr = 0;
    if (infile_c.is_open()) 
    {
        for (int a = 0; a < MATRIX_DIM_X; a++) 
        {
            for (int b = 0; b < MATRIX_DIM_Z; b++) 
            {
                float i;
                infile_c >> i;
                // std::cout << "Python Output: " << i << " Calculated Output: " << output[a][b] << std::endl;
                difference = abs((float)output[a][b] - i);
                accerr += abs(difference);
                avgerr += abs(difference / i);
                outfile_c << i << " " << output[a][b] << " " << difference << std::endl;
                // std::cout << "Difference: " << difference << std::endl;
            }
            outfile_c << std::endl;
        }
        accerr /= MATRIX_DIM_X * MATRIX_DIM_Z;
        avgerr /= MATRIX_DIM_X * MATRIX_DIM_Z;
        outfile_c << accerr << std::endl;
        outfile_c << avgerr;
        outfile_c.close();
        infile_c.close();
    }
}


int main() 
{
    dtype_in input_1[MATRIX_DIM_X][MATRIX_DIM_Y];
    dtype_in input_2[MATRIX_DIM_Y][MATRIX_DIM_Z];
    dtype_out output[MATRIX_DIM_X][MATRIX_DIM_Z];

    read_matrices(input_1, input_2);
    matrix_multiply<MATRIX_DIM_X, MATRIX_DIM_Y, MATRIX_DIM_Z>(input_1, input_2, output);
    //dut(input_1, input_2, output);
    verify_output(output);
}