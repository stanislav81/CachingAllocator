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
	std::map<size_t, FreeListNode*>::iterator it;

	size_t m_hashTableSize;
	HashTable *m_hashTable;

public:
	CacheAllocator();
	virtual ~CacheAllocator();

	template <class T>
	T *getBlock() {

		size_t blockSize = sizeof (T);
		FreeListNode *node;
		char *array;

		if (blockSize < m_hashTableSize )
		{
			node = m_hashTable->getNode(blockSize);
			array = static_cast<char*>(node->getBlock());
		}
		else
		{
			it = tree.find(blockSize);
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

	template <class T>
	T *getBlock(size_t number) {

		size_t blockSize = sizeof (T) * number;
		FreeListNode *node;
		char *array;

		if (blockSize < m_hashTableSize )
		{
			node = m_hashTable->getNode(blockSize);
			array = static_cast<char*>(node->getBlock());
		}
		else
		{
			it = tree.find(blockSize);
			if (it == tree.end()) {
				node = new FreeListNode(blockSize);
				array = static_cast<char*>(node->getBlock());
				tree[blockSize] = node;
			} else {
				array = static_cast<char*>((*it).second->getBlock());
			}
		}
		return (T*)(array);
	}

	template <class T>
	void freeBlock(T *ptr) {
		ChunkHeader *block = (ChunkHeader *)((char *)ptr - sizeof(ChunkHeader));
		size_t chunkSize = sizeof (T);
		size_t blockSize = block->size;

		if (chunkSize == blockSize) {
			ptr->~T();
		} else {
			for (size_t i = 0; i < blockSize/chunkSize; i++) {
				T* chunk = (T*)((char *)ptr + chunkSize*i);
				chunk->~T();
			}
		}

		if (blockSize < m_hashTableSize)
		{
			FreeListNode *node = m_hashTable->getNode(blockSize);
			node->freeBlock(ptr);
		}
		else
		{
			it = tree.find(blockSize);
			if (it == tree.end()) {
				cerr << "error: This block does not belong to the CacheAllocator" << endl;
			} else {
				(*it).second->freeBlock((void *)ptr);
			}
		}
	}

	void freeBlock(char *ptr) 			{	freeSimpleType(ptr);	}
	void freeBlock(bool *ptr) 			{	freeSimpleType(ptr);	}
	void freeBlock(int *ptr) 			{	freeSimpleType(ptr);	}
	void freeBlock(size_t *ptr) 		{	freeSimpleType(ptr);	}
	void freeBlock(long int *ptr) 		{	freeSimpleType(ptr);	}
	void freeBlock(long long int *ptr) 	{	freeSimpleType(ptr);	}
	void freeBlock(short *ptr) 			{	freeSimpleType(ptr);	}
	void freeBlock(float *ptr) 			{	freeSimpleType(ptr); 	}
	void freeBlock(double *ptr) 		{ 	freeSimpleType(ptr); 	}
	void freeBlock(long double *ptr) 	{ 	freeSimpleType(ptr);	}

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

	void prepareFreeList(size_t number, size_t size) {

		char** ptrArray = new char*[number];

		for (size_t i = 0; i < size; i++) {
			ptrArray[i] = getBlock<char>(size);
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

private:
	inline void freeSimpleType(void * ptr) {
		ChunkHeader *block = (ChunkHeader *)((char *)ptr - sizeof(ChunkHeader));
		size_t blockSize = block->size;

		if (blockSize < m_hashTableSize)
		{
			FreeListNode *node = m_hashTable->getNode(blockSize);
			node->freeBlock(ptr);
		}
		else
		{
			it = tree.find(blockSize);
			if (it == tree.end()) {
				cerr << "error: This block does not belong to the CacheAllocator" << endl;
			} else {
				(*it).second->freeBlock((void *)ptr);
			}
		}
	}

};

} /* namespace cache_allocator */
#endif /* CACHEALLOCATOR_H_ */

