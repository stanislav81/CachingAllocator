/*
 * HashTable.h
 *
 *  Created on: 19.11.2011
 *      Author: stas
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "stddef.h"

namespace cache_allocator {

class FreeListNodeHashTable;
class FreeListNode;

class HashTable {
	size_t m_tableSize;
	FreeListNodeHashTable **m_hashTable;
	FreeListNodeHashTable *m_headList; // To have able collect to left and right from this point
public:
	HashTable(size_t size);
	virtual ~HashTable();
	FreeListNode* getNode(size_t blockSize);
	size_t size() {return m_tableSize;}

	FreeListNodeHashTable *getHeadHashTable () { return m_headList; }
};

} /* namespace cache_allocator */
#endif /* HASHTABLE_H_ */
