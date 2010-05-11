#include "StdAfx.h"
#include "PatternMatch.h"

extern "C" int __cdecl MATCH_WILDCARD(LPCTSTR pattern, LPCTSTR text);

HMODULE					CPatternMatch::m_hHmJre = NULL;
FINDREGULARNOCASESENSE	CPatternMatch::FindRegular = NULL;
GETLASTMATCHLENGTH		CPatternMatch::GetLastMatchLength = NULL;

CPatternMatch::CPatternMatch(int mode)
: m_mode(mode)
{
	if(m_mode<0 || m_mode>=MATCH_MODE_MAX) m_mode = MATCH_MODE_STRSTR;
	if(m_mode==MATCH_MODE_HMJRE || m_mode==MATCH_MODE_HMJRE_NOCASESENSE){
		m_hHmJre = ::LoadLibrary("HmJre.dll");
		if(!m_hHmJre){
			m_mode = MATCH_MODE_STRSTR;
		}
		else{
			FindRegular = (FINDREGULARNOCASESENSE)::GetProcAddress(m_hHmJre, "FindRegular");
			GetLastMatchLength     = (GETLASTMATCHLENGTH)::GetProcAddress(m_hHmJre, "GetLastMatchLength");
			if(!FindRegular || !GetLastMatchLength){
				::FreeLibrary(m_hHmJre);
				m_hHmJre = NULL;
				m_mode = MATCH_MODE_STRSTR;
			}
		}
	}
}

CPatternMatch::~CPatternMatch(void)
{
	if(m_hHmJre){
		::FreeLibrary(m_hHmJre);
		m_hHmJre = NULL;
	}
}

int	CPatternMatch::Find(LPCTSTR src, LPCTSTR pattern, int& length)
{
	int	result = -1;
	length = 0;

	switch(m_mode)
	{
	case MATCH_MODE_STRSTR:
		result = CString(src).Find(pattern);
		if(result>=0){
			length = _tcslen(pattern);
		}
		return result;
	case MATCH_MODE_WILDCARD:
		if(MATCH_WILDCARD(pattern, src)){
			length = _tcslen(src);
			return 0;
		}
		return -1;
	case MATCH_MODE_HMJRE:
		result = FindRegular(pattern, src, 0);
		if(result>=0){
			length = GetLastMatchLength();
		}
		return result;
	}
	return -1;
}
