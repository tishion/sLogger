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
	int i = 10000;
	while (i--)
	{
		sLogger::LogA(sLogger::eLogLvl_Debug, "MainTest", "This is %s, number is: %d", "MainFunction", 1002);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

    return 0;
}

