// TtHideTools.h : TtHideTools.DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include "FastStringArray.h"
#include "EditListDialog.h"

// CTtHideToolsApp
// このクラスの実装に関しては TtHideTools.cpp を参照してください。
//

class CTtHideToolsApp : public CWinApp
{
public:
	CTtHideToolsApp();
	CString m_ResultString;
	CFastStringArray m_ResultStringArray;
	CEditListDialog* m_EditListDialog;
	CPatternMatch* m_PatternMatch;

// オーバーライド
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
