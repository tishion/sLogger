#pragma once
#include "../../Interface/ISLogMessageProcessor.h"

/* Header
 * /-------------------\
 * | MagicNo: int32	   |
 * |-------------------|		   /--------------\	
 * | VersionNo:	int32  |		 / | Length:int32 |
 * |-------------------|		/  |--------------|
 * |Chunk[0]		   |-------|   | Data: xxxxxx |
 * |-------------------|		\  |--------------|
 * |Chunk[1]		   |		 \ | xxxxxxxxxxxx |
 * |-------------------|		   \--------------/
 * |Chunk[2]		   |			
 * |-------------------|
 */

/// <summary>
/// 
/// </summary>
class CSLoggerFileStorage : public ISLogMessageProcessor
{
private:
	/// <summary>
	/// 
	/// </summary>
	static const int32_t SLoggerFileMagicNumber = 'SLOG';

	/// <summary>
	/// 
	/// </summary>
	typedef struct _tagSLoggerFileHeader
	{
		__int32		magic;
		__int32		ver;
		__int32		reserved0;
		__int32		reserved1;
		__int32		reserved2;
		__int32		reserved3;
		__int32		reserved4;
		__int32		reserved5;

		_tagSLoggerFileHeader()
		{
			magic = CSLoggerFileStorage::SLoggerFileMagicNumber;
			ver = 0;
			reserved0 = 0;
			reserved1 = 0;
			reserved2 = 0;
			reserved3 = 0;
			reserved4 = 0;
			reserved5 = 0;
		}

		~_tagSLoggerFileHeader()
		{
			magic = 0;
			ver = 0;
			reserved0 = 0;
			reserved1 = 0;
			reserved2 = 0;
			reserved3 = 0;
			reserved4 = 0;
			reserved5 = 0;
		}

	} SLoggerFileHeader, *PSLoggerFileHeader;

public:
	/// <summary>
	/// 
	/// </summary>
	CSLoggerFileStorage(void);

	/// <summary>
	/// 
	/// </summary>
	~CSLoggerFileStorage(void);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="logFileName"></param>
	/// <returns></returns>
	virtual bool Initialize(const SLUtf8String& parameter);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool UnInitialize(void);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="msg"></param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg);

protected:
#if defined(_WIN32)
	bool AppendToFile(HANDLE hFile, LPCVOID pData, DWORD dwBytesToWrite);
#endif

private:
	/// <summary>
	/// 
	/// </summary>
	SLoggerFileHeader	m_Header;

#if defined(_WIN32)
	///// <summary>
	///// 
	///// </summary>
	//HANDLE m_hBinaryFile;

	/// <summary>
	/// 
	/// </summary>
	HANDLE m_hTextFile;
#endif
};

