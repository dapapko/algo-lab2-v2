#ifndef Binnum_H
#define Binnum_H

#include <iostream>
#include <array>
#include <limits>
#include <map>
#include<math.h>
const int r = 8;
using namespace std;


template<typename T>
class Binnum {
    array<bool,r> bin;

public:
    Binnum() :
            bin({}) {}

    explicit Binnum(T num) :
            bin(to_bin(num)) {
    }

    explicit Binnum(array<bool,r> bin) :
            bin(bin) {}


    size_t size() const {
        return  bin.size();
    }


    array<bool,r> to_bin(T num) {
        array<bool,r> bin;
        map<int, int> masks = {{8,0100}, {16, 040000},
        {32, 010000000000}};
T mask = masks[r];
       
        bin[0] = (num < 0 ? 1 : 0);
        unsigned int absval = abs(num);
        for (int i = 1; i < r; ++i) {
            bin[i] = (absval & mask ? 1 : 0);
            mask >>= 1;
        }
        return bin;
    }

    Binnum additional_code() const {
        Binnum res = *this;
        bool temp = res.bin[0];
        for(int k = 0; k < r; k++) {
            res.bin[k] = !res.bin[k];
        }
        Binnum comp;
        comp.bin[size()-1] = true;
        res = res + comp;
        res.bin[0] = temp;
        return res;
    }
    Binnum operator-(const Binnum &other) const {
      Binnum A = *this;
      Binnum B = other * Binnum<T>(-1);
      return A + B;
    }
   
    Binnum operator+(const Binnum &other) const {
        array<bool,r> res;

        Binnum A = *this;
        Binnum B = other;

        if (A.bin[0]) {
            A = A.additional_code();
        }

        if (B.bin[0]) {
            B = B.additional_code();
        }

        bool carry = false;
        bool carryOut;
for (int i = r - 1; i >= 0; i--) {
  auto a = A.bin[i];
  auto b = B.bin[i];
  res[i] = ((a ^ b) ^ carry);
  carry = ((a & b) | (a & carry)) | (b & carry);
  if(i == sizeof(T)*8 - 2) carryOut = carry;
  }
  if (carry != carryOut) {
    throw std::runtime_error("Overflow error");
}
      
       
        return Binnum(res);
    }
  

    Binnum shift() {
        Binnum res = *this;
        auto temp = res.bin[0];
        int k = 0;
        for (k = 0; k < size()-1; k++) {
            res.bin[k] = res.bin[k+1];
        }
        res.bin[k] = temp;
        return res;
    }

    Binnum operator*(const Binnum<T> &other) const {
        auto sign = bin[0] ^ other.bin[0];
        Binnum res;
        Binnum a = *this;
        Binnum b = other;
        a.bin[0] = false;
        b.bin[0] = false;

        for (int k = r-1; k > 0; k--) {
            if (b.bin[k]) {
                res = res + a;
            }
            a = a.shift();
        }
        res.bin[0] = sign;
        if (sign) {
            return res.additional_code();
        } else {
            return  res;
        }

    }

    T to_dec(){
        int k=0;
        int dec = 0;

        for(int i=r-1;i>=0;i--){
                dec+= bin[i]*pow(2, k);
            k++;
        }

        return dec;
    }

    friend ostream &operator<<(ostream &stream, const Binnum &binary_num) {
        for (auto element: binary_num.bin) {
            stream << element;
        }
        stream << endl;
        return stream;
    }
};
#endif