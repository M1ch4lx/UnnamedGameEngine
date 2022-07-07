#pragma once

#include "PoolAllocator.h"

namespace UEngine
{
	template<typename T>
	class Allocator
	{
	private:
		PoolAllocator allocator;

	public:
		Allocator(size_t poolCapacity) :
			allocator(sizeof(T), poolCapacity)
		{}

		template<typename... Types>
		T* New(const Types&... args)
		{
			return new (allocator.Allocate()) T(args...);
		}

		void Delete(T* instance)
		{
			allocator.Deallocate(reinterpret_cast<void*>(instance));
		}

		size_t Capacity() const
		{
			return allocator.Capacity();
		}

		size_t PoolCapacity() const
		{
			return allocator.PoolCapacity();
		}
	};
}