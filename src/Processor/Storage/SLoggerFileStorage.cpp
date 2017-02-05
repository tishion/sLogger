#include "stdafx.h"
#include "SLoggerFileStorage.h"

CSLoggerFileStorage::CSLoggerFileStorage(void)
{
}

CSLoggerFileStorage::~CSLoggerFileStorage(void)
{
}

bool CSLoggerFileStorage::Initialize(const SLUtf8String& parameter)
{
#if defined(_WIN32)
	CAtlStringW exeFilePath;
	::GetModuleFileNameW(NULL, exeFilePath.GetBuffer(MAX_PATH), MAX_PATH);
	exeFilePath.ReleaseBuffer();

	if (!parameter.empty())
	{
		CAtlStringW logFolderPath = CA2W(parameter.c_str(), CP_UTF8);
		auto pFileName = ::PathFindFileNameW(exeFilePath);
		::PathCombine(exeFilePath.GetBuffer(MAX_PATH), logFolderPath, pFileName);
		exeFilePath.ReleaseBuffer();
	}

	//CAtlStringW binaryFilePath = exeFilePath + L".slg";
	//m_hBinaryFile = ::CreateFileW(binaryFilePath, FILE_APPEND_DATA,
	//	FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	//if (INVALID_HANDLE_VALUE == m_hBinaryFile || NULL == m_hBinaryFile)
	//{
	//	m_hBinaryFile = NULL;
	//	return false;
	//}

	CAtlStringW textFilePath = exeFilePath + L".log";
	m_hTextFile = ::CreateFileW(textFilePath, FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (INVALID_HANDLE_VALUE == m_hTextFile || NULL == m_hTextFile)
	{
		//::CloseHandle(m_hBinaryFile);
		//m_hBinaryFile = NULL;
		m_hTextFile = NULL;
		return false;
	}

#endif
	return true;
}

bool CSLoggerFileStorage::UnInitialize()
{
#if defined(_WIN32)
	//if (m_hBinaryFile)
	//	::CloseHandle(m_hBinaryFile);

	if (m_hTextFile)
		::CloseHandle(m_hTextFile);
#endif
	return true;
}

void CSLoggerFileStorage::ProcessLogMessage(const SLoggerMessagePtr& msg)
{
	if (!msg) return;

#if !defined(DEBUG) && !defined(_DEBUG)
	// For non-debug version, we don't save the debug log message into file
	if (msg->GetLogLevel() <= 0) return;
#endif

	//if (m_hBinaryFile)
	//{
	//	//std::vector<uint8_t> buffer;
	//	//msg->ToBytesArray(buffer);
	//}

	if (m_hTextFile)
	{
		auto logMessage = msg->FormatLogMessage();
		SLUtf16StringConvert Utf16StringConvert;
		auto utf8LogMessage = Utf16StringConvert.to_bytes(logMessage);
		AppendToFile(m_hTextFile, utf8LogMessage.data(), utf8LogMessage.size());
	}
}

#if defined(_WIN32)
bool CSLoggerFileStorage::AppendToFile(HANDLE hFile, LPCVOID pData, DWORD dwBytesToWrite)
{
	DWORD dwNumberOfBytesWritten = 0;
	DWORD dwNumberOfBytesToWrite = dwBytesToWrite;

	static OVERLAPPED overlapped = { 0, -1, 0 };
	::LockFileEx(hFile, LOCKFILE_EXCLUSIVE_LOCK, 0, -1, -1, &overlapped);
	do
	{
		if (!::WriteFile(hFile, pData, dwBytesToWrite, &dwNumberOfBytesWritten, NULL))
			break;

		dwNumberOfBytesToWrite -= dwNumberOfBytesWritten;
	} while (dwNumberOfBytesToWrite > 0);
	::UnlockFileEx(hFile, 0, -1, -1, &overlapped);

	return dwNumberOfBytesToWrite == 0;
}
#endif
