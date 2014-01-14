#include "LogManager.h"

#include <iostream>
#include <sstream>
#include <ctime>
#include <direct.h>
#include <Shlwapi.h>

LogManager LogManager::m_instance;

LogManager::LogManager()
{
	m_xFile = nullptr;
	bDisableFile = false;
	m_hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	m_logFilePath = "logs\\";
	m_logFileName = GenerateFileName();
	VerifyLogPath();

	if(!bDisableFile)
		OpenFile();
}

LogManager::~LogManager()
{
	CloseFile();
}

bool LogManager::Write( std::string text, int color )
{
	WriteCmd(text, color);
	return (bDisableFile || WriteFile(text));
}

void LogManager::WriteCmd( std::string text, int color )
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(m_hstdout, &csbi);
	SetConsoleTextAttribute(m_hstdout, color);
	std::cout << text;
	SetConsoleTextAttribute(m_hstdout, csbi.wAttributes);
}

bool LogManager::WriteFile( std::string text )
{
	if(FileOpen()) {
		(*m_xFile) << text;
		m_xFile->flush();
		return true;
	}
	return false;
}

std::string LogManager::GenerateFileName()
{
	time_t t = time(0);
	struct tm* now = new struct tm();
	localtime_s(now, &t);

	int mon = now->tm_mon+1;
	std::stringstream str;
	str << m_logFilePath
		<<(now->tm_year+1900) << "-"
		<< ((mon < 10) ? "0" : "") << mon << "-"
		<< ((now->tm_mday < 10) ? "0" : "") << now->tm_mday << " "
		<< ((now->tm_hour < 10) ? "0" : "") << now->tm_hour << "-"
		<< ((now->tm_min < 10) ? "0" : "") << now->tm_min << "-"
		<<((now->tm_sec < 10) ? "0" : "") << now->tm_sec << ".log";

	delete now;
	return str.str();
}

void LogManager::VerifyLogPath()
{
	char* pathbuf = _getcwd(NULL, 0);
	std::string logPath(pathbuf);
	logPath += "\\" + m_logFilePath;

	if(!PathIsDirectoryA(logPath.c_str())) {

		if(_mkdir(logPath.c_str()) == -1) {

			bDisableFile = true;
			Log::Warn("Couldn't verify/create log path; disabling logging to file." + logPath);
		}
	}
}

bool LogManager::OpenFile()
{
	if(m_xFile != nullptr) {
		
		CloseFile();
	}

	std::string fileName = GenerateFileName();
	m_xFile = new std::ofstream(fileName);

	if(!m_xFile->is_open()) {

		Log::Warn("Couldn't create log file " + fileName);
		CloseFile();
		return false;
	}

	Log::Success("LogFile: " + fileName);
	return true;
}

void LogManager::CloseFile()
{
	if(m_xFile != nullptr) {

		if(m_xFile->is_open()) {

			m_xFile->close();
		}

		delete m_xFile;
		m_xFile = nullptr;
	}
}

bool LogManager::FileOpen() {

	return ( (m_xFile != nullptr && m_xFile->is_open()) );
}


bool Log::Write( std::string text, int color /*= COLOR_DEFAULT*/ )
{
	return LogManager::GetInstance().Write(text,color);
}

bool Log::Writeln( std::string text, int color /*= COLOR_DEFAULT*/ )
{
	text += "\n";
	return Log::Write(text, color);
}

bool Log::Warn( std::string warn )
{
	return Log::Writeln(warn, Log::COLOR_WARNING);
}

bool Log::Err( std::string err )
{
	return Log::Writeln(err, Log::COLOR_ERROR);
}

bool Log::Success( std::string msg )
{
	return Log::Writeln(msg, Log::COLOR_SUCCESS);
}
