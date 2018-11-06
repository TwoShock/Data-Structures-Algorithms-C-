#pragma once
#include "Node.h"
template<class Data>class BST{
private:
    Node<Data>* root;
    unsigned int numberOfNodes;
public:
    BST(){
        root = NULL;
        numberOfNodes = 0;
    }
    void insert(Data value){
        numberOfNodes++;
        if (root == NULL) {
            root = new Node<Data>(value);
        }
        else{
            root->insert(value);
        }
    }
    Node<Data>* find(Data value){
        if (root != NULL) {
            return root->find(value);
        }
        return NULL;
    }
    Node<Data>* min(){
        if (root != NULL) {
            return root->getMin();
        }
        return NULL;
    }

    Node<Data>* getRoot(){
        return root;
    }
    unsigned int getNodeCount(){
        return numberOfNodes;
    }
    void remove(Node<Data>* node){
        if(node->getRightChild() == NULL && node->getLeftChild() == NULL){//leaf case
            node = NULL;
        }
        else if(node->getLeftChild() == NULL){//one child case 1
            Node<Data>* tmp = node->getRightChild();
            node->setRightChild(NULL);
            node->setValue(tmp->getValue());
            delete tmp;
            tmp = NULL;
        }
        else if(node->getRightChild() == NULL){//one child case 2
            Node<Data>* tmp = node->getLeftChild();
            node->setLeftChild(NULL);
            node->setValue(tmp->getValue());
            delete tmp;
            tmp = NULL;
        }
        else{//2 children
            Node<Data>* nextNode = node->next(node,root);
            node->setValue(nextNode->getValue());
            remove(nextNode);
        }
    }
    unsigned int depth(){
        return root->getDepth(root);
    }
    void deleteTree(){
        root->deleteNodeBranch(root);
    }

};
