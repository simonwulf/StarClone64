#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include <ctime>
#include <iostream>

#include "LogManager.h"

#define PROFILE(stmt) { time_t start = clock(); stmt; time_t ticks = clock() - start; std::cout << "Executed " << #stmt << " in " << ticks << " ticks" << std::endl; }

void CheckForGLError();

#endif