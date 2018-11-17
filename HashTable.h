#pragma once
#include "HashFunction.h"
#include <vector>
using namespace std;
template<class key,class value>
class HashTable{
private:
    struct HashNode{
        value element;
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
    
    void rehash(){
        vector<HashNode*> newHashTable;
        newHashTable.reserve(maxSize*2);
        for (int i = 0; i < hashTable.size(); i++) {
            newHashTable[i] = hashTable[i];
        }
        hashTable = newHashTable;
        maxSize *= 2;
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
    }
    bool insert(key k,value v){
        size++;
        unsigned int index = hashFunction(k,maxSize);
        HashNode *element = new HashNode(v);
        if (hashTable[index] == NULL) {
            hashTable[index] = element;
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
    void printIndex(unsigned int index){
        HashNode *head = hashTable[index];
        while (head != NULL) {
            cout<<head->element<<" ";
            head = head->next;
        }
    }
    bool remove(key k,value v){
        if (!isMember(k,v)) {
            return false;
        }
        unsigned int index = hashFunction(k,maxSize);
        HashNode *head = hashTable[index];
        HashNode *prev = NULL;
        /*if (head->element == v) {
            HashNode *temp = head;
            temp = temp->next;
            //free(head);
            head = temp;
        }*/
        while (head != NULL) {
            prev = head;
            head = head->next;
            if (head->element == v) {
                break;
            }
        }
        prev->next = head->next;
        free(head);
        return true;
    }
    bool isMember(key k,value v){
        unsigned int index = hashFunction(k,maxSize);
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
        unsigned int index = hashFunction(k,maxSize);
        unsigned int count = 0;
        HashNode *head = hashTable[index];
        while (head != NULL) {
            head = head->next;
            count++;
        }
        return count;
    }
    value getIthMatch(key k,unsigned int i){
        unsigned int index = hashFunction(k,maxSize);
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
    
};
