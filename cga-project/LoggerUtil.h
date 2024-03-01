#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

class LoggerUtil {
public:
	inline static void CustomErrorLog(std::string &msg, const char* func)
	{
		SetConsoleColor(4);
		std::cout <<  "ERROR: " << msg << " : [" << func << " ]" << std::endl;
	}
	#define CE_OUTPUT_ERROR(msg) CustomErrorLog(msg, __FUNCSIG__)

	inline static void CustomWarningLog(std::string& msg, const char* func)
	{
		SetConsoleColor(6);
		std::cout << "WARNING: " << msg << " : [" << func << " ]" << std::endl;
	}
	#define CE_OUTPUT_WARNING(msg) CustomWarningLog(msg, __FUNCSIG__)

	inline static void CustomDebugLog(std::string& msg, const char* func)
	{
		SetConsoleColor(3);
		std::cout << "DEBUG: " << msg << " : [" << func << " ]" << std::endl;
	}
	#define CE_OUTPUT_DEBUG(msg) CustomDebugLog(msg, __FUNCSIG__)

private:
	//COLORS LIST
	//1: Blue
	//2: Green
	//3: Cyan
	//4: Red
	//5: Purple
	//6: Yellow (Dark)
	//7: Default white
	//8: Gray/Grey
	//9: Bright blue
	//10: Brigth green
	//11: Bright cyan
	//12: Bright red
	//13: Pink/Magenta
	//14: Yellow
	//15: Bright white
	inline static void SetConsoleColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};