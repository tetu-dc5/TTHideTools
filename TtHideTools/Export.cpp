#include "stdafx.h"
#include "TtHideTools.h"
#include "EditListDialog.h"
#include "HookKeyboard.h"
#include "PatternMatch.h"

static bool match(LPCTSTR text, LPCTSTR pattern)
{
	switch (*pattern) {
	case _T('\0'):
		return	!*text;
	case _T('*') :
		return	match(text, pattern+1) || (*text && match(text+1, pattern));
	case _T('?') :
		return	*text && match(text+1, pattern+1);
	default  :
		return	(*text == *pattern) && match(text+1, pattern+1);
	}
}

extern "C" int __cdecl MATCH_WILDCARD(LPCTSTR pattern, LPCTSTR text)
{
	return match(text, pattern) ? 1 : 0;
}

extern "C" int __cdecl LIST_DESTROY(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	if(app->m_EditListDialog){
		delete app->m_EditListDialog;
		app->m_EditListDialog=NULL;
	}
	if(app->m_PatternMatch){
		delete app->m_PatternMatch;
		app->m_PatternMatch=NULL;
	}
	return 1;
}

extern "C" int __cdecl LIST_CREATE(LPCTSTR title, int match_mode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	if(app->m_EditListDialog) LIST_DESTROY();
	app->m_PatternMatch = new CPatternMatch(match_mode);
	app->m_EditListDialog = new CEditListDialog(NULL, app->m_PatternMatch);
	app->m_EditListDialog->m_Title = title;
	return 1;
}

extern "C" int __cdecl LIST_INIT_SEARCH(int sw)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	if(app->m_EditListDialog){
		app->m_EditListDialog->SetEnableText(sw);
		return 1;
	}
	else{
		return 0;
	}
}

extern "C" int __cdecl LIST_SET_SEARCH_TEXT(LPCTSTR text)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	if(app->m_EditListDialog){
		app->m_EditListDialog->m_InitSearch = text;
		return 1;
	}
	else{
		return 0;
	}
}

extern "C" int __cdecl LIST_ADD_STRING(LPTSTR list)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	if(app->m_EditListDialog){
		return app->m_EditListDialog->SetItems(list);
	}
	else{
		return 0;
	}
}

extern "C" int __cdecl LIST_ADD_STRING_FROM_FILE(LPTSTR path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	if(app->m_EditListDialog){
		return app->m_EditListDialog->SetItemsFromFile(path);
	}
	else{
		return 0;
	}
}

extern "C" int __cdecl LIST_SET_SIZE(int w, int h)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	if(app->m_EditListDialog){
		app->m_EditListDialog->m_width  = w;
		app->m_EditListDialog->m_height = h;
		return 1;
	}
	else{
		return 0;
	}
}

extern "C" LPCTSTR __cdecl LIST_SHOW(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	CHookKeyboard hook;
	if(app->m_EditListDialog){
		if(app->m_EditListDialog->DoModal()==IDOK){
			return app->m_EditListDialog->m_result;
		}
	}
	return _T("");
}

extern "C" int __cdecl LIST_GET_VIEW_NUM(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	return app->m_ResultStringArray.GetCount();
}

extern "C" LPCTSTR __cdecl LIST_GET_VIEW_ITEM(int index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CTtHideToolsApp* app = (CTtHideToolsApp*)AfxGetApp();
	return app->m_ResultStringArray[index];
}
