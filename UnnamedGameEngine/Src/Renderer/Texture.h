#pragma once

#include "Data/Image.h"

namespace UEngine
{
	class Texture :public FactoryObject
	{
	public:
		virtual void Bind(unsigned int slot) = 0;
	};
}