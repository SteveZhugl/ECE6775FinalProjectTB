#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>

#include <iostream>
#include <fstream>

#include "timer.h"
#include "typedefs.h"
#include "gemm.h"
#include "attention_layer.h"

//------------------------------------------------------------------------
// Helper function for reading images and labels
//------------------------------------------------------------------------

void read_input_matricies(int8_t input_matrix_A[MATRIX_DIM_X][MATRIX_DIM_Y], 
                          int8_t input_matrix_B[MATRIX_DIM_Y][MATRIX_DIM_Z]) {
  std::ifstream infile_a("data/quantized_matrix_a.dat");
  if (infile_a.is_open()) {
    for (int x = 0; x < MATRIX_DIM_X; x++) {
      for (int y = 0; y < MATRIX_DIM_Y; y++) {
        int i;
        infile_a >> i;
        input_matrix_A[x][y] = i;
      }
    }
    infile_a.close();
  }

  std::ifstream infile_b("data/quantized_matrix_b.dat");
  if (infile_b.is_open()) {
    for (int y = 0; y < MATRIX_DIM_Y; y++) {
      for (int z = 0; z < MATRIX_DIM_Z; z++) {
        int i;
        infile_b >> i;
        input_matrix_B[y][z] = i;
      }
    }
    infile_b.close();
  }
}

void read_output_matricies(int8_t output_matrix_C[MATRIX_DIM_X][MATRIX_DIM_Z]) {
  std::ifstream infile_c("data/quantized_output.dat");
  if (infile_c.is_open()) {
    for (int x = 0; x < MATRIX_DIM_X; x++) {
      for (int z = 0; z < MATRIX_DIM_Z; z++) {
        int i;
        infile_c >> i;
        output_matrix_C[x][z] = i;
      }
    }
    infile_c.close();
  }
}

//--------------------------------------
// main function
//--------------------------------------
int main(int argc, char **argv) {
  // Open channels to the FPGA board.
  // These channels appear as files to the Linux OS
  int fdr = open("/dev/xillybus_read_32", O_RDONLY);
  int fdw = open("/dev/xillybus_write_32", O_WRONLY);

  // Check that the channels are correctly opened
  if ((fdr < 0) || (fdw < 0)) {
    fprintf(stderr, "Failed to open Xillybus device channels\n");
    exit(-1);
  }

  // Arrays to store test data and expected results (labels)
  int8_t input_matrix1[MATRIX_DIM_X][MATRIX_DIM_Y]; 
  int8_t input_matrix2[MATRIX_DIM_Y][MATRIX_DIM_Z];
  int8_t output_matrix[MATRIX_DIM_X][MATRIX_DIM_Z];
  bit32_t test_image;

  // Timer
  Timer timer("gemm on FPGA");
  // intermediate results
  int nbytes;
  int error = 0;
  int num_test_insts = 0;
  float correct = 0.0;

  //--------------------------------------------------------------------
  // Read data from the input file into two arrays
  //--------------------------------------------------------------------
  read_input_matricies(input_matrix1, input_matrix2);
  read_output_matricies(output_matrix);

  timer.start();
  //--------------------------------------------------------------------
  // Send data to accelerator
  //--------------------------------------------------------------------
  // for (int i = 0; i < TEST_SIZE; ++i) {
  //   // Send 32-bit value through the write channel
  //   for (int j = 0; j < 8; j++) {
  //     for (int k = 0; k < 32; k++) {
  //       test_image(k, k) = test_images[i][j * 32 + k];
  //     }
  //     nbytes = write(fdw, (void *)&test_image, sizeof(test_image));
  //     assert(nbytes == sizeof(test_image));
  //   }
  // }

  for (int x = 0; x < MATRIX_DIM_X; ++x) {
    for (int y = 0; y < MATRIX_DIM_Y; ++y) {
      for (int byte_offset = 0; byte_offset < 32; ++byte_offset) {
        test_image(byte_offset, byte_offset) = input_matrix1[x][y * 32 + byte_offset];
      }
      nbytes = write(fdw, (void *)&test_image, sizeof(test_image));
      assert(nbytes == sizeof(test_image));
    }
  }

  for (int y = 0; y < MATRIX_DIM_Y; ++y) {
    for (int z = 0; z < MATRIX_DIM_Z; ++z) {
      for (int byte_offset = 0; byte_offset < 32; ++byte_offset) {
        test_image(byte_offset, byte_offset) = input_matrix1[y][z * 32 + byte_offset];
      }
      nbytes = write(fdw, (void *)&test_image, sizeof(test_image));
      assert(nbytes == sizeof(test_image));
    }
  }

  //--------------------------------------------------------------------
  // Receive data from the accelerator
  //--------------------------------------------------------------------
  for (int x = 0; x < MATRIX_DIM_X; ++x) {
    for(int z = 0; z < MATRIX_DIM_Z; ++z) {
      bit32_t output;
      nbytes = read(fdr, (void *)&output, sizeof(output));
      assert(nbytes == sizeof(output));
      // verify results
      if (output == output_matrix[x][z])
        correct += 1.0;
    }
  }
  timer.stop();

  int num_operations = MATRIX_DIM_X * MATRIX_DIM_Z;
  //--------------------------------------------------------------------
  // Calculate error rate
  //--------------------------------------------------------------------
  std::cout << "Number of Operations: " << num_operations << std::endl;
  std::cout << "Accuracy: " << correct / num_operations << std::endl;

  return 0;
}
