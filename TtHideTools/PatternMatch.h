#pragma once

enum
{
	MATCH_MODE_STRSTR,
	MATCH_MODE_WILDCARD,
	MATCH_MODE_HMJRE,
	MATCH_MODE_HMJRE_NOCASESENSE,
	MATCH_MODE_MAX,
};

typedef	int (__cdecl *FINDREGULARNOCASESENSE)(LPCTSTR, LPCTSTR, int);
typedef	int (__cdecl *GETLASTMATCHLENGTH)(void);
typedef	int (__cdecl *JREGETVERSION)(void);

class CPatternMatch
{
private:
	int	m_mode;

private:
	static	HMODULE	m_hHmJre;
	static	FINDREGULARNOCASESENSE	FindRegular;
	static	GETLASTMATCHLENGTH		GetLastMatchLength;

public:
	CPatternMatch(int mode = MATCH_MODE_HMJRE);
	virtual ~CPatternMatch(void);

	int	Find(LPCTSTR src, LPCTSTR pattern, int& length);
};
