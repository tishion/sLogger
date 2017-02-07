#pragma once

#include "../common.h"
#include "../Interface/ISLogMessageProcessor.h"

/// <summary>
/// The logger object.
/// </summary>
class CSLogger
{
public:
	/// <summary>
	/// The log level.
	/// </summary>
	enum LogLevel
	{
		eLogLvl_Debug = 0,
		eLogLvl_Release,
	};

	/// <summary>
	/// Gets the instance of the logger object.
	/// </summary>
	/// <returns>The reference of the logger instance.</returns>
	static CSLogger& getInstance();

	/// <summary>
	/// Logs the message.
	/// </summary>
	/// <param name="nLevel">The log level.</param>
	/// <param name="strFilter">The log filter.</param>
	/// <param name="strText">The log text content.</param>
	void Log(int nLevel, const SLUtf16String& strFilter, const SLUtf16String& strText);

	/// <summary>
	/// Initializes the logger.
	/// </summary>
	/// <returns>True if successful; otherwise false.</returns>
	bool Initialize(const SLUtf8String& parameter = "");

	/// <summary>
	/// Unintializes the logger.
	/// </summary>
	void Uninitialize();

protected:
	/// <summary>
	/// Constructor.
	/// </summary>
	CSLogger(void);

	/// <summary>
	/// Destructor.
	/// </summary>
	~CSLogger(void);

private:
	/// <summary>
	/// The process id.
	/// </summary>
	int					m_nPid;

	/// <summary>
	/// The processor list.
	/// </summary>
	SLogMessageProcessorList m_processorList;
};