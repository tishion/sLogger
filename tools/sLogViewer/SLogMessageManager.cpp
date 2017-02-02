#include "stdafx.h"
#include "SLogMessageManager.h"

SLogMessageManager::SLogMessageManager()
{
	Clear();
}

SLogMessageManager::~SLogMessageManager()
{
	Clear();
}

SLogMessageManager& SLogMessageManager::GetInstance()
{
	static SLogMessageManager s_instance;
	return s_instance;
}

DWORD SLogMessageManager::Append(const SLoggerMessagePtr& pLogMsg)
{
	DWORD nIndex = 0;
	m_cs.Enter();
	nIndex =m_list.Add(pLogMsg);
	m_cs.Leave();
	return nIndex;
}

VOID SLogMessageManager::Remove(DWORD nIndex)
{
	m_cs.Enter();
	m_list.RemoveAt(nIndex);
	m_cs.Leave();
}

VOID SLogMessageManager::Clear()
{
	m_cs.Enter();
	m_list.RemoveAll();
	m_cs.Leave();
}

const SLoggerMessagePtr SLogMessageManager::Get(DWORD nIndex)
{
	SLoggerMessagePtr pMsgLog;
	m_cs.Enter();
	pMsgLog = m_list.GetAt(nIndex);
	m_cs.Leave();
	return pMsgLog;
}
