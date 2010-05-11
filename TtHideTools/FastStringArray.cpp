#include "StdAfx.h"
#include "FastStringArray.h"

CFastStringArray::CFastStringArray(int init_count, DWORD init_size, DWORD step_size)
: m_limit_count(init_count)
, m_count(0)
, m_limit_size(init_size)
, m_size(0)
, m_step_size(step_size)
, m_index_list(NULL)
, m_buffer(NULL)
{
	m_index_list = new DWORD[m_limit_count];
	m_buffer = new TCHAR[m_limit_size];
}

CFastStringArray::~CFastStringArray(void)
{
	if(m_index_list)
	{
		delete [] m_index_list;
	}
	if(m_buffer)
	{
		delete [] m_buffer;
	}
}

void CFastStringArray::GrowIndex(void)
{
	int new_limit = m_limit_count*2;
	DWORD*	tmp = new DWORD[new_limit];
	memcpy(tmp, m_index_list, sizeof(DWORD)*m_count);
	delete [] m_index_list;
	m_index_list = tmp;
	m_limit_count = new_limit;
}

void CFastStringArray::GrowBuffer(void)
{
	DWORD	new_limit = m_limit_size + m_step_size;
	TCHAR*	tmp = new TCHAR[new_limit];
	memcpy(tmp, m_buffer, m_size);
	delete [] m_buffer;
	m_buffer = tmp;
	m_limit_size = new_limit;
}

int CFastStringArray::Add(LPCTSTR str)
{
	if(m_count>=m_limit_count) GrowIndex();
	int len = _tcslen(str) + 1;
	if(m_size + len > m_limit_size) GrowBuffer();
	m_index_list[m_count] = m_size;
	memcpy(m_buffer + m_size, str, sizeof(TCHAR)*len);
	m_count++;
	m_size += len;
	return m_count-1;
}

int CFastStringArray::AddList(LPTSTR str, LPCTSTR fs)
{
	TCHAR*	context = NULL;
	TCHAR*	tok = _tcstok_s(str, fs, &context);
	while(tok != NULL){
		Add(tok);
		tok = _tcstok_s(NULL, fs, &context);
	}
	return m_count-1;
}

int CFastStringArray::AddListFromFile(LPCTSTR fname)
{
	FILE*	fp;
	errno_t err = _tfopen_s(&fp, fname, _T("rt"));
	if(err) return 0;
	TCHAR	buf[4096];
	for(;;){
		TCHAR*	p = _fgetts(buf, 4096, fp);
		if(!p) break;
		int len = _tcslen(p);
		for(int i=0;i<len;i++){
			if(p[i]==_T('\n') || p[i]==_T('\r')){
				p[i] = _T('\0');
				break;
			}
		}
		if(_tcslen(p)) Add(p);
	}
	fclose(fp);
	return m_count-1;
}

LPCTSTR	CFastStringArray::GetAt(int index)
{
	if(index<0) return NULL;
	if(index>=m_count) return NULL;
	return m_buffer + m_index_list[index];
}

LPCTSTR CFastStringArray::operator[](int index)
{
	return GetAt(index);
}
