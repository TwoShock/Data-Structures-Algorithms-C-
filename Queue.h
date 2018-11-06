#pragma once
#include "LinkedList.h"

template<class Data>
class Queue{
private:
    unsigned int qSize;
    LinkedList<Data> qData;
public:
    void enqueue(Data value){
        qSize++;
        qData.push_back(value);
    }
    void dequeue(){
        if (qSize == 0) {
            return;
        }
        qSize--;
        qData.delete_start();
    }
    Data front(){
        return qData.getHead()->data;;
    }
   friend ostream& operator<<(ostream& os,Queue<Data> q){
       Node<Data> *head = q.qData.getHead();
       while (head != NULL) {
           os<<head->data<<" ";
           head = head->next;
       }
        return os;
    }
};
