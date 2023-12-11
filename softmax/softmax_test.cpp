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
    std::ofstream outfile_a("data/draft_a.txt");
    if (infile_a.is_open()) 
    {
        for (int a = 0; a < layer_size; a++) 
        {

            float i;
            infile_a >> i;
            input_vector[a] = i;
            outfile_a << input_vector[a] << ", ";
        }
        infile_a.close();
        outfile_a.close();
    }
}

void verify_output(float output[layer_size])
{
    float difference = 0;
    std::ifstream infile_b("data/output_dat.dat");
    std::ofstream outfile_c("data/draft_c.txt", std::ios::out);
    float accerr = 0;
    float avgerr = 0;
    if (infile_b.is_open()) 
    {
        for (int a = 0; a < layer_size; a++) 
        {
            float i;
            infile_b >> i;
            std::cout << "Python Output: " << i << " Calculated Output: " << output[a] << std::endl;
            difference = abs(output[a] - i);
            std::cout << "Difference: " << difference << std::endl;
            accerr += abs(difference);
            avgerr += abs(difference / i);
            outfile_c << i << " " << output[a] << " " << difference << std::endl;
        }
        accerr /= 128;
        avgerr /= 128;
        outfile_c << accerr << std::endl;
        outfile_c << avgerr;
        outfile_c.close();
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