#include "LogManager.h"

#include <iostream>
#include <sstream>
#include <ctime>
#include <direct.h>

LogManager LogManager::m_instance;

LogManager::LogManager()
{
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
	if(!bDisableFile)
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
	return false;
}

std::string LogManager::GenerateFileName()
{
	time_t t = time(0);
	struct tm* now = new struct tm();
	localtime_s(now, &t);

	std::stringstream str;
	str << (now->tm_year+1900) << "-"
		<< (now->tm_mon+1) << "-"
		<< now->tm_mday << " "
		<< now->tm_hour << "-"
		<< now->tm_min << "-"
		<< now->tm_sec << ".log";

	delete now;
	return str.str();
}

std::string LogManager::GetTimestamp()
{
	time_t t = time(0);
	struct tm* now = new struct tm();
	localtime_s(now, &t);

	std::stringstream str;
	str << "[" << now->tm_hour << ":"
		<< now->tm_min << ":"
		<< now->tm_sec << "]";

	delete now;
	return str.str();
}

void LogManager::VerifyLogPath()
{
	char* pathbuf = _getcwd(NULL, 0);
	std::string logPath(pathbuf);
	logPath += m_logFilePath;

	DWORD fileAttrib = GetFileAttributesA(logPath.c_str());
	if(fileAttrib & FILE_ATTRIBUTE_DIRECTORY)
		return;
	else if(fileAttrib == INVALID_FILE_ATTRIBUTES)
	{
		_mkdir(logPath.c_str());
	}
	else
	{
		bDisableFile = true;
		WriteCmd("Couldn't verify/create log path; disabling logging to file.", Log::COLOR_WARNING);
	}
}

bool LogManager::OpenFile()
{
	return false;
}

void LogManager::CloseFile()
{
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
