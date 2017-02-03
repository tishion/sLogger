// sLoggerClientDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <chrono>

#define SLOGGERSTATIC
#include <Logger.h>
#pragma comment(lib, "slogger-static.lib")

int main()
{
	sLogger::Initialize();

	int i = 10000;
	while (i--)
	{
		sLogger::LogA(sLogger::eLogLvl_Debug, "sLogger::LogA", "This is %s, number is: %d", "MainFunction", 1002);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		sLogger::LogW(sLogger::eLogLvl_Release, L"sLogger::LogW", L"÷–Œƒ≤‚ ‘ is %s, number is: %d", L"MainFunction", 2342);
	}

    return 0;
}

