#include "pch.h"
#include "Logger.h"

#include <chrono>
#include <time.h>
#include <iomanip>

meow::Logger::Logger()
	: m_hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) } {

	std::cout << "\n\n";
}

meow::Logger::~Logger() {

	SetConsoleTextAttribute(m_hConsole, m_BaseColor);
}

void meow::Logger::LogError(const std::string& error)
{
	SetConsoleTextAttribute(m_hConsole, m_ErrorColor);
	
	std::tm tm = GetTime();
	std::cout << "<" << std::put_time(&tm, "%X") << ">" << " ERROR:\t" << error << std::endl << std::endl;
}

void meow::Logger::LogWarning(const std::string& warning) {

	SetConsoleTextAttribute(m_hConsole, m_WarningColor);
	std::tm tm = GetTime();
	std::cout << "<" << std::put_time(&tm, "%X") << ">" << " WARNING:\t" << warning << std::endl << std::endl;
}

void meow::Logger::LogInfo(const std::string& info) {

	SetConsoleTextAttribute(m_hConsole, m_InfoColor);
	std::tm tm = GetTime();
	std::cout << "<" << std::put_time(&tm, "%X") << ">" << " INFO:\t" << info << std::endl << std::endl;
}

std::tm meow::Logger::GetTime() {
	
	auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm tm{};
	localtime_s(&tm, &tt);
	return tm;
}
