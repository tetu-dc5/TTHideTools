// MaskListBox.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "TtHideTools.h"
#include "MaskListBox.h"


// CMaskListBox

IMPLEMENT_DYNAMIC(CMaskListBox, CListBox)

CMaskListBox::CMaskListBox()
: m_mask(_T(""))
, m_items(NULL)
, m_Match(NULL)
{

}

CMaskListBox::~CMaskListBox()
{
}


BEGIN_MESSAGE_MAP(CMaskListBox, CListBox)
END_MESSAGE_MAP()



// CMaskListBox ���b�Z�[�W �n���h��



void CMaskListBox::MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/)
{
}

void CMaskListBox::GetItemName(LPCTSTR src, CString& dst, bool lower)
{
	dst = src;
	int pos = dst.Find(_T("//"));
	if(pos>=0){
		dst = dst.Left(pos);
	}
	if(lower) dst.MakeLower();
}

void CMaskListBox::GetItemComment(LPCTSTR src, CString& dst, bool lower)
{
	dst = src;
	int pos = dst.Find(_T("//"));
	if(pos>=0){
		dst = dst.Mid(pos+2);
	}
	if(lower) dst.MakeLower();
}

void CMaskListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	pDC->SetBkMode(TRANSPARENT);
	COLORREF text_color;
	if(lpDrawItemStruct->itemState & ODS_SELECTED){
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT));
		text_color=GetSysColor(COLOR_HIGHLIGHTTEXT);
	}
	else{
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW));
		text_color=GetSysColor(COLOR_WINDOWTEXT);
	}
	pDC->SetTextColor(text_color);
	CString	name;
	int no = GetItemData(lpDrawItemStruct->itemID) + 1;
	GetItemName(m_items->GetAt(lpDrawItemStruct->itemData), name, true);
	int len = 0;
	int pos = 0;
	pos = m_Match->Find((LPCTSTR)name,(LPCTSTR)m_mask,len);

	int rlen = name.GetLength() - (pos+len);
	int x = lpDrawItemStruct->rcItem.left+4;
	int y = lpDrawItemStruct->rcItem.top+2;
	CString	tmp;
	CSize	size;
	//	�I���W�i���̖��O�ɖ߂�
	GetItemName(m_items->GetAt(lpDrawItemStruct->itemData), name, false);
	//	�ԍ��`��
	tmp.Format("%d", no);
	size = pDC->GetOutputTextExtent(tmp);
	int num_x = size.cx;
	int count = m_items->GetCount();
	if(count>1000){
		size = pDC->GetOutputTextExtent(_T("0000"),4);
	}
	else if(count>100){
		size = pDC->GetOutputTextExtent(_T("000"),3);
	}
	else{
		size = pDC->GetOutputTextExtent(_T("00"),2);
	}
	int num_width = size.cx;
	if(no>=0){
		pDC->SetTextColor(RGB(0xD0,0xD0,0xD0));
		pDC->TextOut(x+(num_width-num_x),y,(LPCTSTR)tmp);
		pDC->SetTextColor(text_color);
	}
	size = pDC->GetOutputTextExtent(_T("0"),1);
	x+=num_width+size.cx;

	if(len && pos>=0){
		//	������BOLD�t�H���g�쐬
		CFont*	old;
		CFont	dummy;
		dummy.CreatePointFont(140,_T("FixedSys"),pDC);
		old = pDC->SelectObject(&dummy);
		CFont	bold;
		LOGFONT log;
		old->GetLogFont(&log);
		log.lfWeight=FW_BLACK;
		bold.CreateFontIndirect(&log);
		pDC->SelectObject(old);
		//	����
		if(pos!=0){
			tmp = name.Left(pos);
			pDC->TextOut(x,y,(LPCTSTR)tmp);
			size = pDC->GetOutputTextExtent(tmp);
			x+=size.cx;
		}
		//	�^��
		{
			old = pDC->SelectObject(&bold);
			tmp = name.Mid(pos,len);
			pDC->TextOut(x,y,(LPCTSTR)tmp);
			size = pDC->GetOutputTextExtent(tmp);
			x+=size.cx;
			pDC->SelectObject(old);
		}
		//	�E��
		if(rlen){
			tmp = name.Right(rlen);
			pDC->TextOut(x,	y,(LPCTSTR)tmp);
		}
	}
	else{
		pDC->TextOut(x,y,(LPCTSTR)name);
	}
}
