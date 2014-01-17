#include "stdafx.h"

#include "Profiler.h"

#include <Windows.h>
#include "LogManager.h"

Profiler Profiler::s_xInstance;

Profiler::Profiler() {

	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		Log::Err("QueryPerformanceFrequency failed");

	m_iFrequency = li.QuadPart / 1000;
}

Profiler* Profiler::instance() {

	return &s_xInstance;
}

void Profiler::profileStart(std::string name) {

	ProfileMap::iterator itr = m_xProfiles.find(name);

	Profile* profile;

	if (itr == m_xProfiles.end()) {
	
		profile = &m_xProfiles[name];

		profile->totalTime = 0;
		profile->callCount = 0;

	} else {
	
		profile = &itr->second;
	}

	profile->startTime = now();
	profile->callCount++;
}

void Profiler::profileEnd(std::string name) {

	ProfileMap::iterator itr = m_xProfiles.find(name);

	if (itr == m_xProfiles.end())
		return;

	Profile* profile = &itr->second;

	profile->totalTime += now() - profile->startTime;
}

void Profiler::logData() {

	Profile* profile;

	float total;
	float average;

	Log::Writeln("---------------");
	Log::Writeln("Profiler report");
	Log::Writeln("---------------");

	for (ProfileMap::iterator itr = m_xProfiles.begin(); itr != m_xProfiles.end(); ++itr) {
	
		profile = &itr->second;

		total = (float)profile->totalTime / (float)m_iFrequency;
		average = total / (float)profile->callCount;

		std::stringstream ss;
		ss << std::endl << itr->first << std::endl << "---" << std::endl <<
			"total time:\t" << total << "ms" << std::endl <<
			"average time:\t" << average << "ms" << std::endl <<
			"call count:\t" << profile->callCount << std::endl;

		Log::Write(ss.str());
	}

	Log::Write("\n");
}

unsigned long long Profiler::now() {

	LARGE_INTEGER li;

	QueryPerformanceCounter(&li);

	return li.QuadPart;
}