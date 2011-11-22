/*
 * HashTable.cpp
 *
 *  Created on: 19.11.2011
 *      Author: stas
 */

#include "HashTable.h"
#include "FreeListNodeHashTable.h"

namespace cache_allocator {

HashTable::HashTable(size_t size) :
	m_tableSize(size),
	m_hashTable(NULL),
	m_headList(NULL)
{
	m_hashTable = new FreeListNodeHashTable*[m_tableSize];
	for (size_t i = 0; i < m_tableSize; i++ ) {
		m_hashTable[i] = (FreeListNodeHashTable*)NULL;
	}
}

FreeListNode *HashTable::getNode(size_t blockSize)
{
	FreeListNodeHashTable *nodePtr;

	nodePtr = m_hashTable[blockSize];

	if (nodePtr == (FreeListNodeHashTable*)NULL)
	{
		nodePtr = m_hashTable[blockSize] = new FreeListNodeHashTable(blockSize);

		// двигаемся слева на право
		if (m_headList == NULL) {
			m_headList = nodePtr;
		}
		else
		{
			m_headList->right = nodePtr;
			nodePtr->left = m_headList;
			m_headList = nodePtr;
		}
	}
	return static_cast<FreeListNode*>(nodePtr);
}

HashTable::~HashTable() {

	if (m_headList)
	{
		FreeListNodeHashTable *curr;
		for (curr = m_headList->right; curr != NULL; curr = curr->right) {
			delete curr;
		}
		for (curr = m_headList->left; curr != NULL; curr = curr->left) {
			delete curr;
		}
		delete m_headList;
	}
	delete m_hashTable;
}


} /* namespace cache_allocator */
