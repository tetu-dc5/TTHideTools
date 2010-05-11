#pragma once
#include "afxwin.h"
#include "MaskListBox.h"
#include "PatternMatch.h"
#include "FastStringArray.h"

// CEditListDialog �_�C�A���O

class CEditListDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditListDialog)

public:
	CEditListDialog(CWnd* pParent, CPatternMatch* match);   // �W���R���X�g���N�^
	virtual ~CEditListDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CString m_Edit;
	CString m_InitSearch;
	CMaskListBox m_List;
	afx_msg void OnEnChangeEdit1();
	CFastStringArray m_items;
	void ClearItem(void);
	int SetItems(LPTSTR str);
	int SetItemsFromFile(LPTSTR file);
	CString m_Title;
	virtual BOOL OnInitDialog();
	void AddViewList(int index);
	void MaskList(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_result;
	void GetMaskedList(bool enable);
	void SetEnableText(BOOL sw);
protected:
	virtual void OnOK();
	virtual void OnCancel();
	void SelectNext(void);
	void SelectPrev(void);
	LPCTSTR GetSelectedItem(void);
	void SelectItem(void);
	BOOL m_EnableText;
public:
	LPCTSTR getText(int list_index);
	CEdit m_EditCtrl;
	CPatternMatch* m_Match;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int m_width;
	int m_height;
};
