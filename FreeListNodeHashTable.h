/*
 * FreeListNodeHashTable.h
 *
 *  Created on: 18.11.2011
 *      Author: stas
 */

#ifndef FREELISTNODEHASHTABLE_H_
#define FREELISTNODEHASHTABLE_H_
#include "FreeListNode.h"

namespace cache_allocator {

class FreeListNodeHashTable : public FreeListNode {
public:

	FreeListNodeHashTable *left, *right;

	FreeListNodeHashTable(size_t blockSize);

	virtual ~FreeListNodeHashTable();
};

} /* namespace cache_allocator */
#endif /* FREELISTNODEHASHTABLE_H_ */
