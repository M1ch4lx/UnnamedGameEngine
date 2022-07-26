#pragma once

namespace UEngine
{
	class Exception
	{
	private:
		std::string message;

	public:
		Exception(const std::string& message) :
			message(message)
		{}

		const std::string& Message() const
		{
			return message;
		}
	};
}