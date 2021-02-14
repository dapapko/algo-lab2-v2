//
// Created by drford on 14.02.2021.
//

#ifndef TIGER_LAB2_BINNNUM_H
#define TIGER_LAB2_BINNNUM_H
#include <bitset>
#include <limits>
#include <iostream>
using namespace std;
template <typename T>
using BinaryStorage = bitset<8 * sizeof(T)>;


template<typename T>
class Binnum {
    T dec;
    BinaryStorage<T> binary_num_;
public:
    Binnum() :
            binary_num_({}) {}


    explicit Binnum(T num) {
        binary_num_ = bitset<sizeof(T)*8>(num);
        if (num < numeric_limits<T>::min() || num > numeric_limits<T>::max()) {
            throw runtime_error("number is out of range");
        }
        dec = num;
    }

    explicit Binnum(BinaryStorage<T> binary_num) :
    binary_num_(binary_num) {}


    size_t size() const {
        return  binary_num_.size();
    }

    Binnum<T> operator*(const Binnum<T> &other) const {
        return Binnum(dec * other.dec);
    }
    Binnum<T> operator+(const Binnum<T> &other) const {
        return Binnum(dec + other.dec);
    }
    Binnum<T> operator-(const Binnum<T> &other) const {
        return Binnum(dec - other.dec);
    }
    BinaryStorage<T> convert_to_binary_num(T num) {
        return bitset<sizeof(T)*8>(num);
    }
    void prt_bin() {
        cout << binary_num_;
    }
    friend ostream &operator<<(ostream &stream, const Binnum &binary_num) {
        //for (int i=0;i<sizeof(T)*8;i++) {
        //    stream << binary_num.binary_num_[i];
        // }
        // stream << endl;
        // return stream;
        stream << binary_num.dec;
    }
};


#endif //TIGER_LAB2_BINNNUM_H
