#pragma once

#include "../common.h"
#include "../Interface/ISLogMessageProcessor.h"

/// <summary>
/// 
/// </summary>
class CSLogger
{
public:
	/// <summary>
	/// 
	/// </summary>
	enum LogLevel
	{
		eLogLvl_Debug = 0,
		eLogLvl_Release,
	};

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static CSLogger& getInstance();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="nLevel"></param>
	/// <param name="strFilter"></param>
	/// <param name="strText"></param>
	void Log(int nLevel, const SLUtf16String& strFilter, const SLUtf16String& strText);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool Initialize(const SLUtf8String& parameter = "");

	/// <summary>
	/// 
	/// </summary>
	void Uninitialize();

protected:
	/// <summary>
	/// 
	/// </summary>
	CSLogger(void);

	/// <summary>
	/// 
	/// </summary>
	~CSLogger(void);

private:
	/// <summary>
	/// 
	/// </summary>
	int					m_nPid;

	/// <summary>
	/// 
	/// </summary>
	SLogMessageProcessorList m_processorList;
};