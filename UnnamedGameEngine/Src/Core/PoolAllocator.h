#pragma once

#include "Common.h"

namespace UEngine
{
	class PoolAllocator
	{
	private:
		struct Chunk
		{
			Chunk* next;
		};

		size_t chunkSize;

		size_t chunksPerPool;

		size_t allocatedChunks;

		std::vector<char*> pools;

		Chunk* currentChunk;

		Chunk* AllocatePool();

		void CleanupCapacity();

	public:
		PoolAllocator(size_t chunkSize, size_t chunksPerPool);

		~PoolAllocator();

		void* Allocate();

		void Deallocate(void* ptr);

		size_t AllocatedChunksCount() const;

		size_t PoolCapacity() const;

		size_t PoolsCount() const;

		size_t Capacity() const;

		PoolAllocator(const PoolAllocator&) = delete;
		PoolAllocator(PoolAllocator&&) = delete;
		PoolAllocator& operator=(const PoolAllocator&) = delete;
		PoolAllocator& operator=(PoolAllocator&&) = delete;
	};
}