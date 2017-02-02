#pragma once

#include "../../Interface/ISLogMessageProcessor.h"

/// <summary>
/// 
/// </summary>
class CSLoggerSender : public ISLogMessageProcessor
{
public:
	/// <summary>
	/// 
	/// </summary>
	CSLoggerSender(void);
	
	/// <summary>
	/// 
	/// </summary>
	~CSLoggerSender(void);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool Initialize(const SLUtf8String& parameter);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool UnInitialize();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="msg"></param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg);
};

