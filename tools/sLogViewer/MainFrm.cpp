#include "stdafx.h"
#include "aboutdlg.h"
#include "MainFrm.h"
#include "SLogFilterManager.h"
#include "SLogMessageManager.h"
#include "FilterRulesDlg.h"

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_LogItemListView.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	BOOL bCapture = FALSE;
	BOOL bAutoScroll = TRUE;

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);

	// initialize toolbar
	{
		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, 
			FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

		m_ToolBar.Attach(hWndToolBar);

		m_ToolBarImageList.CreateFromImage(
			IDB_TOOBARIMAGELIST, 17, 1, CLR_DEFAULT, IMAGE_BITMAP);
		m_ToolBar.SetImageList(m_ToolBarImageList);

		m_ToolBar.ChangeBitmap(ID_FILE_OPEN, IMAGE_INDEX_OPEN);
		m_ToolBar.ChangeBitmap(ID_FILE_CLOSE, IMAGE_INDEX_CLOSE);
		m_ToolBar.ChangeBitmap(ID_CAPTURE_CAPTURE, IMAGE_INDEX_DISABLE_CAPTURE);
		m_ToolBar.ChangeBitmap(ID_CAPTURE_AUTOSCROLL, IMAGE_INDEX_ENABLE_AUTOSCROLL);
		m_ToolBar.ChangeBitmap(ID_CAPTURE_CLEAR, IMAGE_INDEX_CLEAR);
		m_ToolBar.ChangeBitmap(ID_CAPTURE_FILTER, IMAGE_INDEX_FILTER);

		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		UIAddToolBar(hWndToolBar);

		UISetCheck(ID_CAPTURE_CAPTURE, bCapture);
		UISetCheck(ID_CAPTURE_AUTOSCROLL, bAutoScroll);
		UISetCheck(ID_VIEW_TOOLBAR,			TRUE);

		UIEnable(ID_FILE_OPEN, FALSE);
		UIEnable(ID_FILE_CLOSE, FALSE);
		m_ToolBar.EnableButton(ID_FILE_OPEN, FALSE);
		m_ToolBar.EnableButton(ID_FILE_CLOSE, FALSE);
	}
	
	// initialize splitter window
	{
		CRect rcClient;
		GetClientRect(rcClient);

		m_hWndClient = m_Splitter.Create(m_hWnd, rcClient, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		m_LogItemListView.Create(m_hWndClient, rcDefault, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL |
			LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS | LVS_SINGLESEL,
			WS_EX_CLIENTEDGE);

		m_LogItemDetailView.Create(m_hWndClient, rcDefault, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL |
			ES_MULTILINE,
			WS_EX_CLIENTEDGE);

		
		m_LogItemListView.Initialize();


		m_Splitter.SetSplitterPanes(m_LogItemListView, m_LogItemDetailView);
		m_Splitter.SetSplitterPos(((rcClient.bottom - rcClient.top) / 4) * 3);
	}

	// register object for message filtering and idle updates
	{
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
	}

	// initialize　log message object receiver
	{
		m_Receiver.Start();
		m_Receiver.SetProcessorWindow(m_hWnd);
		m_Receiver.EnableReceive(bCapture);
	}

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	m_Receiver.Stop();

	// unregister message filtering and idle updated
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
	
	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnAppExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainFrame::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	return 0;
}

LRESULT CMainFrame::OnFileClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	return 0;
}

LRESULT CMainFrame::OnCaptureCapture(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bEnable = !(UPDUI_CHECKED & UIGetState(ID_CAPTURE_CAPTURE));
	m_Receiver.EnableReceive(bEnable);

	UISetCheck(ID_CAPTURE_CAPTURE, bEnable);

	if (bEnable)
	{
		m_ToolBar.ChangeBitmap(ID_CAPTURE_CAPTURE, IMAGE_INDEX_ENABLE_CAPTURE);
	}
	else
	{
		m_ToolBar.ChangeBitmap(ID_CAPTURE_CAPTURE, IMAGE_INDEX_DISABLE_CAPTURE);
	}

	UpdateLayout();

	return 0;
}

LRESULT CMainFrame::OnCaptureAutoscroll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bEnable = !(UPDUI_CHECKED & UIGetState(ID_CAPTURE_AUTOSCROLL));
	m_LogItemListView.EnableAutoScroll(bEnable);
	
	UISetCheck(ID_CAPTURE_AUTOSCROLL, bEnable);

	if (bEnable)
	{
		m_ToolBar.ChangeBitmap(ID_CAPTURE_AUTOSCROLL, IMAGE_INDEX_ENABLE_AUTOSCROLL);
	}
	else
	{
		m_ToolBar.ChangeBitmap(ID_CAPTURE_AUTOSCROLL, IMAGE_INDEX_DISABLE_AUTOSCROLL);
	}

	UpdateLayout();

	return 0;
}

LRESULT CMainFrame::OnCaptureClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_LogItemListView.ClearLogItems();
	m_LogItemDetailView.SetWindowTextW(NULL);

	UpdateLayout();

	return 0;
}

LRESULT CMainFrame::OnCaptureFilter(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//CFilterRulesDlg dlg;
	//dlg.DoModal();

	if (!m_FilterRulesDlg.IsWindow())
	{
		m_FilterRulesDlg.Create(m_hWnd);
	}

	m_FilterRulesDlg.ShowWindow(SW_SHOWNORMAL);
	return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndToolBar);
	::ShowWindow(m_hWndToolBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnLogMsgObj(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	DWORD nIndex = (DWORD)(wParam);
	auto pLogMsg = SLogMessageManager::GetInstance().Get(nIndex);
	
	if (pLogMsg && SLogFilterManager::GetInstance().ShouldDisplayThisItem(pLogMsg))
			m_LogItemListView.AppendLogItem(pLogMsg, nIndex);
	
	return 0;
}

LRESULT CMainFrame::OnLVNItemChanged(int wParam, LPNMHDR lParam, BOOL& /*bHandled*/)
{
	if (lParam)
	{
		if (lParam->hwndFrom == m_LogItemListView.m_hWnd)
		{
			LPNMLISTVIEW lpNMListView = (LPNMLISTVIEW)(lParam);

			if (lpNMListView && (lpNMListView->uNewState & LVIS_SELECTED))
			{
				DWORD nIndex = (DWORD)
					m_LogItemListView.GetItemData(lpNMListView->iItem);

				auto pLogMsg = SLogMessageManager::GetInstance().Get(nIndex);
				m_LogItemDetailView.ShowDetails((LPCTSTR)(pLogMsg->GetLogText().c_str()));
			}
		}
	}

	return 0;
}

LRESULT CMainFrame::OnApplyFilterRules(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}
