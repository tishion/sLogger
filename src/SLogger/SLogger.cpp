#include "stdafx.h"
#include <process.h>
#include <thread>

#include "SLogger.h"
#include "../Message/SLoggerMessage.h"
#include "../Processor/Output/SLoggerSystemOutput.h"
#include "../Processor/Sender/SLoggerSender.h"
#include "../Processor/Storage/SLoggerFileStorage.h"

CSLogger& CSLogger::getInstance()
{
	static CSLogger s_instance;
	return s_instance;
}

CSLogger::CSLogger(void)
{
	Initialize();
}

CSLogger::~CSLogger(void)
{
	Uninitialize();
}

bool CSLogger::Initialize()
{
	m_nPid = _getpid();

	SLogMessageProcessorPtr pProcessor;
	pProcessor = std::make_shared<CSLoggerSystemOutput>();
	pProcessor->Initialize("");
	m_processorList.push_back(pProcessor);

	pProcessor = std::make_shared<CSLoggerSender>();
	pProcessor->Initialize("");
	m_processorList.push_back(pProcessor);

	pProcessor = std::make_shared<CSLoggerFileStorage>();
	pProcessor->Initialize("");
	m_processorList.push_back(pProcessor);

	return true;
}

void CSLogger::Log(int nLevel, const SLUtf16String& strFilter, const SLUtf16String& strText)
{
	std::shared_ptr<CSLoggerMessage> msg = std::make_shared<CSLoggerMessage>();

#if defined(_WIN32)
	msg->SetThreadId(::GetCurrentThreadId());
	msg->SetTickCount(::GetTickCount());
#endif

	msg->SetProcessId(m_nPid);
	msg->SetTimeStamp(std::time(nullptr));
	msg->SetLogLevel(nLevel);
	msg->SetLogFilter(strFilter);
	msg->SetLogText(strText);


	for (auto const p : m_processorList)
		p->ProcessLogMessage(msg);
}

void CSLogger::Uninitialize()
{
	for (auto const p : m_processorList)
		p->UnInitialize();

	m_processorList.clear();
}
