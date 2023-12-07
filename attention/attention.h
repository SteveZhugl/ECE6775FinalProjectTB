//===========================================================================
// attention.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef ATTENTION
#define ATTENTION


const float euler_number = 2.7182818284590;

// Function to calculate power using Taylor series expansion
double custom_exponential(double base, double exponent) {
    double result = 1.0;

    // Calculate power using Taylor series expansion
    for (int i = 1; i <= 100; ++i) {
        double term = 1.0;
        for (int j = 1; j <= i; ++j) {
            term *= exponent / j;
        }
        result += term;
    }

    // Multiply by the base
    result = base * result;

    return result;
}

template <int MATRIX_DIM_X, int MATRIX_DIM_Y, int MATRIX_DIM_Z>
void attention_mechanism
(
    float matrix_input1[MATRIX_DIM_X][MATRIX_DIM_Y], 
    float matrix_input2[MATRIX_DIM_Y][MATRIX_DIM_Z],
    float matrix_output[MATRIX_DIM_X][MATRIX_DIM_Z]
)
{
    float matrix_gemm_output[MATRIX_DIM_X][MATRIX_DIM_Z];
    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        for(int k = 0; k < MATRIX_DIM_Z; ++k)
        {
            matrix_gemm_output[i][k] = 0;
        }
    }
        

    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        for(int j = 0; j < MATRIX_DIM_Y; ++j)
        {
            for(int k = 0; k < MATRIX_DIM_Z; ++k)
            {
                matrix_gemm_output[i][k] += matrix_input1[i][j] * matrix_input2[j][k];
            }
        }
    }

    // Matrix_dim_x is the layer size for softmax
    for(int i = 0; i < MATRIX_DIM_X; ++i)
    {
        float euler_layer_sum = 0;
        float euler_sums[MATRIX_DIM_Z];

        for (int k = 0; k < MATRIX_DIM_Z; ++k) {
            euler_sums[k] = custom_exponential(euler_number, matrix_gemm_output[i][k]);
            euler_layer_sum += euler_sums[k];
        }

        for (int l = 0; l < MATRIX_DIM_Z; ++l) {
            matrix_output[i][l] = euler_sums[l] / euler_layer_sum;
        }
    }
}

#endif
