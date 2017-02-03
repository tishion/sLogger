#include "stdafx.h"
#include "common.h"
#include "Include/Logger.h"
#include "SLogger/SLogger.h"

static SLUtf16StringConvert s_SLUtf16StringConvert;

bool SLOGGER_API sLogger::Initialize(const std::string& parameter)
{
	return CSLogger::getInstance().Initialize(parameter);
}

void SLOGGER_API sLogger::LogA(int nLevel, const std::string& strFilter, const std::string strFormat, ...)
{
	if (strFormat.empty())
		return;

	va_list arglist;
	char szText[LOG_STRING_MAX_LEN] = { 0 };
	int nBufLen = -1;

	va_start(arglist, strFormat);
	nBufLen = vsprintf_s((char*)szText, LOG_STRING_MAX_LEN, strFormat.c_str(), arglist);
	va_end(arglist);
	if (nBufLen <= 0)
		return;

	SLUtf16String strFlt = s_SLUtf16StringConvert.from_bytes(strFilter);
	SLUtf16String strText = s_SLUtf16StringConvert.from_bytes(szText);

	CSLogger::getInstance().Log(nLevel, strFlt, strText);
}

void SLOGGER_API sLogger::LogW(int nLevel, const std::wstring& strFilter, const std::wstring strFormat, ...)
{
	if (strFormat.empty())
		return;

	va_list arglist;
	wchar_t wszText[LOG_STRING_MAX_LEN] = { 0 };
	int nBufLen = -1;

	va_start(arglist, strFormat);
	nBufLen = vswprintf_s((wchar_t *)wszText, LOG_STRING_MAX_LEN, strFormat.c_str(), arglist);
	va_end(arglist);
	if (nBufLen <= 0)
		return;

	SLUtf16String strText = wszText;

	CSLogger::getInstance().Log(nLevel, strFilter, strText);
}

void SLOGGER_API sLogger::LogA(int nLevel, const std::string& strFilter, const std::string& strText)
{
	SLUtf16String filter = s_SLUtf16StringConvert.from_bytes(strFilter);
	SLUtf16String text = s_SLUtf16StringConvert.from_bytes(strText);

	CSLogger::getInstance().Log(nLevel, filter, text);
}

void SLOGGER_API sLogger::LogW(int nLevel, const std::wstring& strFilter, const std::wstring& strText)
{
	CSLogger::getInstance().Log(nLevel, strFilter, strText);
}

void SLOGGER_API sLogger::LogA(int nLevel, const std::string& strFilter, const std::ostringstream& strText)
{
	SLUtf16String filter = s_SLUtf16StringConvert.from_bytes(strFilter);
	SLUtf16String text = s_SLUtf16StringConvert.from_bytes(strText.str());

	CSLogger::getInstance().Log(nLevel, filter, text);
}

void SLOGGER_API sLogger::LogW(int nLevel, const std::wstring& strFilter, const std::wostringstream& strText)
{
	CSLogger::getInstance().Log(nLevel, strFilter, strText.str());
}