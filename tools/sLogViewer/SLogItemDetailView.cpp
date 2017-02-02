#include "StdAfx.h"
#include "SLogItemDetailView.h"

BOOL SLogItemDetailView::PreTranslateMessage(MSG* pMsg)
{
	UNREFERENCED_PARAMETER(pMsg);
	return FALSE;
}

void SLogItemDetailView::ShowDetails(LPCTSTR pDetails)
{
	if (pDetails)
	{
		SetWindowText(pDetails);
	}
}
