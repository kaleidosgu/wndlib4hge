#pragma once
#include <hge.h>
#include <map>
#include "DllExport.h"
class WNDLIB_EXPORT CResMgr
{
public:
	CResMgr(void);
	virtual ~CResMgr(void);
	HTEXTURE GetHTexture( const char* pFileName );
private:
	std::map < std::string, HTEXTURE > m_mapTexture;
};

extern WNDLIB_EXPORT CResMgr g_ResMgr;