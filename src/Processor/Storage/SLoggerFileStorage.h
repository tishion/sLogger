#pragma once
#include "../../Interface/ISLogMessageProcessor.h"

/* This is the design of the binary storage file. */
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
/// The log message file storage.
/// </summary>
class CSLoggerFileStorage : public ISLogMessageProcessor
{
private:
	///// <summary>
	///// The magic number of the binary file.
	///// </summary>
	//static const int32_t SLoggerFileMagicNumber = 'SLOG';

	///// <summary>
	///// The header of binary file.
	///// </summary>
	//typedef struct _tagSLoggerFileHeader
	//{
	//	/// <summary>
	//	/// The magic number.
	//	/// </summary>
	//	__int32		magic;

	//	/// <summary>
	//	/// The version.
	//	/// </summary>
	//	__int32		ver;

	//	/// <summary>
	//	/// Reserved fields.
	//	/// </summary>
	//	__int32		reserved0;
	//	__int32		reserved1;
	//	__int32		reserved2;
	//	__int32		reserved3;
	//	__int32		reserved4;
	//	__int32		reserved5;

	//	_tagSLoggerFileHeader()
	//	{
	//		magic = CSLoggerFileStorage::SLoggerFileMagicNumber;
	//		ver = 0;
	//		reserved0 = 0;
	//		reserved1 = 0;
	//		reserved2 = 0;
	//		reserved3 = 0;
	//		reserved4 = 0;
	//		reserved5 = 0;
	//	}

	//	~_tagSLoggerFileHeader()
	//	{
	//		magic = 0;
	//		ver = 0;
	//		reserved0 = 0;
	//		reserved1 = 0;
	//		reserved2 = 0;
	//		reserved3 = 0;
	//		reserved4 = 0;
	//		reserved5 = 0;
	//	}
	//} SLoggerFileHeader, *PSLoggerFileHeader;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	CSLoggerFileStorage(void);

	/// <summary>
	/// Destructor.
	/// </summary>
	~CSLoggerFileStorage(void);

	/// <summary>
	/// Initializes the processor.
	/// </summary>
	///	<param name="parameter">The folder path to save the log file.</param>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool Initialize(const SLUtf8String& parameter);

	/// <summary>
	/// Initializes the processor.
	/// </summary>
	/// <returns>True if successful; otherwise false.</returns>
	virtual bool UnInitialize(void);

	/// <summary>
	/// Save the log message to the file.
	/// </summary>
	/// <param name="msg">The log message.</param>
	virtual void ProcessLogMessage(const SLoggerMessagePtr& msg);

protected:
#if defined(_WIN32)
	/// <summary>
	/// Appends the content to the file.
	/// </summary>
	/// <param name="hFile">The file handle.</param>
	/// <param name="pData">The pointer to the data buffer.</param>
	/// <param name="dwBytesToWrite">The size to write.</param>
	/// <returns>True if successful; otherwise false.</returns>
	bool AppendToFile(HANDLE hFile, LPCVOID pData, DWORD dwBytesToWrite);
#endif

private:
	///// <summary>
	///// The header for binary file.
	///// </summary>
	//SLoggerFileHeader	m_Header;

#if defined(_WIN32)
	///// <summary>
	///// The file handle of binary file.
	///// </summary>
	//HANDLE m_hBinaryFile;

	/// <summary>
	/// The file handle of text file.
	/// </summary>
	HANDLE m_hTextFile;
#endif
};

