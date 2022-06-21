#include "Pch.h"
#include "PoolAllocator.h"

namespace Atron
{
	PoolAllocator::Chunk* PoolAllocator::AllocatePool()
	{
		auto poolBegin = new char[chunksPerPool * chunkSize];
		pools.emplace_back(poolBegin);

		auto chunk = poolBegin;
		for (int i = 0; i < chunksPerPool - 1; i++)
		{
			reinterpret_cast<Chunk*>(chunk)->next = reinterpret_cast<Chunk*>(chunk + chunkSize);
			chunk = reinterpret_cast<char*>(reinterpret_cast<Chunk*>(chunk)->next);
		}
		reinterpret_cast<Chunk*>(chunk)->next = nullptr;

		return reinterpret_cast<Chunk*>(poolBegin);
	}

	void PoolAllocator::CleanupCapacity()
	{
		for (auto pool : pools)
		{
			delete[] pool;
		}
		pools.clear();
		pools.shrink_to_fit();
		currentChunk = nullptr;
		allocatedChunks = 0;
	}

	PoolAllocator::PoolAllocator(size_t chunkSize, size_t chunksPerPool) :
		currentChunk(nullptr), chunkSize(chunkSize), chunksPerPool(chunksPerPool),
		allocatedChunks(0)
	{

	}

	PoolAllocator::~PoolAllocator()
	{
		CleanupCapacity();
	}

	void* PoolAllocator::Allocate()
	{
		if (!currentChunk)
		{
			currentChunk = AllocatePool();
		}

		auto chunk = currentChunk;
		currentChunk = currentChunk->next;

		allocatedChunks++;

		return chunk;
	}

	void PoolAllocator::Deallocate(void* ptr)
	{
		std::memset(ptr, 1, chunkSize);

		reinterpret_cast<Chunk*>(ptr)->next = currentChunk;

		currentChunk = reinterpret_cast<Chunk*>(ptr);

		allocatedChunks--;
	}

	size_t PoolAllocator::AllocatedChunksCount() const
	{
		return allocatedChunks;
	}

	size_t PoolAllocator::PoolCapacity() const
	{
		return chunksPerPool;
	}

	size_t PoolAllocator::PoolsCount() const
	{
		return pools.size();
	}

	size_t PoolAllocator::Capacity() const
	{
		return pools.size() * chunksPerPool;
	}

}