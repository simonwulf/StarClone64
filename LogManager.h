#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <fstream>
#include <Windows.h>
#include <sstream>

namespace Log {

	enum {
		COLOR_BLACK,
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_AQUA,
		COLOR_RED,
		COLOR_PURPLE,
		COLOR_YELLOW,
		COLOR_WHITE,
		COLOR_GRAY,
		COLOR_LIGHT_BLUE,
		COLOR_LIGHT_GREEN,
		COLOR_LIGHT_AQUA,
		COLOR_LIGHT_RED,
		COLOR_LIGHT_PURPLE,
		COLOR_LIGHT_YELLOW,
		COLOR_LIGHT_WHITE
	};

	const static int COLOR_DEFAULT	= COLOR_LIGHT_WHITE;
	const static int COLOR_ERROR	= COLOR_LIGHT_RED;
	const static int COLOR_WARNING	= COLOR_LIGHT_YELLOW;
	const static int COLOR_SUCCESS	= COLOR_LIGHT_GREEN;

	bool Write(std::string text, int color = Log::COLOR_DEFAULT);
	bool Writeln(std::string text, int color = Log::COLOR_DEFAULT);
	bool Warn(std::string warn);
	bool Err(std::string err);
	bool Success(std::string msg);
}

class LogManager {

	public:
		~LogManager();

		static LogManager& GetInstance(){ return m_instance; }

		bool Write(std::string text, int color);


	private:
		LogManager();
		LogManager(const LogManager&);
		void operator=(const LogManager&);

		std::string m_logFilePath;
		std::string m_logFileName;
		std::ofstream* m_logFile;
		void* m_hstdout;
		bool bDisableFile;

		static LogManager m_instance;

		void WriteCmd(std::string text, int color);
		bool WriteFile(std::string text);

		std::string GenerateFileName();
		std::string GetTimestamp();
		bool OpenFile();
		void CloseFile();
		void VerifyLogPath();
};

#endif