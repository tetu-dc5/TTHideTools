// TtHideTools.h : TtHideTools.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��
#include "FastStringArray.h"
#include "EditListDialog.h"

// CTtHideToolsApp
// ���̃N���X�̎����Ɋւ��Ă� TtHideTools.cpp ���Q�Ƃ��Ă��������B
//

class CTtHideToolsApp : public CWinApp
{
public:
	CTtHideToolsApp();
	CString m_ResultString;
	CFastStringArray m_ResultStringArray;
	CEditListDialog* m_EditListDialog;
	CPatternMatch* m_PatternMatch;

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
