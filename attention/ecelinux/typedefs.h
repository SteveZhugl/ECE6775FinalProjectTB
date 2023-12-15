//===========================================================================
// typedefs.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <ap_int.h>

typedef ap_int<6>  dtype_in;
typedef ap_int<20> dtype_out; 
typedef ap_int<4>  bit4_t;
typedef ap_int<6>  bit6_t;
typedef ap_int<8>  bit8_t;
typedef ap_int<16> bit16_t;
typedef ap_int<32> bit32_t;
typedef ap_int<64> bit64_t;

// ap_float type conversion
// template<int W, int E> 
class ap_float{
public:
    ap_float() = default;

    // ap_float(int num){

    // }

    ap_float(float num){
        if(num == 0.0){
            exponent = 0;
            mantissa = 0.0;
            sign = false;
        }else{
            // make it int while keep the mantissa and exponent and Extract sign
            uint32_t bits = *reinterpret_cast<uint32_t*>(&num);
            sign = (bits >> 31) != 0;

            // Extract exponent and adjust with bias
            // int originalExponent = ((bits >> 23) & 0xFF) - 127; the bias is 2^E - 1, i.e., 1 << (E-1) - 1 
            // exponent = originalExponent + (1 << (E - 1)) - 1;
            int originalExponent = ((bits >> 23) & 0xFF) - 127;
            exponent = (ap_int<3>)(originalExponent & 0x3) + 1; // E

            // Extract mantissa and normalize
            // int originalMantissa = (bits & 0x7FFFFF) | 0x800000;
            // mantissa = originalMantissa >> (23 - W);
            int originalMantissa = (bits >> 21) & 0x3;
            switch(originalMantissa){
                case 0:
                    mantissa = 0; break;
                case 1:
                    mantissa = 0.25; break;
                case 2:
                    mantissa = 0.5; break;
                case 3:
                    mantissa = 0.75; break;
                default:
                    mantissa = 0; break;
            }
            std::cout << "Exponent: " << exponent-1 << "    Mantissa: " << mantissa+1 << std::endl;
        }
    }

    static float tofloat(ap_float& val){
        if(val.exponent == 0){
            return 0.0;
        }

        uint32_t num = val.sign ? 0x80000000 : 0;
        // mantissa
        if(val.mantissa == 0.25){
            num += 1 << 20;
        }else if(val.mantissa == 0.5){
            num += 2 << 20;
        }else{
            num += 3 << 20;
        }
        // exponent
        num += ((uint32_t)val.exponent + 126) << 23;
        // delete val;
        return *(float*)(&num);
    }

    friend std::istream& operator>>(std::istream &is, ap_float &num){
        // std::cout << "Do not type in to ap_float" << std::endl;
        return is;
    }

    friend std::ostream& operator<<(std::ostream &os, ap_float &num){
        if(num.exponent == 0){
            os << "0.0";
        }else{
            if(num.sign){
                os << "-";
            }
            os << (float)(num.mantissa+1) << " * 2^" << (num.exponent-1) << " = " << (1<<(num.exponent-1))*(float)(num.mantissa+1);
            // os << (1 << (num.exponent-1)) * (float)(num.mantissa + 1);
        }
        return os;
    }

    static int Comp(ap_float& a, ap_float& b){
        if(a.exponent > b.exponent){
            return 1;
        }else if(a.exponent < b.exponent){
            return -1;
        }

        if(a.mantissa > b.mantissa){
            return 1;
        }else if(a.mantissa < b.mantissa){
            return -1;
        }

        return 0;
    }

    static ap_float add(ap_float& a, ap_float& b){
        ap_float res;
        res.sign = false;
        ap_ufixed<4, 2> m;
        if(a.exponent > b.exponent){
            m = 1 + a.mantissa + ((1+b.mantissa) / (1 << (a.exponent - b.exponent)));
            if(m >= 2.0){
                if(a.exponent == 3){
                    res.mantissa = 0.75;
                    res.exponent = 3;
                }else{
                    res.mantissa = m/2 - 1;
                    res.exponent = a.exponent + 1;
                }
            }else{
                res.mantissa = m - 1;
                res.exponent = a.exponent;
            }
        }else if(a.exponent < b.exponent){
            m = 1 + b.mantissa + ((1+a.mantissa) / (1 << (a.exponent - b.exponent)));
            if(m >= 2.0){
                if(b.exponent == 3){
                    res.mantissa = 0.75;
                    res.exponent = 3;
                }else{
                    res.mantissa = m/2 - 1;
                    res.exponent = b.exponent + 1;
                }
            }else{
                res.mantissa = m - 1;
                res.exponent = b.exponent;
            }
        }else{
            m = 2 + a.mantissa + b.mantissa;
            if(a.exponent == 3){
                res.mantissa = 0.75;
                res.exponent = 3;
            }else{
                res.mantissa = m/2 - 1;
                res.exponent = a.exponent + 1;
            }
        }

        return res;
    }

    static ap_float minus(ap_float& a, ap_float& b){
        ap_float res;
        res.sign = false;

        ap_ufixed<3, 1> one = 0.25;
        int comp = ap_float::Comp(a, b);
        if(comp == 1){
            if(a.exponent > b.exponent){
                res.mantissa = (1+a.mantissa) + ~((1+b.mantissa) / (1 << (a.exponent - b.exponent))) + one;
                if(res.mantissa == 0.25){
                    res.mantissa = 0;
                    res.exponent = a.exponent - 2;
                }else if(res.mantissa == 0.5){
                    res.mantissa = 0;
                    res.exponent = a.exponent - 1;
                }else if(res.mantissa == 0.75){
                    res.mantissa = 0.5;
                    res.exponent = a.exponent - 1;
                }else{
                    res.mantissa -= 1;
                    res.exponent = a.exponent;
                }
            }else{ // else a.exponent == b.exponent
                res.mantissa = (1+a.mantissa) + ~((1+b.mantissa) / (1 << (a.exponent - b.exponent))) + one;
                if(a.exponent == 1){
                    res.mantissa = 0.0;
                    res.exponent = 0;
                }else{
                    if(res.mantissa == 0.75){
                        res.mantissa = 0.5;
                        res.exponent = a.exponent == 2 ? 1 : 2;
                    }else{
                        std::cout << "HERE!!!!!" << std::endl;
                        res.exponent = a.exponent == 2 ? (res.mantissa == 0.5 ? 1 : 0) : (res.mantissa == 0.5 ? 2 : 1);
                        res.mantissa = 0.0;

                    }
                }
            }
        }else if(comp == -1){
            res.sign = true;
            if(b.exponent > a.exponent){
                res.mantissa = (1+b.mantissa) + ~((1+a.mantissa) / (1 << (b.exponent - a.exponent))) + one;
                if(res.mantissa == 0.25){
                    res.mantissa = 0;
                    res.exponent = b.exponent - 2;
                }else if(res.mantissa == 0.5){
                    res.mantissa = 0;
                    res.exponent = b.exponent - 1;
                }else if(res.mantissa == 0.75){
                    res.mantissa = 0.5;
                    res.exponent = b.exponent - 1;
                }else{
                    res.mantissa -= 1;
                    res.exponent = b.exponent;
                }
            }else{
                res.mantissa = (1+b.mantissa) + ~((1+a.mantissa) / (1 << (b.exponent - a.exponent))) + one;
                if(b.exponent == 1){
                    res.mantissa = 0.0;
                    res.exponent = 0;
                }else{
                    if(res.mantissa == 0.75){
                        res.mantissa = 0.5;
                        res.exponent = b.exponent == 2 ? 1 : 2;
                    }else{
                        res.exponent = b.exponent == 2 ? (res.mantissa == 0.5 ? 1 : 0) : (res.mantissa == 0.5 ? 2 : 1);
                        res.mantissa = 0.0;
                    }
                }
            }
        }else{
            res.exponent = 0;
            res.mantissa = 0.0;
        }

        return res;
    }

    friend ap_float operator+(ap_float& a, ap_float& b){
        // zero
        if(a.exponent == 0 && b.exponent == 0){
            ap_float res;
            res.exponent = 0;
            res.mantissa = 0.0;
            res.sign = false;
            return res;
        }else if(a.exponent == 0){
            ap_float res;
            res.exponent = b.exponent;
            res.mantissa = b.mantissa;
            res.sign = b.sign;
            return res;
        }else if(b.exponent == 0){
            ap_float res;
            res.exponent = a.exponent;
            res.mantissa = a.mantissa;
            res.sign = a.sign;
            return res;
        }

        // non-zero
        if(!a.sign && !b.sign){
            return ap_float::add(a, b);
        }else if(a.sign && b.sign){
            ap_float res = ap_float::add(a, b);
            res.sign = true;
            return res;
        }
        else if(a.sign && !b.sign){
            return ap_float::minus(b, a);
        }else{
            return ap_float::minus(a, b);
        }
    }

    friend ap_float operator-(ap_float& a, ap_float& b){
        // zero
        if(a.exponent == 0 && b.exponent == 0){
            ap_float res;
            res.exponent = 0;
            res.mantissa = 0.0;
            res.sign = false;
            return res;
        }else if(a.exponent == 0){
            ap_float res;
            res.exponent = b.exponent;
            res.mantissa = b.mantissa;
            res.sign = b.sign;
            return res;
        }else if(b.exponent == 0){
            ap_float res;
            res.exponent = a.exponent;
            res.mantissa = a.mantissa;
            res.sign = a.sign;
            return res;
        }

        // non-zero
        if(!a.sign && b.sign){
            return ap_float::add(a, b);
        }else if(a.sign && !b.sign){
            ap_float res = ap_float::add(a, b);
            res.sign = true;
            return res;
        }else if(a.sign && b.sign){
            return a < b ? ap_float::minus(b, a) : ap_float::minus(a, b);
        }else{
            return ap_float::minus(a, b);
        }
    }

    friend ap_float operator*(ap_float& a, ap_float& b){
        ap_float res;
        res.sign = a.sign ^ b.sign;

        if(a.exponent == 0 || b.exponent == 0){
            res.exponent = 0;
            res.mantissa = 0.0;
            res.sign = false;
            return res;
        }

        // exponent
        if(a.exponent == 1 && b.exponent == 1){
            res.exponent = 1;
        }else{
            res.exponent = a.exponent + b.exponent;
            res.exponent = res.exponent == 3 ? 2 : 3;
        }

        // mantissa
        res.mantissa = a.mantissa * b.mantissa;

        // exponent

        return res;
    }

    ap_float& operator=(float num){
        uint32_t bits = *reinterpret_cast<uint32_t*>(&num);
        sign = (bits >> 31) != 0;
        int originalExponent = ((bits >> 23) & 0xFF) - 127;
        exponent = (ap_int<3>)(originalExponent & 0x3) + 1;
        mantissa = ((bits >> 21) & 0x2) | 0x3;
        return *this;
    }
    
    friend bool operator<(ap_float &a, ap_float &b){
        if(a.sign && !b.sign){
            return true;
        }else if(!a.sign && b.sign){
            return false;
        }else if(a.sign && b.sign){
            return ap_float::Comp(a, b) == 1;
        }else{
            return ap_float::Comp(a, b) == -1;
        }
    }

    friend bool operator<=(ap_float &a, ap_float &b){
        if(a.sign && !b.sign){
            return true;
        }else if(!a.sign && b.sign){
            return false;
        }else if(a.sign && b.sign){
            return ap_float::Comp(a, b) != -1;
        }else{
            return ap_float::Comp(a, b) != 1;
        }
    }

    friend bool operator>(ap_float& a, ap_float& b){
        if(a.sign && !b.sign){
            return false;
        }else if(!a.sign && b.sign){
            return true;
        }else if(a.sign && b.sign){
            return ap_float::Comp(a, b) == -1;
        }else{
            return ap_float::Comp(a, b) == 1;
        }
    }

    friend bool operator>=(ap_float& a, ap_float& b){
        if(a.sign && !b.sign){
            return false;
        }else if(!a.sign && b.sign){
            return true;
        }else if(a.sign && b.sign){
            return ap_float::Comp(a, b) != 1;
        }else{
            return ap_float::Comp(a, b) != -1;
        }
    }

    friend bool operator==(ap_float& a, ap_float& b){
        if(a.sign != b.sign){
            return false;
        }else{
            return !(ap_float::Comp(a, b));
        }
    }

    friend bool operator!=(ap_float& a, ap_float& b){
        if(a.sign != b.sign){
            return true;
        }else{
            return ap_float::Comp(a, b);
        }
    }

private:
    ap_ufixed<3, 1> mantissa;
    ap_uint<2> exponent;
    bool sign;
    // ap_fixed<W+1, 1> mantissa;
    // ap_uint<E> exponent;
    // int maskE = (1 << E) - 1;
    // int maskM = (1 << W) - 1;
};

// customized 4 int type
// class NF4{
// NF4 type conversion
// inline int round(float num){
//     int res;
//     float decimal = num - (int)num;
//     if(decimal <= -0.5){
//         res = (int)num - 1;
//     }else if(decimal < 0.5){
//         res = (int)num;
//     }else{
//         res = (int)num + 1;
//     }
//     return res;
// }

// inline ap_int<4> quantization(float data, float absmax, float *qconst){
//     *qconst = 7 / absmax;
//     int res = round((*qconst) * data);
//     return (ap_int<4>)res;
// }

// inline float dequantization(ap_int<4> data, float qconst){
//     return data / qconst;
// } 
// }

#endif


/*
    In the ap_float float constructor, if you want to make it E2M3, please refer to this:
    // switch(originalMantissa){
    //     case 0:
    //         mantissa = 0; break;
    //     case 1:
    //         mantissa = 0.125; break;
    //     case 2:
    //         mantissa = 0.25; break;
    //     case 3:
    //         mantissa = 0.375; break;
    //     case 4:
    //         mantissa = 0.5; break;
    //     case 5:
    //         mantissa = 0.625; break;
    //     case 6:
    //         mantissa = 0.75; break;
    //     case 7:
    //         mantissa = 0.875; break;
    //     default:
    //         mantissa = 0; break;     
    // }
    however, the operators need to be re-implemented

    The logic in minus is simplified:
    logic:
    else if(a.exponent == 2){
        if(res.mantissa == 0.25){
            res.mantissa = 0.0;
            res.exponent = 0;
        }else if(res.mantissa == 0.5){
            res.mantissa = 0.0;
            res.exponent = 1;
        }else{
            res.mantissa = 0.5;
            res.exponent = 1;
        }
    }else{
        if(res.mantissa == 0.25){
             res.mantissa = 0.0;
             res.exponent = 1;
        }else if(res.mantissa == 0.5){
             res.mantissa = 0.0;
             res.exponent = 2;
        }else{
             res.mantissa = 0.5;
             res.exponent = 2;
        }
    }
*/
