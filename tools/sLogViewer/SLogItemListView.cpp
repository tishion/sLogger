#include "StdAfx.h"
#include "SLogItemListView.h"
#include "SLogMessageManager.h"

SLogItemListView::SLogItemListView()
{
	m_bAutoScroll = TRUE;
}

SLogItemListView::~SLogItemListView()
{
}

BOOL SLogItemListView::PreTranslateMessage(MSG* pMsg)
{
	UNREFERENCED_PARAMETER(pMsg);
	return FALSE;
}

typedef struct _tagColumn
{
	DWORD	i;
	TCHAR*	n;
	DWORD	w;
	DWORD	f;
} Column, *PColumn;

enum ColumnIndex
{
	eCI_Time = 0,
	eCI_Tick,
	eCI_Level,
	eCI_Pid, 
	eCI_Tid, 
	eCI_Filter, 
	eCI_Message
};

Column ColumnDefine[] = 
{
	{ eCI_Time,		_T("Time"),		120,	LVCFMT_LEFT },
	{ eCI_Tick,		_T("Tick"),		80,		LVCFMT_LEFT },
	{ eCI_Level,	_T("Level"),	80,		LVCFMT_LEFT },
	{ eCI_Pid,		_T("Process"),	80,		LVCFMT_LEFT },
	{ eCI_Tid,		_T("Thread"),	80,		LVCFMT_LEFT },
	{ eCI_Filter,	_T("Filter"),	150,	LVCFMT_LEFT },
	{ eCI_Message,	_T("Message"),	500,	LVCFMT_LEFT },
};

#define InsertColumnMacro(i)	InsertColumn(i, ColumnDefine[i].n, ColumnDefine[i].f, ColumnDefine[i].w)

VOID SLogItemListView::Initialize()
{
	SetExtendedListViewStyle(LVS_EX_FULLROWSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);

	InsertColumnMacro(eCI_Time);
	InsertColumnMacro(eCI_Tick);
	InsertColumnMacro(eCI_Level);
	InsertColumnMacro(eCI_Pid);
	InsertColumnMacro(eCI_Tid);
	InsertColumnMacro(eCI_Filter);
	InsertColumnMacro(eCI_Message);
}

VOID SLogItemListView::AppendLogItem(const SLoggerMessagePtr& pLogMessage, size_t nIndex)
{
	int i = GetItemCount();
	
	__time64_t t = pLogMessage->GetTimeStamp();
	tm localtm;
	_localtime64_s(&localtm, &t);

	CString strTemp;
	_tcsftime(strTemp.GetBuffer(32), 32, _T("%Y-%m-%d %H:%M:%S"), &localtm);
	strTemp.ReleaseBuffer();

	InsertItem(i, strTemp);

	strTemp.Format(_T("%d"), pLogMessage->GetTickCount());
	SetItemText(i, eCI_Tick, strTemp);

	if (0 == pLogMessage->GetLogLevel())
		SetItemText(i, eCI_Level, _T("DEBUG"));
	else if (1 == pLogMessage->GetLogLevel())
		SetItemText(i, eCI_Level, _T("RELEASE"));
	else
		SetItemText(i, eCI_Level, _T("Unknown"));

	strTemp.Format(_T("%d"), pLogMessage->GetProcessId());
	SetItemText(i, eCI_Pid, strTemp);

	strTemp.Format(_T("%d"), pLogMessage->GetThreadId());
	SetItemText(i, eCI_Tid, strTemp);

	SetItemText(i, eCI_Filter, (TCHAR*)(pLogMessage->GetLogFilter().c_str()));
	SetItemText(i, eCI_Message, (TCHAR*)(pLogMessage->GetLogText().c_str()));
	SetItemData(i, (DWORD_PTR)nIndex);

	if (m_bAutoScroll)
		SelectItem(i);

	return ;
}

VOID SLogItemListView::ClearLogItems()
{
	DeleteAllItems();

	SLogMessageManager::GetInstance().Clear();

	return;
}

VOID SLogItemListView::EnableAutoScroll(BOOL bEnable)
{
	m_bAutoScroll = bEnable;
}
