#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;
template<class Data>
struct Node{
    Data data;
    Node *next;
    
    Node(Data data){
        this->data = data;
    }
    Node(){}
};
template<class Data>
class LinkedList{
private:
    Node<Data> *head,*tail;
    int length;

public:
    LinkedList(){
        head = NULL;
        tail = NULL;
        length = 0;
    }
    void push_back(Data value){
        length++;
        Node<Data> *temp = new Node<Data>(value);
        temp->next = NULL;
        
        if (head == NULL) {
            head = temp;
            tail = temp;
            temp = NULL;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
    }
    int size(){
        return length;
    }
    Node<Data> *getHead(){
        return head;
    }
    Node<Data> *getTail(){
        return tail;
    }
    void push_front(Data value){
        if (size() == 0) {
            push_back(value);
            return;
        }
        length++;
        Node<Data> *temp = new Node<Data>(value);
        temp->next = head;
        head = temp;
        
    }
    void insert_pos(int pos,Data value){
        length++;
        Node<Data>*temp = new Node<Data>(value);
        Node<Data> *previous;
        Node<Data> *current;
        current = head;
        
        for (int i = 1; i < pos; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = temp;
        temp->next = current;
    }
    void delete_start(){
        length--;
        Node<Data> *temp;
        temp = head;
        head = head->next;
        delete temp;
    }
    void delete_end(){
        length--;
        Node<Data> *previous;
        Node<Data> *current;
        current = this->head;
        
        while (current->next != NULL) {
            previous = current;
            current = current->next;
        }
        tail = previous;
        tail->next = NULL;
        delete current;
        
    }
    void delete_at_pos(int pos){
        length--;
        Node<Data> *current;
        Node<Data> *previous;
        current = head;
        for(int i = 0;i < pos;i++ ){
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }
    void reverse(){
        Node<Data> *previous = NULL;
        Node<Data > *current = head;
        Node<Data> *next = NULL;
        while (current != NULL) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next ;
            
        }
        head = previous;
    }

    void empty(){
        Node<Data> *current = getHead();
        Node<Data> *next;
        while (current!=NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        head = NULL;
    }
    friend ostream& operator<<(ostream& os, LinkedList& l){
        Node<Data> *head = l.getHead();
        while (head != NULL) {
            os<<head->data<<"->";
            head = head->next;
        }
        os<<"NULL";
        return os;
    }
};

