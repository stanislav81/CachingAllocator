/*
 * CacheAllocator.cpp
 *
 *  Created on: 11.11.2011
 *      Author: stan
 */

#include "CacheAllocator.h"
#include "FreeListNode.h"

namespace cache_allocator {

CacheAllocator::CacheAllocator(): m_hashTableSize(100*1024)
{
	m_hashTable = new HashTable(m_hashTableSize);
}


CacheAllocator::~CacheAllocator() {
	// TODO Auto-generated destructor stub
}

} /* namespace cache_allocator */
