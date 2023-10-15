#pragma once

#include <stdexcept>

namespace stfcpp
{
	class assertion_failed_exception : public std::exception
	{
	public:
		inline assertion_failed_exception(const std::string& message) : m_message(message)
		{

		}

		inline const char* what() const noexcept override { return m_message.c_str(); }

	private:
		std::string m_message;
	};
}