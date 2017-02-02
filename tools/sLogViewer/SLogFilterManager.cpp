#include "stdafx.h"
#include "SLogFilterManager.h"

typedef std::pair<FilterRuleList::iterator, bool> InsertResult;

SLogFilterManager::SLogFilterManager()
{
	m_bDebugLvlEnable = TRUE;
	m_bReleaseLvlEnable = TRUE;
}

SLogFilterManager::~SLogFilterManager()
{

}

SLogFilterManager& SLogFilterManager::GetInstance()
{
	static SLogFilterManager s_instance;
	return s_instance;
}

BOOL SLogFilterManager::ShouldDisplayThisItem(const SLoggerMessagePtr& pLogMsg)
{
	BOOL bInclude = MatchIncludeFilterRules(pLogMsg);
	BOOL bExclude = MatchExcludeFilterRules(pLogMsg);

	if (bExclude)
	{
		// bExclude = TRUE 
		// bInclude = FALSE or bInclude = TRUE
		return FALSE;
	}
	else
	{
		if (bInclude)
		{
			// bExclude = FALSE && bInclude = TRUE
			return TRUE;
		}
		else
		{
			// bExclude = FALSE && bInclude = FALSE
			return FALSE;
		}
	}
}

bool SLogFilterManager::AddRule(Attribute attr, Operator opr, CString& value,  Category cat)
{
	FilterRule rule;
	rule.attr = attr;
	rule.opr = opr;
	rule.value = value;

	InsertResult r;
	m_cs.Enter();
	if (eInclude == cat)
	{
		r = m_includeList.insert(rule);
	}
	else if (eExclued == cat)
	{
		
		r = m_excludeList.insert(rule);
	}
	m_cs.Leave();

	return r.second;
}

void SLogFilterManager::DelRule(Attribute attr, Operator opr, CString& value, Category cat)
{
	FilterRule rule;
	rule.attr = attr;
	rule.opr = opr;
	rule.value = value;

	m_cs.Enter();
	if (eInclude == cat)
	{
		m_includeList.erase(rule);
	}
	else if (eExclued == cat)
	{
		m_excludeList.erase(rule);
	}
	m_cs.Leave();
}

void SLogFilterManager::ClearRules()
{
	m_cs.Enter();
	m_includeList.clear();
	m_excludeList.clear();
	m_cs.Leave();
}

BOOL SLogFilterManager::MatchIncludeFilterRules(const SLoggerMessagePtr& pLogMsg)
{
	if (0 == m_includeList.size())
	{
		return TRUE;
	}

	BOOL bInclude = FALSE;
	m_cs.Enter();
	for (auto it = m_includeList.begin();
		it != m_includeList.end();
		it++)
	{
		FilterRule rule = *it;
		switch (rule.attr)
		{
		case ePid:
		{
			DWORD ruleValue = ::StrToInt(rule.value.GetString());
			bInclude = Compare(pLogMsg->GetProcessId(), rule.opr, ruleValue);
		}
			break;
		case eTid:
		{
			DWORD ruleValue = ::StrToInt(rule.value.GetString());
			bInclude = Compare(pLogMsg->GetThreadId(), rule.opr, ruleValue);
		}
			break;
		case eTick:
		{
			DWORD ruleValue = ::StrToInt(rule.value.GetString());
			bInclude = Compare(pLogMsg->GetTickCount(), rule.opr, ruleValue);
		}
			break;
		case eFilter:
		{
			bInclude = Compare((LPCTSTR)(pLogMsg->GetLogFilter().c_str()), rule.opr, rule.value.GetString());
		}
			break;
		case eMessage:
		{
			bInclude = Compare((LPCTSTR)(pLogMsg->GetLogText().c_str()), rule.opr, rule.value.GetString());
		}
			break;
		default:
			break;
		}

		if (TRUE == bInclude)
		{
			break;
		}
	}
	m_cs.Leave();

	return bInclude;
}

BOOL SLogFilterManager::MatchExcludeFilterRules(const SLoggerMessagePtr& pLogMsg)
{
	if (0 == m_excludeList.size())
	{
		return FALSE;
	}

	BOOL bExclude = FALSE;
	m_cs.Enter();
	for (auto it = m_excludeList.begin();
		it != m_excludeList.end();
		it++)
	{
		FilterRule rule = *it;
		switch (rule.attr)
		{
		case ePid:
		{
			DWORD ruleValue = ::StrToInt(rule.value.GetString());
			bExclude = Compare(pLogMsg->GetProcessId(), rule.opr, ruleValue);
		}
			break;
		case eTid:
		{
			DWORD ruleValue = ::StrToInt(rule.value.GetString());
			bExclude = Compare(pLogMsg->GetThreadId(), rule.opr, ruleValue);
		}
			break;
		case eTick:
		{
			DWORD ruleValue = ::StrToInt(rule.value.GetString());
			bExclude = Compare(pLogMsg->GetTickCount(), rule.opr, ruleValue);
		}
			break;
		case eFilter:
		{
			bExclude = Compare((LPCTSTR)(pLogMsg->GetLogFilter().c_str()), rule.opr, rule.value.GetString());
		}
			break;
		case eMessage:
		{
			bExclude = Compare((LPCTSTR)(pLogMsg->GetLogText().c_str()), rule.opr, rule.value.GetString());
		}
			break;
		default:
			break;
		}

		if (TRUE == bExclude)
		{
			break;
		}
	}
	m_cs.Leave();
	return bExclude;
}

BOOL SLogFilterManager::Compare(DWORD left, Operator opr, DWORD right)
{
	BOOL bRet = FALSE;
	switch (opr)
	{
	case eIs:
	{
		bRet = (left == right);
	}
		break;
	case eNotIs:
	{
		bRet = (left != right);
	}
		break;
	case eContains:
	{
		return FALSE;
	}
		break;
	case eNotContains:
	{
		return FALSE;
	}
		break;
	case eLessThan:
	{
		bRet = (left < right);
	}
		break;
	case eMoreThan:
	{
		bRet = (left > right);
	}
		break;
	default:
		break;
	}

	return bRet;
}

BOOL SLogFilterManager::Compare(LPCTSTR left, Operator opr, LPCTSTR right)
{
	BOOL bRet = FALSE;

	CString strLeft = left;
	CString strRight = right;

	switch (opr)
	{
	case eIs:
	{
		bRet = (0 == strLeft.CompareNoCase(right));
	}
		break;
	case eNotIs:
	{
		return FALSE;
	}
		break;
	case eContains:
	{
		bRet = (strLeft.Find(right) != -1);
	}
		break;
	case eNotContains:
	{
		bRet = (strLeft.Find(right) == 1);
	}
		break;
	case eLessThan:
	{
		bRet = (strLeft.CompareNoCase(right) < 0);
	}
		break;
	case eMoreThan:
	{
		bRet = (strLeft.CompareNoCase(right) > 0);
	}
		break;
	default:
		break;
	}

	return bRet;
}

void SLogFilterManager::GetRulesLists(FilterRuleList& inclist, FilterRuleList& exclist)
{
	m_cs.Enter();
	inclist = m_includeList;
	exclist = m_excludeList;
	m_cs.Leave();
}

