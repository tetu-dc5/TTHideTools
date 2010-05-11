#pragma once

class CHookKeyboard
{
public:
	CHookKeyboard(void);
	virtual ~CHookKeyboard(void);
private:
	static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);
	static HHOOK m_hHook;
	static HWND m_hWnd;
public:
	static void SetHWND(HWND hWnd);
};
