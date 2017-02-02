#include "stdafx.h"
#include "FilterRulesDlg.h"
#include "SLogFilterManager.h"

TCHAR* gItemName[] =
{
	_T("Pid"),
	_T("Tid"),
	_T("Tick"),
	_T("Filter"),
	_T("Message")
};

TCHAR* gCompareName[] =
{
	_T("is"),
	_T("not is"),
	_T("contain"),
	_T("not contain"),
	_T("less than"),
	_T("more than")
};

TCHAR* gCategoryName[] =
{
	_T("Include"),
	_T("Exclude")
};

int findIndex(LPCTSTR k, TCHAR* a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (0 == _tcscmp(a[i], k))
		{
			return i;
		}
	}
	return -1;
}

LRESULT CFilterRulesDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_ItemList = GetDlgItem(IDC_COMBO_ITEM);
	for (int i = 0; i < _countof(gItemName); i++)
	{
		m_ItemList.AddString(gItemName[i]);
	}
	m_ItemList.SetCurSel(0);

	m_CompareList = GetDlgItem(IDC_COMBO_COMPARE);
	for (int i = 0; i < _countof(gCompareName); i++)
	{
		m_CompareList.AddString(gCompareName[i]);
	}
	m_CompareList.SetCurSel(0);

	m_CategoryList = GetDlgItem(IDC_COMBO_CATEGORY);
	m_CategoryList.AddString(gCategoryName[0]);
	m_CategoryList.AddString(gCategoryName[1]);
	m_CategoryList.SetCurSel(0);

	m_RulesList = GetDlgItem(IDC_LIST_RULES);
	m_RulesList.SetExtendedListViewStyle(
		LVS_EX_FULLROWSELECT | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);
	m_RulesList.InsertColumn(0, _T("Column"), LVCFMT_LEFT, 60);
	m_RulesList.InsertColumn(1, _T("Compare"), LVCFMT_LEFT, 60);
	m_RulesList.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 380);
	m_RulesList.InsertColumn(3, _T("Action"), LVCFMT_LEFT, 60);

	m_Value = GetDlgItem(IDC_EDIT_VALUE);

	InitRulesListItems();

	CenterWindow(GetParent());
	return TRUE;
}

LRESULT CFilterRulesDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CFilterRulesDlg::OnAddCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString		value;
	m_Value.GetWindowText(value.GetBuffer(MAX_PATH), MAX_PATH);
	value.ReleaseBuffer();

	if (value.IsEmpty())
	{
		return 0;
	}

	Attribute	attr = (Attribute)(m_ItemList.GetCurSel());
	CString		strAttr;
	m_ItemList.GetWindowText(strAttr.GetBuffer(MAX_PATH), MAX_PATH);
	strAttr.ReleaseBuffer();

	Operator	opr = (Operator)(m_CompareList.GetCurSel());
	CString		strOpr;
	m_CompareList.GetWindowText(strOpr.GetBuffer(MAX_PATH), MAX_PATH);
	strOpr.ReleaseBuffer();

	Category	cat = (Category)(m_CategoryList.GetCurSel());
	CString		strCat;
	m_CategoryList.GetWindowText(strCat.GetBuffer(MAX_PATH), MAX_PATH);
	strCat.ReleaseBuffer();

	if (SLogFilterManager::GetInstance().AddRule(attr, opr, value, cat))
	{
		int nListIndex = 0;

		if (cat == 0)
		{
			nListIndex = m_RulesList.InsertItem(0, strAttr);
		}
		else
		{
			nListIndex = m_RulesList.InsertItem(m_RulesList.GetItemCount(), strAttr);
		}

		m_RulesList.SetItemText(nListIndex, 1, strOpr);
		m_RulesList.SetItemText(nListIndex, 2, value);
		m_RulesList.SetItemText(nListIndex, 3, strCat);
	}

	return 0;
}

LRESULT CFilterRulesDlg::OnRemoveCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nListIndex = m_RulesList.GetSelectedIndex();
	if (nListIndex >= 0)
	{
		CString strAttr;
		m_RulesList.GetItemText(nListIndex, 0, strAttr);
		CString strOpr;
		m_RulesList.GetItemText(nListIndex, 1, strOpr);
		CString value;
		m_RulesList.GetItemText(nListIndex, 2, value);
		CString strCat;
		m_RulesList.GetItemText(nListIndex, 3, strCat);

		Attribute attr = (Attribute)findIndex(strAttr.GetString(), gItemName, _countof(gItemName));
		Operator opr = (Operator)findIndex(strOpr.GetString(), gCompareName, _countof(gCompareName));
		Category cat = (Category)findIndex(strCat.GetString(), gCategoryName, _countof(gCategoryName));

		SLogFilterManager::GetInstance().DelRule(attr, opr, value, cat);

		m_RulesList.DeleteItem(nListIndex);
	}
	return 0;
}

LRESULT CFilterRulesDlg::OnApplyCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	::PostMessage(GetParent(), SLVM_APPLY_FILTER_RULES, 0, 0);
	return 0;
}

LRESULT CFilterRulesDlg::OnClearCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_RulesList.DeleteAllItems();
	SLogFilterManager::GetInstance().ClearRules();
	return 0;
}

void CFilterRulesDlg::InitRulesListItems()
{
	FilterRuleList includeList;
	FilterRuleList excludeList;
	SLogFilterManager::GetInstance().GetRulesLists(includeList, excludeList);

	for (auto it = includeList.begin();
		it != includeList.end();
		it++)
	{
		FilterRule rule = *it;

		Attribute	attr = (Attribute)(rule.attr);
		CString		strAttr = gItemName[attr];

		Operator	opr = (Operator)(rule.opr);
		CString		strOpr = gCompareName[opr];

		int nListIndex = m_RulesList.InsertItem(0, strAttr);
		m_RulesList.SetItemText(nListIndex, 1, strOpr);
		m_RulesList.SetItemText(nListIndex, 2, rule.value);
		m_RulesList.SetItemText(nListIndex, 3, _T("Include"));

		uint32_t category = (0 << 31);
	}

	for (auto it = excludeList.begin();
		it != excludeList.end();
		it++)
	{
		FilterRule rule = *it;

		Attribute	attr = (Attribute)(rule.attr);
		CString		strAttr = gItemName[attr];

		Operator	opr = (Operator)(rule.opr);
		CString		strOpr = gCompareName[opr];

		int nListIndex = m_RulesList.InsertItem(m_RulesList.GetItemCount(), strAttr);
		m_RulesList.SetItemText(nListIndex, 1, strOpr);
		m_RulesList.SetItemText(nListIndex, 2, rule.value);
		m_RulesList.SetItemText(nListIndex, 3, _T("Exclude"));

		uint32_t category = (1 << 31);
	}
}