/*
 * FreeListNodeHashTable.cpp
 *
 *  Created on: 18.11.2011
 *      Author: stas
 */

#include "FreeListNodeHashTable.h"
#include <stddef.h>

namespace cache_allocator {

FreeListNodeHashTable::FreeListNodeHashTable(size_t blockSize) : FreeListNode(blockSize) {
	left = (FreeListNodeHashTable*)NULL;
	right = (FreeListNodeHashTable*)NULL;
}

FreeListNodeHashTable::~FreeListNodeHashTable() {
}

} /* namespace cache_allocator */
