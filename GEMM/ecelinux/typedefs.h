//===========================================================================
// typedefs.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "ap_int.h"
#include "ap_fixed.h"

typedef ap_int<6>  dtype_in;
typedef ap_int<20> dtype_out; 
typedef ap_int<4>  bit4_t;
typedef ap_int<6>  bit6_t;
typedef ap_int<8>  bit8_t;
typedef ap_int<16> bit16_t;
typedef ap_int<32> bit32_t;
typedef ap_int<64> bit64_t;

#endif
