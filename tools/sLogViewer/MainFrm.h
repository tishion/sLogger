#pragma once
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlw.h>
#include <atlcoll.h>
#include <atlsplit.h>
#include <atltypes.h>
#include "SLogItemListView.h"
#include "SLogItemDetailView.h"
#include "SLogReceiver.h"
#include "FilterRulesDlg.h"

class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(SLV_MAIN_WNDCLS_NAME, IDR_MAINFRAME)

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_FILE_OPEN, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_FILE_CLOSE, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CAPTURE_CAPTURE, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CAPTURE_AUTOSCROLL, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CAPTURE_CLEAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		// message for main window
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		// message for command button
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(ID_FILE_CLOSE, OnFileClose)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnAppExit)
		COMMAND_ID_HANDLER(ID_CAPTURE_CAPTURE, OnCaptureCapture)
		COMMAND_ID_HANDLER(ID_CAPTURE_AUTOSCROLL, OnCaptureAutoscroll)
		COMMAND_ID_HANDLER(ID_CAPTURE_CLEAR, OnCaptureClear)
		COMMAND_ID_HANDLER(ID_CAPTURE_FILTER, OnCaptureFilter)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		// message for log message coming
		MESSAGE_HANDLER(SLVM_NEW_LOGMSGOBJ, OnLogMsgObj)
		MESSAGE_HANDLER(SLVM_APPLY_FILTER_RULES, OnApplyFilterRules)
		// message for item selected changed
		NOTIFY_CODE_HANDLER(LVN_ITEMCHANGED, OnLVNItemChanged)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnFileClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnAppExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnCaptureCapture(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnCaptureAutoscroll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnCaptureClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnCaptureFilter(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnLogMsgObj(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	LRESULT OnApplyFilterRules(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	LRESULT OnLVNItemChanged(int wParam, LPNMHDR lParam, BOOL& /*bHandled*/);

private:
	CImageList					m_ToolBarImageList;
	
	CToolBarCtrl				m_ToolBar;

	CHorSplitterWindow			m_Splitter;

	SLogItemListView			m_LogItemListView;
	
	SLogItemDetailView		m_LogItemDetailView;
	
	SLogReceiver			m_Receiver;

	CFilterRulesDlg				m_FilterRulesDlg;
};