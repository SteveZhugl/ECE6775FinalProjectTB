//===========================================================================
// typedefs.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "ap_int.h"
#include "ap_fixed.h"

typedef ap_int<6> dtype_in;
typedef ap_int<8> dtype_out; 
typedef ap_uint<4> bit4;
typedef ap_uint<6> bit6;
typedef ap_uint<32> bit32;
typedef ap_uint<64> bit64;
typedef ap_uint<49> digit;

#endif
