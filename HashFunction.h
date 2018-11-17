#pragma once
#include <string>
using namespace std;
template <class key>
struct HashFunction{
    virtual int operator()(key,unsigned int)=0;
};
struct StringHash:public HashFunction<string>{
    virtual int operator()(string key,unsigned int n){
        int hashSum = 0;
        for (int i = 0;i < key.length(); i++) {
            hashSum += key[i];
        }
        return hashSum%n;
    }
};

