#include "Pch.h"
#include "Timer.h"

#include <iostream>

namespace UEngine
{
	Timer::Timer()
	{

	}

	void Timer::Start()
	{
		start = std::chrono::steady_clock::now();
	}

	void Timer::Stop()
	{
		end = std::chrono::steady_clock::now();
	}

	void Timer::Wait(unsigned int miliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	}

	float Timer::GetElapsedTime() const
	{
		return static_cast<float>(
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	}
}