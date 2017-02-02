#pragma once
#include "../../Interface/ISLogMessageProcessor.h"

/// <summary>
/// 
/// </summary>
class CSLoggerSystemOutput : public ISLogMessageProcessor
{
public:
	/// <summary>
	/// 
	/// </summary>
	CSLoggerSystemOutput(void);

	/// <summary>
	/// 
	/// </summary>
	~CSLoggerSystemOutput(void);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool Initialize(const SLUtf8String& parameter);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool UnInitialize(void);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="msg"></param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg);
};

