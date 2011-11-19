/*
 * FreeListNode.cpp
 *
 *  Created on: 11.11.2011
 *      Author: stan
 */

#include <stdlib.h>
#include "FreeListNode.h"
#include <new>
#include <iostream>
#include <stdio.h>

using namespace std;

namespace cache_allocator {

FreeListNode::FreeListNode(size_t blockSize) {
	m_blockSize = blockSize;
	m_freeList = (ChunkHeader *)NULL;
	m_usedList = (ChunkHeader *) NULL;
}

void *FreeListNode::getBlock()
{
	ChunkHeader *chunk;
	char *block;

	// если chunk в m_freeList берем его оттуда и кладем в m_usedList
	if (m_freeList)
	{
		//1. берем chunk из m_freeList
		chunk = m_freeList;
		m_freeList = chunk->next;
		if (m_freeList)
			m_freeList->last = NULL;

//		кладем в m_usedList
		chunk->next = m_usedList;
		if (m_usedList) {
			m_usedList->last = chunk;
		}
		m_usedList = chunk;
		return (void *)(m_usedList + sizeof(ChunkHeader));
	}
	// иначе создаем новой chunk и кледем его в m_usedList
	else
	{
		size_t chunkSize = sizeof(ChunkHeader) + m_blockSize;
		block = (char *)malloc(chunkSize);
		if (!block)
			throw bad_alloc();
		ChunkHeader *chunk = (ChunkHeader *)block;

		if (m_usedList)
		{
			m_usedList->last = chunk;
			chunk->next = m_usedList;
			chunk->last = NULL;
			m_usedList = chunk;
		}
		else
		{
			chunk->last = chunk->next = (ChunkHeader*) NULL;
			m_usedList = chunk;
		}
	}
	return (void *)(block + sizeof(ChunkHeader));
}

void FreeListNode::freeBlock(void * ptr)
{
	ChunkHeader* chunk = (ChunkHeader *) ((char *)ptr - sizeof(ChunkHeader));
	//  удаляем его их m_usedList и кладем во m_freeList
	//1.  удаляем его их m_usedList
	if (chunk->next) {
		chunk->next->last = chunk->last;
	} else {
		if (chunk->last) {
			chunk->last->next = NULL;
		}
	}

	if (chunk->last) {
		chunk->last->next = chunk->next;
	} else {
		m_usedList = chunk->next;
		if (m_usedList) {
			m_usedList->last = NULL;
		}
	}

	//2. кладем во m_freeList
	if (m_freeList) {
		m_freeList->last = chunk;
	}

	chunk->next = m_freeList;
	chunk->last = NULL;
	m_freeList = chunk;
}

FreeListNode::~FreeListNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace cache_allocator */

