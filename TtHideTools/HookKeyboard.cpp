#include "StdAfx.h"
#include "HookKeyboard.h"

#pragma data_seg("SHARE_DATA")
HHOOK CHookKeyboard::m_hHook=NULL;
#pragma data_seg()

HWND CHookKeyboard::m_hWnd=NULL;

CHookKeyboard::CHookKeyboard(void)
{
	m_hWnd  = NULL;
	m_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, AfxGetInstanceHandle(), 0);
}

CHookKeyboard::~CHookKeyboard(void)
{
	UnhookWindowsHookEx(m_hHook);
	m_hHook = NULL;
}

LRESULT CALLBACK CHookKeyboard::HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode==HC_ACTION){
		KBDLLHOOKSTRUCT*pK = (KBDLLHOOKSTRUCT*)lParam;
		if(pK->vkCode==VK_ESCAPE && (GetAsyncKeyState(VK_CONTROL) & 0x8000)){
			if(m_hWnd){
				::PostMessage(m_hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
			}
			return TRUE;
		}
	}
	return CallNextHookEx(m_hHook, nCode, wParam, lParam);
}

void CHookKeyboard::SetHWND(HWND hWnd)
{
	m_hWnd = hWnd;
}
