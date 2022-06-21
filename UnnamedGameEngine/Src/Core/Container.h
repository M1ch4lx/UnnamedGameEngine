#pragma once

#include "Allocator.h"

namespace UEngine
{
	template<typename T>
	class Container
	{
	private:
		Allocator<T> allocator;

		std::vector<T*> instances;

	public:
		Container() :
			allocator(100)
		{}

		~Container()
		{
			Clear();
		}

		void Clear()
		{
			for (auto ptr : instances)
			{
				allocator.Delete(ptr);
			}
			instances.clear();
		}

		template<typename... Types>
		T* Create(Types... args)
		{
			if (instances.size() == allocator.Capacity())
			{
				instances.reserve(instances.capacity() + allocator.PoolCapacity());
			}
			instances.emplace_back(allocator.New(args...));

			return instances.back();
		}

		void Delete(T* instance)
		{
			auto iter = std::find(instances.begin(), instances.end(), instance);
			if (iter != instances.end())
			{
				allocator.Delete(instance);

				instances.erase(iter);
			}
		}

		void Delete(size_t index)
		{
			allocator.Delete(instances[index]);
			instances.erase(instances.begin() + index);
		}

		void DeleteIf(const std::function<bool(T*)>& callback)
		{
			std::erase_if(instances, [this, &callback](T* ptr)
				{
					if (callback(ptr))
					{
						allocator.Delete(ptr);
						return true;
					}
					return false;
				});
		}

		size_t Size() const
		{
			return instances.size();
		}

		T* operator[](size_t index)
		{
			return instances.at(index);
		}

		T* At(size_t index)
		{
			return instances.at(index);
		}

		std::vector<T*>& Collection()
		{
			return instances;
		}
	};
}