#pragma once
#include "../common.h"
#include "ISLoggerMessage.h"

/// <summary>
/// The inferface of log message processor.
/// </summary>
class ISLogMessageProcessor
{
public:
	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~ISLogMessageProcessor(void) {};

	/// <summary>
	/// Initializes the processor.
	/// </summary>
	/// <param name="parameter">The parameter.</param>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool Initialize(const SLUtf8String& parameter) = 0;
	
	/// <summary>
	/// Uninitializes the processor.
	/// </summary>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool UnInitialize(void) = 0;

	/// <summary>
	/// Processes the log message.
	/// </summary>
	/// <param name="msg">The log message object.</param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg) = 0;
};

/// <summary>
/// Smart pointer of <see cref="ISLogMessageProcessor" />.
/// </summary>
typedef std::shared_ptr<ISLogMessageProcessor> SLogMessageProcessorPtr;

/// <summary>
/// The processor list type.
/// </summary>
typedef std::vector<SLogMessageProcessorPtr> SLogMessageProcessorList;