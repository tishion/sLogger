#pragma once
#include "../../Interface/ISLogMessageProcessor.h"

/// <summary>
/// The log message sender.
/// </summary>
class CSLoggerSender : public ISLogMessageProcessor
{
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	CSLoggerSender(void);
	
	/// <summary>
	/// Destructor.
	/// </summary>
	~CSLoggerSender(void);

	/// <summary>
	/// Initializes the processor.
	/// </summary>
	///	<param name="parameter">The string parameter.</param>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool Initialize(const SLUtf8String& parameter);

	/// <summary>
	/// Initializes the processor.
	/// </summary>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool UnInitialize();

	/// <summary>
	/// Send the log message to the log viewer.
	/// </summary>
	/// <param name="msg">The log message.</param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg);
};

