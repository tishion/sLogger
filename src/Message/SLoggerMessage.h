#pragma once

#include "../Interface/ISLoggerMessage.h"

#define IMPLEMENT_PROPERTY(Type, Name)						\
protected:													\
	Type m_##Name;											\
public:														\
	void Set##Name(const Type& value) { m_##Name = value; }	\
	Type Get##Name() const { return m_##Name; }

/// <summary>
/// 
/// </summary>
class CSLoggerMessage : public ISLoggerMessage
{
public:
	/// <summary>
	/// 
	/// </summary>
	CSLoggerMessage(void);
	
	/// <summary>
	/// 
	/// </summary>
	~CSLoggerMessage(void);

	// Time stamp
	IMPLEMENT_PROPERTY(int64_t, TimeStamp);

	// Tick count
	IMPLEMENT_PROPERTY(uint32_t, TickCount);

	// Log level
	IMPLEMENT_PROPERTY(uint32_t, LogLevel);

	// Process ID
	IMPLEMENT_PROPERTY(uint32_t, ProcessId);

	// Thread ID
	IMPLEMENT_PROPERTY(uint32_t, ThreadId);
	
	// Log filter Utf16 string
	IMPLEMENT_PROPERTY(std::wstring, LogFilter);

	// Log text utf16 string
	IMPLEMENT_PROPERTY(std::wstring, LogText);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual std::wstring FormatLogMessage() override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="buffer"></param>
	/// <returns></returns>
	virtual bool FromBytesArray(const std::vector<uint8_t>& buffer) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="buffer"></param>
	/// <returns></returns>
	virtual bool ToBytesArray(std::vector<uint8_t>& buffer) const override;
};
