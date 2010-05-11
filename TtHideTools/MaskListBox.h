#pragma once

#include "PatternMatch.h"
#include "FastStringArray.h"

// CMaskListBox

class CMaskListBox : public CListBox
{
	DECLARE_DYNAMIC(CMaskListBox)

public:
	CMaskListBox();
	virtual ~CMaskListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	CString m_mask;
	CFastStringArray* m_items;
	CPatternMatch* m_Match;
	static void GetItemName(LPCTSTR src, CString& dst, bool lower=false);
	static void GetItemComment(LPCTSTR src, CString& dst, bool lower=false);
};


