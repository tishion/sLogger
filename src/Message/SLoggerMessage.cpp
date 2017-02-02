#include "StdAfx.h"
#include <iomanip>
#include "../common.h"
#include "SLoggerMessage.h"

CSLoggerMessage::CSLoggerMessage(void)
{
}

CSLoggerMessage::~CSLoggerMessage(void)
{
}

std::wstring CSLoggerMessage::FormatLogMessage()
{
	SLOUtf16StringStream oss;
	
	char timeStampText[32];
	if (std::strftime(timeStampText, sizeof(timeStampText), "%Y-%m-%d %H:%M:%S", std::localtime(&m_TimeStamp)))
		oss << std::setw(19) << timeStampText << " ";
	else
		oss << std::setw(19) << m_TimeStamp << " ";

	oss << std::setw(10) << std::left << m_TickCount << " ";

	if (0 == m_LogLevel)
		oss << L"DEBUG  " << " ";
	else
		oss << L"RELEASE" << " ";

	oss << std::setw(10) << m_ProcessId << " ";
	oss << std::setw(10) << m_ThreadId << " ";
	oss << m_LogFilter << "  ";
	oss << m_LogText;
	oss << std::endl;

	return oss.str();
}

bool CSLoggerMessage::FromBytesArray(const std::vector<uint8_t>& buffer)
{
	SLUtf16StringConvert Utf16StringConvert;

	m_TimeStamp = 0;
	m_TickCount = 0;
	m_ProcessId = 0;
	m_ThreadId = 0;
	m_LogLevel = 0;

	uint8_t* p = (uint8_t*)buffer.data();
	uint8_t* pLimit = p + buffer.size();

	if (p >= pLimit) return false;
	memcpy(&m_TimeStamp, p, sizeof(m_TimeStamp));
	p += sizeof(m_TimeStamp);

	if (p >= pLimit) return false;
	memcpy(&m_TickCount, p, sizeof(m_TickCount));
	p += sizeof(m_TickCount);

	if (p >= pLimit) return false;
	memcpy(&m_LogLevel, p, sizeof(m_LogLevel));
	p += sizeof(m_LogLevel);

	if (p >= pLimit) return false;
	memcpy(&m_ProcessId, p, sizeof(m_ProcessId));
	p += sizeof(m_ProcessId);

	if (p >= pLimit) return false;
	memcpy(&m_ThreadId, p, sizeof(m_ThreadId));
	p += sizeof(m_ThreadId);

	uint32_t len = 0;

	if (p >= pLimit) return false;
	memcpy(&len, p, sizeof(len));
	p += sizeof(len);

	if (p >= pLimit) return false;
	m_LogFilter = Utf16StringConvert.from_bytes((char*)p, (char*)(p + len));
	p += len;

	if (p >= pLimit) return false;
	memcpy(&len, p, sizeof(len));
	p += sizeof(len);

	if (p >= pLimit) return false;
	m_LogText = Utf16StringConvert.from_bytes((char*)p, (char*)(p + len));
	p += len;

	return true;
}

bool CSLoggerMessage::ToBytesArray(std::vector<uint8_t>& buffer) const
{
	buffer.clear();

	SLUtf16StringConvert Utf16StringConvert;

	int32_t totalSize = 0;
	totalSize += sizeof(m_TimeStamp);
	totalSize += sizeof(m_TickCount);
	totalSize += sizeof(m_LogLevel);
	totalSize += sizeof(m_ProcessId);
	totalSize += sizeof(m_ThreadId);
	totalSize *= 2;

	// Convert to UTF8 string
	auto utf8Filter = Utf16StringConvert.to_bytes(m_LogFilter);
	totalSize += utf8Filter.size();

	// Convert to UTF8 string
	auto utf8Text = Utf16StringConvert.to_bytes(m_LogText);
	totalSize += utf8Text.size();

	buffer.resize(totalSize);
	auto it = buffer.begin();
	uint8_t* p = nullptr;

	// We don't consider about the byte order, because this is not designed for network transfer
	p = (uint8_t*)&m_TimeStamp;
	it = buffer.insert(it, p, p + sizeof(m_TimeStamp));
	it += sizeof(m_TimeStamp);

	p = (uint8_t*)&m_TickCount;
	it = buffer.insert(it, p, p + sizeof(m_TickCount));
	it += sizeof(m_TickCount);

	p = (uint8_t*)&m_LogLevel;
	it = buffer.insert(it, p, p + sizeof(m_LogLevel));
	it += sizeof(m_LogLevel);

	p = (uint8_t*)&m_ProcessId;
	it = buffer.insert(it, p, p + sizeof(m_ProcessId));
	it += sizeof(m_ProcessId);

	p = (uint8_t*)&m_ThreadId;
	it = buffer.insert(it, p, p + sizeof(m_ThreadId));
	it += sizeof(m_ThreadId);

	uint32_t len = 0;

	len = utf8Filter.size();
	p = (uint8_t*)&len;
	it = buffer.insert(it, p, p + sizeof(len));
	it += sizeof(len);

	it = buffer.insert(it, utf8Filter.begin(), utf8Filter.end());
	it += utf8Filter.size();

	len = utf8Text.size();
	p = (uint8_t*)&len;
	it = buffer.insert(it, p, p + sizeof(len));
	it += sizeof(len);

	it = buffer.insert(it, utf8Text.begin(), utf8Text.end());
	it += utf8Filter.size();

	return true;
}
