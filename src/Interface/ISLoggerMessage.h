#pragma once
#include <vector>
#include <memory>

#define DECLARE_PROPERTY(Type, Name)				\
public:												\
	virtual void Set##Name(const Type& value) = 0;	\
	virtual Type Get##Name() const = 0;


/// <summary>
/// 
/// </summary>
class ISLoggerMessage
{
public:
	/// <summary>
	/// 
	/// </summary>
	virtual ~ISLoggerMessage(void) {};

	// Time stamp
	DECLARE_PROPERTY(int64_t, TimeStamp);

	// Tick count
	DECLARE_PROPERTY(uint32_t, TickCount);

	// Log level
	DECLARE_PROPERTY(uint32_t, LogLevel);

	// Process ID
	DECLARE_PROPERTY(uint32_t, ProcessId);

	// Thread ID
	DECLARE_PROPERTY(uint32_t, ThreadId);

	// Log filter Utf16 string
	DECLARE_PROPERTY(std::wstring, LogFilter);

	// Log text utf16 string
	DECLARE_PROPERTY(std::wstring, LogText);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual std::wstring FormatLogMessage() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="buffer"></param>
	/// <returns></returns>
	virtual bool FromBytesArray(const std::vector<uint8_t>& buffer) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="buffer"></param>
	/// <returns></returns>
	virtual bool ToBytesArray(std::vector<uint8_t>& buffer) const = 0;
};

/// <summary>
/// 
/// </summary>
typedef std::shared_ptr<ISLoggerMessage> SLoggerMessagePtr;