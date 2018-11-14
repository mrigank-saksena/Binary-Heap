#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap{

public:


	// The constructor allocates space for the nodes based on capacity
	heap(int capacity);

	/**
	* 1: inserts a new node with specified id string and key into the heap
	* node position is based on key
	* Returns 0 on success, 1 if the heap is already filled to its max capacity, 2 if node with id already exists
	*/
	int insert(const std::string &id, int key, void *pv = NULL);

	/**
	* 2: Set the key of specified node to specified value
	* Returns 0 on success, 1 if node does not exist
	*/
	int setKey(const std::string &id, int key);

	/**
	* 3: Removes node with specified value from the heap
	* Returns 0 on a success, 1 if node does not exist
	*/
	int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

	/**
	* 4: Removes the node with the smallest key from the heap
	* Works by setting smallest node's key to INT MIN and calling deleteMin
	* Returns 0 if success, 1 if the heap is empty
	*/
	int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);


  

private:

  	class node { // An inner class within heap
  		public:
    		std::string id; // The id of this node
    		int key; // The key of this node
    		void *pData; // A pointer to the actual data
  	};

  	std::vector<node> data; // The actual binary heap
  	int currSize; // The current total number of nodes in the heap
    int capacity;  // Maximum nodes the heap can contain
  	hashTable *mapping; // Maps ids to node pointers

	// Positions node by percolating upwards (swapping with parent until heap-ordering property is satisfied)
  	void percolateUp(int posCur);

	// Positions node by percolating downwards (swapping with children until heap-ordering property is satisfied)
  	void percolateDown(int posCur);

	// Retrieves position of given node and gives its index
  	int getPos(node *pn);

};

#endif //_HEAP_H