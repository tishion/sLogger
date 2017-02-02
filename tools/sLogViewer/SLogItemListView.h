#pragma once
#include <atlwin.h>
#include <atlctrls.h>
#include <atltypes.h>
#include <time.h>

class SLogItemListView :
	public CWindowImpl<SLogItemListView, CListViewCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CListViewCtrl::GetWndClassName())

	SLogItemListView();

	~SLogItemListView();

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(SLogItemListView)
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

public:
	VOID Initialize();
	
	VOID EnableAutoScroll(BOOL bEnable);
	
	VOID AppendLogItem(const SLoggerMessagePtr& pLogMessage, size_t nIndex);
	
	VOID ClearLogItems();

private:
	BOOL m_bAutoScroll;
};

