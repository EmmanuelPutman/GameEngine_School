#include "EP_Engine_PCH.h"
#include "Logger.h"

void ep::Logger::Log(const std::string& logString)
{
	std::cout << "{__LOGGER__} ";
	std::cout << logString << "\n";
}

void ep::Logger::Warning(const std::string& warningString)
{
	SetConsoleTextAttribute(m_Handler, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << "{__LOGGER__} ";

	std::cout << warningString << "\n";
	SetConsoleTextAttribute(m_Handler, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ep::Logger::Error(const std::string& errorString)
{
	SetConsoleTextAttribute(m_Handler, FOREGROUND_RED);
	std::cout << "{__LOGGER__} ";

	std::cout << errorString << "\n"; 
	SetConsoleTextAttribute(m_Handler, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//Change text foreground/background: https://stackoverflow.com/questions/17125440/c-win32-console-color