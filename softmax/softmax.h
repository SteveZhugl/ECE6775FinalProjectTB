//===========================================================================
// softmax.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef SOFTMAX
#define SOFTMAX

const float euler_number = 2.7182818284590;

// Function to calculate power using Taylor series expansion
double powerWithoutLibrary(double base, double exponent) {
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


template <int layer_size>
void softmax(float output_layer[layer_size], float probability_distribution[layer_size]) {
    float euler_layer_sum = 0;
    float euler_sums[layer_size];

    for (int i = 0; i < layer_size; ++i) {
        euler_sums[i] = powerWithoutLibrary(euler_number, output_layer[i]);
        euler_layer_sum += euler_sums[i];
    }

    for (int j = 0; j < layer_size; ++j) {
        probability_distribution[j] = euler_sums[j] / euler_layer_sum;
    }
}

#endif
