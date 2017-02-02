#include "stdafx.h"
#include "SLoggerSystemOutput.h"

CSLoggerSystemOutput::CSLoggerSystemOutput(void)
{
}

CSLoggerSystemOutput::~CSLoggerSystemOutput(void)
{
}

bool CSLoggerSystemOutput::Initialize(const SLUtf8String& parameter)
{
	return true;
}

bool CSLoggerSystemOutput::UnInitialize()
{
	return true;
}

void CSLoggerSystemOutput::ProcessLogMessage(const SLoggerMessagePtr& msg)
{
	if (!msg) return;

#if defined(_WIN32)
	std::wstring message = msg->FormatLogMessage();
	::OutputDebugStringW(message.c_str());
#endif
}
