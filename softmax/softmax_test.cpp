#include <iostream>
#include <string>
#include <fstream> 
#include <sstream>
#include <cstdlib>

#include "softmax.h"
#include "vector.h"

void read_vector
(
    float input_vector[layer_size]
) 
{
    std::ifstream infile_a("data/vector_dat.dat");
    if (infile_a.is_open()) 
    {
        for (int a = 0; a < layer_size; a++) 
        {

            float i;
            infile_a >> i;
            input_vector[a] = i;
        }
        infile_a.close();
    }
}

void verify_output(float output[layer_size])
{
    float difference = 0;
    std::ifstream infile_b("data/output_dat.dat");
    if (infile_b.is_open()) 
    {
        for (int a = 0; a < layer_size; a++) 
        {
            float i;
            infile_b >> i;
            std::cout << "Python Output: " << i << " Calculated Output: " << output[a] << std::endl;
            difference = abs(output[a] - i);
            std::cout << "Difference: " << difference << std::endl;
        }
        infile_b.close();
    }
}


int main() 
{
    float input_vector[layer_size];
    float output[layer_size];

    read_vector(input_vector);
    softmax<layer_size>(input_vector, output);
    // dut(input_1, input_2, output);
    verify_output(output);
}