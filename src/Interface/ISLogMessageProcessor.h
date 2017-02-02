#pragma once
#include "../common.h"
#include "ISLoggerMessage.h"

/// <summary>
/// 
/// </summary>
class ISLogMessageProcessor
{
public:
	/// <summary>
	/// 
	/// </summary>
	virtual ~ISLogMessageProcessor(void) {};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="parameter"></param>
	/// <returns></returns>
	virtual bool Initialize(const SLUtf8String& parameter) = 0;
	
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool UnInitialize(void) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="msg"></param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg) = 0;
};

/// <summary>
/// 
/// </summary>
typedef std::shared_ptr<ISLogMessageProcessor> SLogMessageProcessorPtr;

/// <summary>
/// 
/// </summary>
typedef std::vector<SLogMessageProcessorPtr> SLogMessageProcessorList;