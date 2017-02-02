#include "StdAfx.h"
#include "SLogMessageManager.h"
#include "SLogReceiver.h"

SLogReceiver::SLogReceiver()
{
	m_hWndProcessor = NULL;
	m_bEnable		= FALSE;
	m_workThread	= NULL;
}

SLogReceiver::~SLogReceiver()
{

}

LRESULT SLogReceiver::OnCopyData(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	if (m_bEnable)
	{
		PCOPYDATASTRUCT pCds = (PCOPYDATASTRUCT)(lParam);
		if (pCds)
		{
			PVOID pData = pCds->lpData;
			DWORD nLen = pCds->cbData;

			std::vector<unsigned char> buf(nLen, 0);
			RtlCopyMemory(buf.data(), pData, nLen);

			SLoggerMessagePtr pLogMsg = std::make_shared<CSLoggerMessage>();
			pLogMsg->FromBytesArray(buf);

			DWORD nIndex = SLogMessageManager::GetInstance().Append(pLogMsg);
			::PostMessage(m_hWndProcessor, SLVM_NEW_LOGMSGOBJ, (WPARAM)nIndex, 0);
		}
	}
	return 0;
}

LRESULT SLogReceiver::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT SLogReceiver::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DestroyWindow();
	return 0;
}

LRESULT SLogReceiver::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0);
	return 0;
}

DWORD SLogReceiver::WorkThreadProc()
{
	HWND hWnd = Create(HWND_MESSAGE, 0, LOG_VIEWER_WNDTITLE_NAME);

	if (!hWnd)
	{
		return 0;
	}

	CMessageLoop MsgLoop;
	int nRet = MsgLoop.Run();

	return nRet;
}

BOOL SLogReceiver::Start()
{
	m_workThread = std::make_shared<WorkThread>(
		&SLogReceiver::WorkThreadProc, this);

	if (m_workThread->native_handle())
	{
		return TRUE;
	}

	return FALSE;
}

BOOL SLogReceiver::Stop()
{
	PostMessage(WM_CLOSE);
	
	if (m_workThread)
	{
		m_workThread->join();
	}
	return TRUE;
}

BOOL SLogReceiver::EnableReceive(BOOL bEnable)
{
	m_bEnable = bEnable;
	return TRUE;
}

VOID SLogReceiver::SetProcessorWindow(HWND hWnd)
{
	m_hWndProcessor = hWnd;
}
