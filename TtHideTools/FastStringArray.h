#pragma once

class CFastStringArray
{
private:
	int			m_limit_count;
	int			m_count;
	DWORD		m_limit_size;
	DWORD		m_size;
	DWORD		m_step_size;
	DWORD*		m_index_list;
	TCHAR*		m_buffer;

private:
	void	GrowIndex(void);
	void	GrowBuffer(void);

public:
	CFastStringArray(int init_count=100, DWORD init_size=0x10000, DWORD step_size=0x10000);
	virtual ~CFastStringArray(void);

	int		Add(LPCTSTR str);
	int		AddList(LPTSTR str, LPCTSTR fs=_T(","));
	int		AddListFromFile(LPCTSTR fname);
	LPCTSTR	GetAt(int index);
	LPCTSTR operator[](int index);
	void	RemoveAll(void)		{	m_count=0; m_size=0;	}
	int		GetCount(void)		{	return m_count;			}
};
