#include <iostream> 
#include <hls_stream.h>
#include "vector.h"
#include "softmax.h"


void dut(hls::stream<float> &strm_in_a, hls::stream<float> &strm_out) 
{
    dtype_in input1[layer_size];
    float stream_input1;
    dtype_out output[layer_size];

    // read stream 1
    for (int i = 0; i < layer_size; ++i) {
        stream_input1 = strm_in_a.read();
        input1[i] = stream_input1;
    }

    // call softmax
    softmax<layer_size>(input1, output);

    // write out the result
    for (int i = 0; i < layer_size; ++i) {
        strm_out.write(output[i]);
    }
}


