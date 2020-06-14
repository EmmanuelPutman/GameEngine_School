#pragma once
#include "Singleton.h"
#include <iostream>
#include <Windows.h>

namespace ep
{
	class Logger : public Singleton<Logger>
	{
	public:
		Logger() = default;
		~Logger() = default;
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator= (const Logger&) = delete;
		Logger& operator= (const Logger&&) = delete;

		void Log(const std::string& logString);
		void Warning(const std::string& warningString);
		void Error(const std::string& errorString);

	private:
		HANDLE m_Handler = GetStdHandle(STD_OUTPUT_HANDLE);
	};
}

