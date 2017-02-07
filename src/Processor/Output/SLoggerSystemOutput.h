#pragma once
#include "../../Interface/ISLogMessageProcessor.h"

/// <summary>
/// The log message output.
/// </summary>
class CSLoggerSystemOutput : public ISLogMessageProcessor
{
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	CSLoggerSystemOutput(void);

	/// <summary>
	/// Destructor.
	/// </summary>
	~CSLoggerSystemOutput(void);

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
	virtual bool UnInitialize(void);

	/// <summary>
	/// Output the log message to system debug buffer.
	/// </summary>
	/// <param name="msg">The log message.</param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg);
};

