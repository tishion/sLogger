#pragma once
#include <atlcoll.h>
#include <atlsync.h>

class SLogMessageManager 
{
public:
	static SLogMessageManager& GetInstance();

protected:
	SLogMessageManager();

	~SLogMessageManager();

public:

	DWORD	Append(const SLoggerMessagePtr& pLogMsg);

	VOID	Remove(DWORD nIndex);
	
	VOID	Clear();

	const SLoggerMessagePtr Get(DWORD nIndex);

private:
	CAtlArray<SLoggerMessagePtr>	m_list;

	CCriticalSection				m_cs;
};

