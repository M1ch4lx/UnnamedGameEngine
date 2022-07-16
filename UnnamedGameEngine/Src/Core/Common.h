#pragma once

#include <string>
#include <vector>
#include <list>
#include <functional>
#include <stack>
#include <type_traits>
#include <memory>
#include <array>

namespace UEngine
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
}