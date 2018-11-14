#include <iostream>
#include <limits.h>
#include "heap.h"
using namespace std;

// Header file explains functionalities of methods

heap :: heap(int capacity){
    mapping = new hashTable(capacity);
    currSize = 0;
    this->capacity = capacity;
    data.resize(capacity+1);
}

// id - String id of node; key - Integer key of node; pv - Pointer of node
int heap :: insert(const std::string &id, int key, void *pv){

    if(currSize > capacity-1){
        return 1;
    }
    else if(mapping->contains(id)){
        return 2;
    }

    data[++currSize].id = id;
    data[currSize].key = key;
    data[currSize].pData = pv;
    mapping->insert(id);
    percolateUp(currSize);

    return 0;
}


// id - String id of node; key - Integer key to set
int heap :: setKey(const std::string &id, int key){

    node *pn =  static_cast<node *> (mapping->getPointer(id));

    if(pn == NULL){
        return 1;
    }

    int oldKey = pn->key;
    pn->key = key;
    int posCur = getPos(pn);

    if(oldKey < key){
        percolateDown(posCur);
    }
    else{
        percolateUp(posCur);
    }

    return 0;
}

// id - String id of node to be removed; key - Integer key of node; ppData - data to be removed
int heap :: remove(const std::string &id, int *pKey, void *ppData){

    node *pn =  static_cast<node *> (mapping->getPointer(id));

    if(pn == NULL){
        return 1;
    }
    if(pKey != NULL){
        *pKey = pn->key;
    }
    if(ppData != NULL){
        *(static_cast<void **> (ppData)) = pn->pData;
    }

    setKey(id, INT_MIN);
    deleteMin();
    mapping->remove(id);
    return 0;
}

// id - String id of node; key - key of node; ppData - data associated with node
int heap :: deleteMin(std::string *pId, int *pKey, void *ppData){

    mapping->remove(data[1].id);

    if(currSize == 0){
        return 1;
    }

    if(pId != NULL){
        (*pId) = data[1].id;
    }
    if(pKey != NULL){
        (*pKey) = data[1].key;
    }
    if(ppData != NULL){
        *(static_cast<void **> (ppData)) = data[1].pData;
    }

    data[1] = data[currSize--];
    percolateDown(1);
    return 0;
}

// posCur - Current position of node
int heap :: getPos(node *pn){

    int pos = pn - &data[0];
    return pos;
}

// posCur - Current position of node
void heap :: percolateUp(int posCur){

    node temp = data[posCur];

    while(posCur >1 && (temp.key < data[posCur/2].key)){
        data[posCur] = data[posCur/2];
        mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
    }

    data[posCur] = temp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

// posCur - Current position of node
void heap :: percolateDown(int posCur){

    int child;
    node temp  = data[posCur];

        while((2*posCur) <= currSize){
        child = 2*posCur;

        if(child != currSize && data[child+1].key < data[child].key){
            child++;
        }

        if(data[child].key < (temp.key)){
            data[posCur] = data[child];
            mapping->setPointer(data[posCur].id, &data[posCur]);
        }

        else{
            break;
        }
        posCur = child;
    }
    data[posCur] = temp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}