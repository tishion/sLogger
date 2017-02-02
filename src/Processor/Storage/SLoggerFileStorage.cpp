#include "stdafx.h"
#include "SLoggerFileStorage.h"

CSLoggerFileStorage::CSLoggerFileStorage(void)
{
}

CSLoggerFileStorage::~CSLoggerFileStorage(void)
{
}

bool CSLoggerFileStorage::Initialize(const SLUtf8String& logFileName)
{
	return true;
}

bool CSLoggerFileStorage::UnInitialize()
{
	return true;
}

void CSLoggerFileStorage::ProcessLogMessage(const SLoggerMessagePtr& msg)
{
	if (!msg) return;

#if !defined(DEBUG) && !defined(_DEBUG)
	if (msg->GetLogLevel() <= eLogLvl_Debug) return;
#endif

	std::vector<uint8_t> buffer;
	msg->ToBytesArray(buffer);
}
