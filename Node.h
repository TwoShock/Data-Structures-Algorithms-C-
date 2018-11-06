#pragma once

template<class Data>class Node{
private:
    Data nodeData;
    Node* leftChild;
    Node* rightChild;
    unsigned int nodeCount;
public:
    Node(Data value){
        this->nodeData = value;
        leftChild = NULL;
        rightChild = NULL;
        nodeCount = 1;
    }
    Node* getLeftChild(){
        return leftChild;
    }
    Node* getRightChild(){
        return rightChild;
    }
    Data getValue(){
        return nodeData;
    }
    void setLeftChild(Node<Data>* node){
        leftChild = node;
    }
    void setRightChild(Node<Data>* node){
        rightChild = node;
    }
    void setValue(Data value){
        nodeData = value;
    }
    void insert(Data value){
        if (nodeData == value) {
            nodeCount++;
            return;
            
        }
        else if(value < nodeData){
            if (leftChild == NULL)
                leftChild = new Node<Data>(value);
            else
                leftChild->insert(value);
        }
        else if(value > nodeData){
            if (rightChild == NULL)
                rightChild = new Node<Data>(value);
            else
                rightChild->insert(value);
        }
    }
    
    Node* find(Data value){
        if (value == nodeData) {
            return this;
        }
        else if(value < nodeData){
            if(leftChild != NULL)
                return leftChild->find(value);
        }
        else if(value > nodeData){
            if(rightChild != NULL){
                return rightChild->find(value);
            }
        }
        return NULL;
    }
    
    Node<Data>* getMin(){
        if (leftChild == NULL) {
            return this;
        }
        else{
            return leftChild->getMin();
        }
    }
    Node<Data>* next(Node<Data>* node,Node<Data>* root){
        //returns next inorder succesor
        if (node->getRightChild() != NULL) {
            return node->rightChild->getMin();
        }
        Node<Data>* successor = NULL;
        while (root != NULL) {
            if (node -> getValue() < root -> getValue()) {
                successor = root;
                root = root->getLeftChild();
            }
            else if(node -> getValue() > root -> getValue()){
                root = root->getRightChild();
            }
            else{
                break;
            }
        }
        return successor;
    }
    unsigned int getDepth(Node<Data>*node){
        if (node == NULL) {
            return 0;
        }
        else{
            unsigned int leftDepth = getDepth(node->leftChild);
            unsigned int rightDepth = getDepth(node->rightChild);
            
            if(leftDepth > rightDepth)
                return leftDepth + 1;
            else if(rightDepth > leftDepth)
                return rightDepth + 1;
            else
                return leftDepth+1;
        }
    }
    unsigned int getNodeCount(){
        return nodeCount;
    }
    void deleteNodeBranch(Node<Data>*node){
        if (node == NULL) {
            return;
        }
        deleteNodeBranch(node->leftChild);
        deleteNodeBranch(node->rightChild);
        free(node);
    }
};
