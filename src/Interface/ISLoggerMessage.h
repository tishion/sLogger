#pragma once
#include <vector>
#include <memory>

/// <summary>
/// Declare property
/// </summary>
#define DECLARE_PROPERTY(Type, Name)				\
public:												\
	virtual void Set##Name(const Type& value) = 0;	\
	virtual Type Get##Name() const = 0;


/// <summary>
/// The interface of log message.
/// </summary>
class ISLoggerMessage
{
public:
	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~ISLoggerMessage(void) {};

	/// <summary>
	/// Time stamp.
	/// </summary>
	DECLARE_PROPERTY(int64_t, TimeStamp);

	/// <summary>
	/// Tick count.
	/// </summary>
	DECLARE_PROPERTY(uint32_t, TickCount);

	/// <summary>
	/// Log level.
	/// </summary>
	DECLARE_PROPERTY(uint32_t, LogLevel);

	/// <summary>
	/// Process ID.
	/// </summary>
	DECLARE_PROPERTY(uint32_t, ProcessId);

	/// <summary>
	/// Thread ID.
	/// </summary>
	DECLARE_PROPERTY(uint32_t, ThreadId);

	/// <summary>
	/// Log filter Utf16 string.
	/// </summary>
	DECLARE_PROPERTY(std::wstring, LogFilter);

	/// <summary>
	/// Log text utf16 string.
	/// </summary>
	DECLARE_PROPERTY(std::wstring, LogText);

	/// <summary>
	/// Formats the log message as UTF-16 string.
	/// </summary>
	/// <returns>The log message string.</returns>
	virtual std::wstring FormatLogMessage() = 0;

	/// <summary>
	/// Deserializes the bytes array data to message object.
	/// </summary>
	/// <param name="buffer">The bytes array buffer.</param>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool FromBytesArray(const std::vector<uint8_t>& buffer) = 0;

	/// <summary>
	/// Serializes the message object to bytes array.
	/// </summary>
	/// <param name="buffer">The bytes array buffer to recieve the data.</param>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool ToBytesArray(std::vector<uint8_t>& buffer) const = 0;
};

/// <summary>
/// The smart pointer of <see cref="ISLoggerMessage" />.
/// </summary>
typedef std::shared_ptr<ISLoggerMessage> SLoggerMessagePtr;