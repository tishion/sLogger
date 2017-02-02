#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#if defined(SLOGGERDYNAMIC)
#if defined(SLOGGERDYNAMIC_EXPORTS)
#define SLOGGER_API __declspec(dllexport)
#else
#define SLOGGER_API __declspec(dllimport)
#endif
#endif

#if defined(SLOGGERSTATIC)
#define SLOGGER_API
#endif

namespace sLogger
{
	enum LOG_LEVEL
	{
		eLogLvl_Debug = 0,
		eLogLvl_Release,
	};

	void SLOGGER_API LogA(int nLevel, const std::string& strFilter, const std::string strFormat, ...);
	
	void SLOGGER_API LogW(int nLevel, const std::wstring& strFilter, const std::wstring strFormat, ...);
	
	void SLOGGER_API LogA(int nLevel, const std::string& strFilter, const std::string& strText);

	void SLOGGER_API LogW(int nLevel, const std::wstring& strFilter, const std::wstring& strText);

	void SLOGGER_API LogA(int nLevel, const std::string& strFilter, const std::ostringstream& strText);

	void SLOGGER_API LogW(int nLevel, const std::wstring& strFilter, const std::wostringstream& strText);
};

/*
 * Log Macros
 *		use log macros rather than log functions
 */
#define SLogDA(filter, format, ...)	sLogger::LogA(sLogger::eLogLvl_Debug, filter, format, ##__VA_ARGS__)

#define SLogDW(filter, format, ...)	sLogger::LogW(sLogger::eLogLvl_Debug, filter, format, ##__VA_ARGS__)

#define SLogRA(filter, format, ...)	sLogger::LogA(sLogger::eLogLvl_Release, filter, format, ##__VA_ARGS__)

#define SLogRW(filter, format, ...)	sLogger::LogW(sLogger::eLogLvl_Release, filter, format, ##__VA_ARGS__)

/*
* Output log string with RELEASE level
* This macro can use variable number of arguments.
*/
//#if defined(_UNICODE) || defined(UNICODE)
//#define SLogD	SLogDW
//#define SLogR	SLogRW
//#else
//#define SLogD	SLogDA
//#define SLogR	SLogRA
//#endif

#endif