#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// For building of dynamic module
#if defined(SLOGGERDYNAMIC)
#if defined(SLOGGERDYNAMIC_EXPORTS)
#define SLOGGER_API __declspec(dllexport)
#else
#define SLOGGER_API __declspec(dllimport)
#endif
#endif

// For building of using of static module
#if defined(SLOGGERSTATIC)
#define SLOGGER_API
#endif

/// <summary>
/// The sLogger namespace.
/// </summary>
namespace sLogger
{
	/// <summary>
	/// The log levels.
	/// </summary>
	enum LOG_LEVEL
	{
		/// <summary>
		/// The debug log level.
		/// </summary>
		eLogLvl_Debug = 0,

		/// <summary>
		/// The release log level.
		/// </summary>
		eLogLvl_Release,
	};

	/// <summary>
	/// Initializes the logger.
	/// </summary>
	/// <param name="parameter"></param>
	/// <returns></returns>
	bool SLOGGER_API Initialize(const std::string& parameter = "");

	/// <summary>
	/// Logs UTF-8 message.
	/// </summary>
	/// <param name="nLevel">The log level.</param>
	/// <param name="strFilter">The log filter in UTF-8 string.</param>
	/// <param name="strFormat">The format in UTF-8 string.</param>
	void SLOGGER_API LogA(int nLevel, const std::string& strFilter, const std::string strFormat, ...);

	/// <summary>
	/// Logs UTF-16 message.
	/// </summary>
	/// <param name="nLevel">The log level.</param>
	/// <param name="strFilter">The log filter in UTF-16 string.</param>
	/// <param name="strFormat">The format in UTF-16 string.</param>
	void SLOGGER_API LogW(int nLevel, const std::wstring& strFilter, const std::wstring strFormat, ...);
	
	/// <summary>
	/// Logs UTF-8 message.
	/// </summary>
	/// <param name="nLevel">The log level.</param>
	/// <param name="strFilter">The log filter in UTF-8 string.</param>
	/// <param name="strFormat">The log text content in UTF-8 string.</param>
	void SLOGGER_API LogA(int nLevel, const std::string& strFilter, const std::string& strText);

	/// <summary>
	/// Logs UTF-16 message.
	/// </summary>
	/// <param name="nLevel">The log level.</param>
	/// <param name="strFilter">The log filter in UTF-16 string.</param>
	/// <param name="strFormat">The log text content int UTF-16 string.</param>
	void SLOGGER_API LogW(int nLevel, const std::wstring& strFilter, const std::wstring& strText);

	/// <summary>
	/// Logs UTF-8 message.
	/// </summary>
	/// <param name="nLevel">The log level.</param>
	/// <param name="strFilter">The log filter in UTF-8 string.</param>
	/// <param name="strFormat">The log text content int UTF-8 string stream.</param>
	void SLOGGER_API LogA(int nLevel, const std::string& strFilter, const std::ostringstream& strText);

	/// <summary>
	/// Logs UTF-16 message.
	/// </summary>
	/// <param name="nLevel">The log level.</param>
	/// <param name="strFilter">The log filter in UTF-8 string.</param>
	/// <param name="strFormat">The log text content int UTF-16 string stream.</param>
	void SLOGGER_API LogW(int nLevel, const std::wstring& strFilter, const std::wostringstream& strText);
};

/*
 * Log Macros
 *		use log macros rather than log functions
 */

/// <summary>
/// 
/// </summary>
#define SLogDA(filter, format, ...)	sLogger::LogA(sLogger::eLogLvl_Debug, filter, format, ##__VA_ARGS__)

/// <summary>
/// 
/// </summary>
#define SLogDW(filter, format, ...)	sLogger::LogW(sLogger::eLogLvl_Debug, filter, format, ##__VA_ARGS__)

/// <summary>
/// 
/// </summary>
#define SLogRA(filter, format, ...)	sLogger::LogA(sLogger::eLogLvl_Release, filter, format, ##__VA_ARGS__)

/// <summary>
/// 
/// </summary>
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