#pragma once
#include <set>
#include <atlsync.h>

typedef enum Attribute
{
	ePid = 0,
	eTid,
	eTick,
	eFilter,
	eMessage,
};

typedef enum Operator
{
	eIs = 0,
	eNotIs,
	eContains,
	eNotContains,
	eLessThan,
	eMoreThan,
};

typedef enum  Category
{
	eInclude = 0,
	eExclued,
};

class FilterRule
{
public:
	Attribute	attr;
	Operator	opr;
	CString		value;

	bool operator==(const FilterRule& other) const
	{
		if (attr != other.attr
			|| opr != other.opr
			|| 0 != value.Compare(other.value))
		{
			return false;
		}

		return true;
	}

	bool operator!=(const FilterRule& other) const
	{
		if (attr != other.attr
			|| opr != other.opr
			|| 0 != value.Compare(other.value))
		{
			return true;
		}

		return false;
	}

	bool operator<(const FilterRule& other) const
	{
		if (attr != other.attr)
		{
			return (attr < other.attr);
		}

		if (opr != other.opr)
		{
			return (opr < other.opr);
		}

		int n = value.Compare(other.value);
		return (n < 0);
	}

};

typedef std::set<FilterRule> FilterRuleList;

class SLogFilterManager
{
public:
	static SLogFilterManager& GetInstance();

	BOOL ShouldDisplayThisItem(const SLoggerMessagePtr& pLogMsg);

	bool AddRule(Attribute attr, Operator opr, CString& value, Category cat);

	void DelRule(Attribute attr, Operator opr, CString& value, Category cat);

	void ClearRules();

	void GetRulesLists(FilterRuleList& inclist, FilterRuleList& exclist);

protected:
	SLogFilterManager();

	~SLogFilterManager();

	BOOL Compare(DWORD left, Operator opr, DWORD right);
	
	BOOL Compare(LPCTSTR left, Operator opr, LPCTSTR right);
	
	BOOL MatchIncludeFilterRules(const SLoggerMessagePtr& pLogMsg);
	
	BOOL MatchExcludeFilterRules(const SLoggerMessagePtr& pLogMsg);

private:
	BOOL m_bDebugLvlEnable;
	
	BOOL m_bReleaseLvlEnable;

	FilterRuleList		m_includeList;
	
	FilterRuleList		m_excludeList;
	
	CCriticalSection	m_cs;
};

