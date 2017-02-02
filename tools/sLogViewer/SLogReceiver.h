#pragma once
#include <functional>
#include <thread>
#include <vector>

#define LOG_VIEWER_WNDCLASS_NAME L"SLOGGERVIEWER_WNDCLASS_{16a0cd54-f03b-4244-98a4-fffdb085fda2}"
#define LOG_VIEWER_WNDTITLE_NAME L"SLOGGERVIEWER_WNDTITLE_{e408d8b6-8a74-4331-9ccb-b76c4ab825fe}"

class SLogReceiver :
	public CWindowImpl<SLogReceiver, CWindow, CWinTraits<WS_OVERLAPPED>>
{
	typedef std::thread						WorkThread;
	typedef std::shared_ptr<WorkThread>		WorkThreadPtr;
public:
	SLogReceiver();

	~SLogReceiver();

	DECLARE_WND_CLASS(LOG_VIEWER_WNDCLASS_NAME)

	BEGIN_MSG_MAP(SLogReceiver)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_COPYDATA, OnCopyData);
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_MSG_MAP()

	VOID SetProcessorWindow(HWND hWnd);

	BOOL Start();

	BOOL Stop();

	BOOL EnableReceive(BOOL bEnable);

protected:
	LRESULT OnCopyData(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	DWORD WorkThreadProc();

private:
	HWND			m_hWndProcessor;

	BOOL			m_bEnable;

	WorkThreadPtr	m_workThread;
};

