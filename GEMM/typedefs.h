//===========================================================================
// typedefs.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "ap_int.h"
#include "ap_fixed.h"

typedef ap_int<6> dtype_in;
typedef ap_int<20> dtype_out; 
typedef ap_uint<4> bit4;
typedef ap_uint<6> bit6;
typedef ap_uint<32> bit32;
typedef ap_uint<64> bit64;
typedef ap_uint<49> digit;


// inline void round(float &num){
//     float decimal = num - (int)num;
//     if(decimal <= -0.5){
//         num = (int)num - 1;
//     }else if(decimal < 0.5){
//         num = (int)num;
//     }else{
//         num = (int)num + 1;
//     }
// }

// inline ap_int<4> quantization(float data, float absmax, float &qconst){
//     qconst = 7 / absmax;
//     ap_int<4> res = round(qconst * data);
//     return res;
// }

// inline float dequantization(ap_int<4> data, float qconst){
//     return data / qconst;
// }


// typedef ac_float<54,2,11> ac_float_cdouble_t;
// typedef ac_float<25,2,8> ac_float_cfloat_t;

// template <int W, int I, int E>
// class ac_float {
// private:
//     using Ty = int; // You might use a different type based on your needs

//     Ty value;

// public:
//     typedef ac_fixed<W, I, true> mant_t;
//     typedef ac_int<E, true> exp_t;
//     mant_t m;
//     exp_t e;

//   inline ac_float_cdouble_t double_to_ac_float(double d) {
//     typedef ac_float_cdouble_t r_t;

//     r_t::exp_t exp;
//     r_t::mant_t mant = ac::frexp_d(d, exp);
//     return r_t(mant, exp, false);
//   }

//   inline ac_float_cfloat_t float_to_ac_float(float f) {
//     typedef ac_float_cfloat_t r_t;

//     r_t::exp_t exp;
//     r_t::mant_t mant = ac::frexp_f(f, exp);
//     return r_t(mant, exp, false);
//   }


//     // double
//     ac_float(double num) {
//         value = static_cast<Ty>(num * (1 << E));
//     }

//     // else
//     ac_float(bool b) { *this = (ac_int<1, false>) b;}
//     ac_float(char b) { *this = (ac_int<8, true>) b;}
//     // ac_float(signed char b ){}
//     // ac_float(unsigned char b )
//     // short
//     ac_float(signed int b ) { *this = (ac_int<32, true>) b;}
//     ac_float(unsigned int b ) { *this = (ac_int<32, false>) b;}


//     double to_double() const {
//         return static_cast<double>(value) / (1 << E);
//     }

//     ac_float operator+(const ac_float& other) const {
//         ac_float result;
//         result.value = value + other.value;
//         return result;
//     }

//     ac_float operator-(const ac_float& other) const {
//         ac_float result;
//         result.value = value - other.value;
//         return result;
//     }

//     ac_float operator*(const ac_float& other) const {
//         ac_float result;
//         result.value = value * other.value;
//         return result;
//     }

//     ac_float operator/(const ac_float& other) const {
//         ac_float result;
//         result.value = value / other.value;
//         return result;
//     }

//     // Implement other arithmetic operations as needed

//     friend std::ostream& operator<<(std::ostream& os, const ac_float& af) {
//         os << af.to_double();
//         return os;
//     }
// };


#endif
