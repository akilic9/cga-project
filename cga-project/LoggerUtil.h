#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

/*
************************************************************************REFERENCES************************************************************************
* https://cppcodetips.wordpress.com/2020/10/25/different-ways-to-get-the-name-of-the-calling-function-in-c/
* https://cplusplus.com/forum/beginner/92586/
* ********************************************************************************************************************************************************
*/

//TODO: Needs expanding for multiple types and formatting.
class LoggerUtil {
public:
	inline static void CustomErrorLog(std::string &msg, const char* func)
	{
		SetConsoleColor(4);
		std::cout <<  "ERROR: " << msg << " : [" << func << " ]" << std::endl;
	}

	inline static void CustomErrorLog(const char* msg, const char* func)
	{
		SetConsoleColor(4);
		std::cout << "ERROR: " << msg << " : [" << func << " ]" << std::endl;
	}
#define CE_OUTPUT_ERROR(msg) LoggerUtil::CustomErrorLog(msg, __FUNCSIG__)

	inline static void CustomWarningLog(std::string& msg, const char* func)
	{
		SetConsoleColor(6);
		std::cout << "WARNING: " << msg << " : [" << func << " ]" << std::endl;
	}

	inline static void CustomWarningLog(const char* msg, const char* func)
	{
		SetConsoleColor(6);
		std::cout << "WARNING: " << msg << " : [" << func << " ]" << std::endl;
	}
#define CE_OUTPUT_WARNING(msg) LoggerUtil::CustomWarningLog(msg, __FUNCSIG__)

	inline static void CustomDebugLog(std::string& msg, const char* func)
	{
#ifdef _DEBUG
		SetConsoleColor(3);
		std::cout << "DEBUG: " << msg << " : [" << func << " ]" << std::endl;
#endif // _DEBUG
	}

	inline static void CustomDebugLog(const char* msg, const char* func)
	{
#ifdef _DEBUG
		SetConsoleColor(3);
		std::cout << "DEBUG: " << msg << " : [" << func << " ]" << std::endl;
#endif // _DEBUG
	}
#define CE_OUTPUT_DEBUG(msg) LoggerUtil::CustomDebugLog(msg, __FUNCSIG__)

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