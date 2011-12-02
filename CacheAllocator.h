/*
 * CacheAllocator.h
 *
 *  Created on: 11.11.2011
 *      Author: stan
 */

#ifndef CACHEALLOCATOR_H_
#define CACHEALLOCATOR_H_
#include <map>
#include <list>
#include <iostream>
#include "FreeListNodeHashTable.h"
#include "HashTable.h"
using namespace std;

namespace cache_allocator {

class CacheAllocator {
	std::map<size_t, FreeListNode*> tree;

	HashTable *m_hashTable;
	size_t m_hashTableSize;

public:
	CacheAllocator();
	virtual ~CacheAllocator();

	template <class T>
	T *getBlock() {

		size_t blockSize = sizeof (T);
		FreeListNode *node;
		char *array;

		/*
		 Fred* p;
		 void* tmp = operator new(sizeof(Fred));
		 try {
		   new(tmp) Fred();  // Placement new
		   p = (Fred*)tmp;   // The pointer is assigned only if the ctor succeeds
		 }
		 catch (...) {
		   operator delete(tmp);  // Deallocate the memory
		   throw;                 // Re-throw the exception
		 }
		 * */

		if (blockSize < m_hashTableSize )
		{
			node = m_hashTable->getNode(blockSize);
			array = static_cast<char*>(node->getBlock());
		}
		else
		{
			std::map<size_t, FreeListNode*>::iterator it = tree.find(blockSize);
			if (it == tree.end()) {
				node = new FreeListNode(blockSize);
				array = static_cast<char*>(node->getBlock());
				tree[blockSize] = node;
			} else {
				array = static_cast<char*>((*it).second->getBlock());
			}
		}
		new(array) T();
		return (T*)(array);
	}

//	template <class T>
//	T&[] getBlock(size_t number) {
//
//		size_t blockSize = sizeof (T) * number;
//		FreeListNode *node;
//		char *array;
//
//		if (blockSize < m_hashTableSize )
//		{
//			node = m_hashTable->getNode(blockSize);
//			array = static_cast<char*>(node->getBlock());
//		}
//		else
//		{
//			std::map<size_t, FreeListNode*>::iterator it = tree.find(blockSize);
//			if (it == tree.end()) {
//				node = new FreeListNode(blockSize);
//				array = static_cast<char*>(node->getBlock());
//				tree[blockSize] = node;
//			} else {
//				array = static_cast<char*>((*it).second->getBlock());
//			}
//		}
//		new(array) T[number]();
//		return (T[)(array);
//	}

//	template <class T>
//	T *getBlock(size_t number) {
//
//		size_t blockSize = sizeof (T) * number;
//		FreeListNode *node;
//		char *array;
//
//		if (blockSize < m_hashTableSize )
//		{
//			node = m_hashTable->getNode(blockSize);
//			array = static_cast<char*>(node->getBlock());
//		}
//		else
//		{
//			std::map<size_t, FreeListNode*>::iterator it = tree.find(blockSize);
//			if (it == tree.end()) {
//				node = new FreeListNode(blockSize);
//				array = static_cast<char*>(node->getBlock());
//				tree[blockSize] = node;
//			} else {
//				array = static_cast<char*>((*it).second->getBlock());
//			}
//		}
//		return (T*)(array);
//	}

	template <class T>
	void freeBlock(T *ptr) {
		size_t blockSize = sizeof (T);
		ptr->~T();

		if (blockSize < m_hashTableSize)
		{
			FreeListNode *node = m_hashTable->getNode(blockSize);
			node->freeBlock(ptr);
		}
		else
		{
			std::map<size_t, FreeListNode*>::iterator it = tree.find(blockSize);
			if (it == tree.end()) {
				cerr << "error: This block does not belong to the CacheAllocator" << endl;
			} else {
				(*it).second->freeBlock((void *)ptr);
			}
		}
	}

//	void freeBlock(int *ptr) {
//		size_t blockSize = sizeof (int);
//
//		if (blockSize < m_hashTableSize)
//		{
//			FreeListNode *node = m_hashTable->getNode(blockSize);
//			node->freeBlock(ptr);
//		}
//		else
//		{
//			std::map<size_t, FreeListNode*>::iterator it = tree.find(blockSize);
//			if (it == tree.end()) {
//				cerr << "error: This block does not belong to the CacheAllocator" << endl;
//			} else {
//				(*it).second->freeBlock((void *)ptr);
//			}
//		}
//	}
//
//	void freeBlock(char *ptr) {
//		size_t blockSize = sizeof (char);
//
//		if (blockSize < m_hashTableSize)
//		{
//			FreeListNode *node = m_hashTable->getNode(blockSize);
//			node->freeBlock(ptr);
//		}
//		else
//		{
//			std::map<size_t, FreeListNode*>::iterator it = tree.find(blockSize);
//			if (it == tree.end()) {
//				cerr << "error: This block does not belong to the CacheAllocator" << endl;
//			} else {
//				(*it).second->freeBlock((void *)ptr);
//			}
//		}
//	}



	template<class T>
	void prepareFreeList(size_t size) {

		T** ptrArray = new T*[size];

		for (size_t i = 0; i < size; i++) {
			T *ptr = getBlock<T>();
			ptrArray[i] = ptr;
		}

		for (size_t i = 0; i < size; i++) {
			freeBlock(ptrArray[i]);
		}

		delete ptrArray;
	}

	void collect() {
		// TO DO !!!

		// collect needed giant block from map tree
		for (std::map<size_t, FreeListNode*>::iterator it = tree.begin(); it != tree.end(); ++it) {
			//
		}

		// collect small block from hash table
		FreeListNodeHashTable *headHashTable = m_hashTable->getHeadHashTable();
		if (headHashTable) {
			FreeListNodeHashTable *curr;
			for (curr = headHashTable; curr != NULL; curr = curr->right) {
				//
			}

			for (curr = headHashTable; curr != NULL; curr = curr->left) {
				//
			}
		}
	}

};

} /* namespace cache_allocator */
#endif /* CACHEALLOCATOR_H_ */

