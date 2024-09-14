#pragma once

#include<string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";

#else
	return "C:/Users/lolek/Desktop/prj2/LightYears/LightYearsGame/assets/";
#endif
}
