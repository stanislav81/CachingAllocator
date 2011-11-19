/*
 * FreeListNode.h
 *
 *  Created on: 11.11.2011
 *      Author: stan
 */

#ifndef FREELISTNODE_H_
#define FREELISTNODE_H_
#include <stddef.h>

namespace cache_allocator {

struct ChunkHeader {
	ChunkHeader *last;
	ChunkHeader *next;
};

class FreeListNode {
	size_t m_blockSize;
	ChunkHeader *m_freeList;
	ChunkHeader *m_usedList;

public:
	FreeListNode(size_t blockSize);
	void* getBlock();
	void freeBlock(void *ptr);
	virtual ~FreeListNode();
};

} /* namespace cache_allocator */
#endif /* FREELISTNODE_H_ */
