#pragma once

#include <chrono>
#include <thread>

namespace UEngine
{
	using TimePoint = std::chrono::steady_clock::time_point;

	class Timer
	{
	private:
		TimePoint start;

		TimePoint end;

	public:
		Timer();

		void Start();

		void Stop();

		void Wait(unsigned int miliseconds);

		float GetElapsedTime() const;
	};
}