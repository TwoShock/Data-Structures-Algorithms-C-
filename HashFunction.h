#pragma once
#include <string>
#include <functional>
using namespace std;
template <class key>
struct HashFunction{
    long operator()(key k,unsigned int size){
        hash<key> hashFunction;
        unsigned long index = hashFunction(k);
        return index % size;
    }
};
