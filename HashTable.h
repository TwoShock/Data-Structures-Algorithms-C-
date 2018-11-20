#pragma once
#include "HashFunction.h"
#include <vector>
using namespace std;
template<class key,class value>
class HashTable{
private:
    struct HashNode{
        value element;
        key k;
        HashNode *next;
        HashNode(){
            next = NULL;
        }
        HashNode(value element,HashNode *head = NULL){
            this->element = element;
            this->next = head;
        }
    };
    HashFunction<key>& hashFunction;
    vector<HashNode*> hashTable;
    unsigned int size;
    unsigned int maxSize;
    int collisionBound;
    unsigned int rehashCount;
    
    void rehash(){
        rehashCount++;
        vector<HashNode*> newHashTable;
        maxSize = maxSize*2;
        newHashTable.reserve(maxSize);
        
        for (int i = 0; i < hashTable.size(); i++) {
            if (hashTable[i] != NULL) {
                cout<<hashTable[i]->element;
                HashNode *head = hashTable[i];
                while (head != NULL) {
                    insertUtil(head->k,head->element,newHashTable);
                    head = head->next;
                }
            }
        }
        hashTable.resize(maxSize);
        hashTable = newHashTable;
    }
    bool insertUtil(key k,value v,vector<HashNode*>& hashTable){
        size++;
        unsigned long index = hashFunction(k,maxSize);
        HashNode *element = new HashNode(v);
        element->k = k;
        if (hashTable[index] == NULL) {
            hashTable[index] = element;
            return true;
        }
        else{
            unsigned int count = 2;
            HashNode *head = hashTable[index];
            while (head->next != NULL) {
                count++;
                head = head->next;
            }
            
            if (count > collisionBound) {
                rehash();
                return false;
            }
            head->next = element;
        }
        return true;
    }
public:
    HashTable(HashFunction<key>& hashFunction,unsigned int maxCollision = 4,
              unsigned int maxSize = 1024):hashFunction(hashFunction){
        collisionBound = maxCollision;
        size = 0;
        this->maxSize = maxSize;
        hashTable.reserve(maxSize);
        for (int i = 0 ; i < maxSize; i++) {
            hashTable[i] = NULL;
        }
        rehashCount = 0;
    }
    
    void printIndex(unsigned int index){
        HashNode *head = hashTable[index];
        cout<<index<<" : ";
        while (head != NULL) {
            cout<<head->element<<" ";
            head = head->next;
        }
    }
    bool remove(key k,value v){
        if (!isMember(k,v)) {
            return false;
        }
        unsigned long index = hashFunction(k,maxSize);
        HashNode *head = hashTable[index];
        HashNode *prev = NULL;
        if(head->next == NULL){
            hashTable[index] = NULL;
            delete head;
            return true;
        }
        if (head->element == v && head->next != NULL) {
            head->element = head->next->element;
            head->next = head->next->next;
            return true;
        }
        
        while (head != NULL) {
            prev = head;
            head = head->next;
            if (head->element == v) {
                break;
            }
        }
        prev->next = head->next;
        delete head;
        return true;
    }
    bool insert(key k,value v){
        return insertUtil(k,v,this->hashTable);
    }
    bool isMember(key k,value v){
        unsigned long index = hashFunction(k,maxSize);
        HashNode *head = hashTable[index];
        while (head != NULL) {
            if (head->element == v) {
                return true;
            }
            head = head->next;
        }
        return false;
    }
    unsigned int numMatches(key k){
        unsigned long index = hashFunction(k,maxSize);
        unsigned int count = 0;
        HashNode *head = hashTable[index];
        while (head != NULL) {
            head = head->next;
            count++;
        }
        return count;
    }
    unsigned int getRehashCount(){
        return rehashCount;
    }
    value getIthMatch(key k,unsigned int i){
        unsigned long index = hashFunction(k,maxSize);
        unsigned int count = 0;
        HashNode *head = hashTable[index];
        while (head != NULL) {
            if (count == i) {
                return head->element;
            }
            head = head->next;
            count++;
        }
        cerr<<"No match"<<endl;
        throw 0;
    }
    friend ostream& operator<<(ostream& os,HashTable& table){
        for(int i = 0;i<table.maxSize;i++){
            if (table.hashTable[i] != NULL) {
                os<<i<<": ";
                table.printIndex(i);
                os<<endl;
            }
        }
        return os;
    }
    
};
