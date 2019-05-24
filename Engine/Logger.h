#pragma once

namespace meow {

	class Logger
	{
	public:
		Logger();
		virtual ~Logger();

		virtual void LogError(const std::string& error);
		virtual void LogWarning(const std::string& warning);
		virtual void LogInfo(const std::string& info);
	protected:
		HANDLE m_hConsole;

		const WORD m_ErrorColor = 12, m_InfoColor = 11, m_WarningColor = 14, m_BaseColor = 7;

		std::tm GetTime();
	};
}

