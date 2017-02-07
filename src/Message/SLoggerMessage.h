#pragma once

#include "../Interface/ISLoggerMessage.h"

// Implements property
#define IMPLEMENT_PROPERTY(Type, Name)						\
protected:													\
	Type m_##Name;											\
public:														\
	void Set##Name(const Type& value) { m_##Name = value; }	\
	Type Get##Name() const { return m_##Name; }

/// <summary>
/// The log message object.
/// </summary>
class CSLoggerMessage : public ISLoggerMessage
{
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	CSLoggerMessage(void);
	
	/// <summary>
	/// Destructor.
	/// </summary>
	~CSLoggerMessage(void);

	/// <summary>
	/// Time stamp.
	/// </summary>
	IMPLEMENT_PROPERTY(int64_t, TimeStamp);

	/// <summary>
	/// Tick count.
	/// </summary>
	IMPLEMENT_PROPERTY(uint32_t, TickCount);

	/// <summary>
	/// Log level.
	/// </summary>
	IMPLEMENT_PROPERTY(uint32_t, LogLevel);

	/// <summary>
	/// Process ID.
	/// </summary>
	IMPLEMENT_PROPERTY(uint32_t, ProcessId);

	/// <summary>
	/// Thread ID.
	/// </summary>
	IMPLEMENT_PROPERTY(uint32_t, ThreadId);
	
	/// <summary>
	/// Log filter Utf16 string.
	/// </summary>
	IMPLEMENT_PROPERTY(std::wstring, LogFilter);
	/// <summary>
	/// Log text utf16 string.
	/// </summary>
	IMPLEMENT_PROPERTY(std::wstring, LogText);

	/// <summary>
	/// Formats the log message as UTF-16 string.
	/// </summary>
	/// <returns>The log message string.</returns>
	virtual std::wstring FormatLogMessage() override;

	/// <summary>
	/// Deserializes the bytes array data to message object.
	/// </summary>
	/// <param name="buffer">The bytes array buffer.</param>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool FromBytesArray(const std::vector<uint8_t>& buffer) override;

	/// <summary>
	/// Serializes the message object to bytes array.
	/// </summary>
	/// <param name="buffer">The bytes array buffer to recieve the data.</param>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool ToBytesArray(std::vector<uint8_t>& buffer) const override;
};
