#ifndef PROFILER_H
#define PROFILER_H

#define STARCLONE_PROFILE

#ifdef STARCLONE_PROFILE
#define PROFILE_START Profiler::instance()->profileStart(__FUNCTION__);
#define PROFILE_END Profiler::instance()->profileEnd(__FUNCTION__);
#else
#define PROFILE_START
#define PROFILE_END
#endif

#include <unordered_map>

class Profiler {

  public:

	void profileStart(std::string name);
	void profileEnd(std::string name);

	void logData();

	static Profiler* instance();

  private:

	Profiler();
	Profiler(Profiler&);

	static Profiler s_xInstance;

	struct Profile {
	
		unsigned long long startTime;
		unsigned long long totalTime;
		unsigned int callCount;
	};

	typedef std::unordered_map<std::string, Profile> ProfileMap;
	ProfileMap m_xProfiles;

	unsigned int m_iFrequency;

	unsigned long long now();
};

#endif