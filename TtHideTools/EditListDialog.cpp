// EditListDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "TtHideTools.h"
#include "EditListDialog.h"
#include "HookKeyboard.h"


// CEditListDialog ダイアログ

IMPLEMENT_DYNAMIC(CEditListDialog, CDialog)

CEditListDialog::CEditListDialog(CWnd* pParent, CPatternMatch* match)
	: CDialog(CEditListDialog::IDD, pParent)
	, m_Edit(_T(""))
	, m_InitSearch(_T(""))
	, m_items(500,0x100000,0x100000)
	, m_Title(_T("リスト選択"))
	, m_result(_T(""))
	, m_EnableText(FALSE)
	, m_Match(match)
	, m_width(0)
	, m_height(0)
{
	m_List.m_Match = match;
	m_List.m_items = &m_items;
}

CEditListDialog::~CEditListDialog()
{
}

void CEditListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrl);
}


BEGIN_MESSAGE_MAP(CEditListDialog, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CEditListDialog::OnEnChangeEdit1)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CEditListDialog メッセージ ハンドラ

BOOL CEditListDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	//	タイトル設定
	SetWindowText((LPCTSTR)m_Title);
	//	Editの許可
	if(m_EnableText){
		m_EditCtrl.EnableWindow(TRUE);
		m_EditCtrl.ModifyStyleEx(WS_EX_RIGHT, WS_EX_LEFT);
		m_Edit=m_InitSearch;
	}
	else{
		m_Edit=_T("(press ENTER for search)");
	}
	UpdateData(FALSE);
	//	アイテム設定
	MaskList();
	//	ESCAPE転送
	CHookKeyboard::SetHWND(m_hWnd);
	//	サイズ設定
	if(m_width && m_height){
		SetWindowPos(NULL,0,0,m_width,m_height,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
	}
	return TRUE;
}

void CEditListDialog::OnOK()
{
	GetMaskedList(true);
	CHookKeyboard::SetHWND(NULL);
	CDialog::OnOK();
}

void CEditListDialog::OnCancel()
{
	GetMaskedList(false);
	CHookKeyboard::SetHWND(NULL);
	CDialog::OnCancel();
}

void CEditListDialog::SelectNext(void)
{
	int idx = m_List.GetCurSel();
	int cnt = m_List.GetCount();
	if(cnt>1){
		if(idx < (cnt-1)){
			m_List.SetCurSel(idx+1);
		}
		else{
			m_List.SetCurSel(0);
		}
	}
}

void CEditListDialog::SelectPrev(void)
{
	int idx = m_List.GetCurSel();
	int cnt = m_List.GetCount();
	if(cnt>1){
		if(idx>0){
			m_List.SetCurSel(idx-1);
		}
		else{
			m_List.SetCurSel(cnt-1);
		}
	}
}

LPCTSTR CEditListDialog::GetSelectedItem(void)
{
	if(m_List.GetCount()){
		int idx = m_List.GetCurSel();
		if(idx>=0){
			return getText(idx);
		}
		else{
			return _T("");
		}
	}
	else{
		return _T("");
	}
}

void CEditListDialog::SelectItem(void)
{
	m_result = GetSelectedItem();
	if(m_result.GetLength()){
		OnOK();
	}
	else{
		OnCancel();
	}
}

BOOL CEditListDialog::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam==VK_UP){
			SelectPrev();
			return TRUE;
		}
		else if(pMsg->wParam==VK_DOWN){
			SelectNext();
			return TRUE;
		}
		else if(pMsg->wParam==VK_TAB){
			if(GetKeyState(VK_SHIFT) & 0x8000){
				SelectPrev();
			}
			else{
				SelectNext();
			}
			return TRUE;
		}
		else if(pMsg->wParam==VK_ESCAPE){
			m_result = _T("");
			OnCancel();
			return TRUE;
		}
		else if(m_EnableText && pMsg->wParam>=VK_F1 && pMsg->wParam<=VK_F24){
			m_result.Format("\\F%02d,%s", pMsg->wParam-VK_F1+1, GetSelectedItem());
			OnOK();
			return TRUE;
		}
		else if(pMsg->wParam==VK_RETURN){
			if(!m_EnableText){
				m_Edit=m_InitSearch;
				UpdateData(FALSE);
				m_EnableText=TRUE;
				m_EditCtrl.EnableWindow(TRUE);
				m_EditCtrl.ModifyStyleEx(WS_EX_RIGHT, WS_EX_LEFT);
				m_EditCtrl.SetFocus();
				MaskList();
			}
			else{
				SelectItem();
			}
			return TRUE;
		}
		else if(pMsg->wParam==VK_NEXT || pMsg->wParam==VK_PRIOR){
			//	強制的にLISTへ送る
			pMsg->hwnd = m_List.GetSafeHwnd();
		}
		else if((pMsg->wParam==VK_HOME || pMsg->wParam==VK_END) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)){
			//	強制的にLISTへ送る
			pMsg->hwnd = m_List.GetSafeHwnd();
		}
	}
	else if(pMsg->message==WM_KEYUP){
		if(pMsg->wParam==VK_CONTROL && !m_EnableText){
			SelectItem();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CEditListDialog::OnEnChangeEdit1()
{
	UpdateData(TRUE);
	m_List.m_mask = m_Edit;
	m_List.m_mask.MakeLower();
	MaskList();
}

void CEditListDialog::ClearItem(void)
{
	m_items.RemoveAll();
}

int CEditListDialog::SetItems(LPTSTR str)
{
	return m_items.AddList(str, _T(","));
}

int CEditListDialog::SetItemsFromFile(LPTSTR file)
{
	return m_items.AddListFromFile(file);
}

void CEditListDialog::AddViewList(int index)
{
	int vIndex = m_List.AddString(m_items[index]);
	m_List.SetItemData(vIndex, index);
}

void CEditListDialog::MaskList(void)
{
	m_List.ResetContent();
	if(!m_EnableText || m_Edit.GetLength()==0){
		for(int i=0;i<m_items.GetCount();i++){
			AddViewList(i);
		}
		if(!m_EnableText && m_List.GetCount()>1){
			m_List.SetCurSel(1);
		}
		else if(m_List.GetCount()>0){
			m_List.SetCurSel(0);
		}
	}
	else{
		CString pat = m_Edit;
		pat.MakeLower();
		int id=0;
		for(int i=0;i<m_items.GetCount();i++){
			CString src;
			CMaskListBox::GetItemName(m_items[i], src, true);
			int lenth;
			if(m_Match->Find((LPCTSTR)src,(LPCTSTR)pat,lenth)>=0){
				AddViewList(i);
			}
		}
		if(m_List.GetCount()>0){
			m_List.SetCurSel(0);
		}
	}
}

void CEditListDialog::GetMaskedList(bool enable)
{
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	app->m_ResultStringArray.RemoveAll();
	if(!enable) return;
	int num = m_List.GetCount();
	if(!num) return;
	for(int i=0;i<num;i++){
		app->m_ResultStringArray.Add(getText(i));
	}
}

LPCTSTR CEditListDialog::getText(int list_index)
{
	int item_index = m_List.GetItemData(list_index);
	return m_items[item_index];
}

void CEditListDialog::SetEnableText(BOOL sw)
{
	m_EnableText=sw;
}

void CEditListDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	RECT	rect;
	if(m_EditCtrl.m_hWnd){
		m_EditCtrl.GetWindowRect(&rect);
		m_EditCtrl.ScreenToClient(&rect);
		m_EditCtrl.SetWindowPos(NULL,0,0,cx-1,rect.bottom-rect.top,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
	}
	if(m_List.m_hWnd){
		m_List.GetWindowRect(&rect);
		m_EditCtrl.ScreenToClient(&rect);
		m_List.SetWindowPos(NULL,0,0,cx-1,cy-rect.top-1,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
	}
}
