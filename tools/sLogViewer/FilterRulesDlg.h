#pragma once
#include <atlctrls.h>
#include <atlddx.h>  

class CFilterRulesDlg : 
	public CDialogImpl<CFilterRulesDlg>
{
public:
	enum { IDD = IDD_DIALOGFILTERRULE };

	BEGIN_MSG_MAP(CFilterRulesDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_BUTTON_ADD, OnAddCmd)
		COMMAND_ID_HANDLER(IDC_BUTTON_DEL, OnRemoveCmd)
		COMMAND_ID_HANDLER(IDC_BUTTON_CLEAR, OnClearCmd)
		COMMAND_ID_HANDLER(IDC_BUTTON_APPLY, OnCloseCmd)
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnAddCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnRemoveCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnApplyCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnClearCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

protected:
	void InitRulesListItems();

private:
	CComboBox		m_ItemList;
	
	CComboBox		m_CompareList;

	CComboBox		m_CategoryList;

	CListViewCtrl	m_RulesList;

	CEdit			m_Value;
};
