#pragma once
#include "LinkedList.h"

template <class Data>
class Stack{
    
private:
    Data stackTop;
    unsigned int stackSize;
    LinkedList<Data> stackData;
public:
    Stack(){}
    void push(Data value){
        stackSize++;
        stackData.push_back(value);
        stackTop = stackData.getTail()->data;
    }
    Data peek(){
        return stackTop;
    }
    void pop(){
        if (stackSize == 0) {
            return;
        }
        stackSize--;
        stackData.delete_end();
        stackTop = stackData.getTail()->data;
    }
    friend ostream& operator<<(ostream& os,Stack<Data> s){
        Node<Data> *head = s.stackData.getHead();
        while (head != NULL) {
            os<<head->data<<" ";
            head = head->next;
        }
        return os;
    }
    unsigned int size(){
        return size;
    }
    Data top(){
        return stackTop;
    }

};
