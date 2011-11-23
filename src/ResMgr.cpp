#include "ResMgr.h"
#include "HGEDevice.h"
#include "WndBase.h"
#include <string>

CResMgr g_ResMgr;
CResMgr::CResMgr(void)
{
}

CResMgr::~CResMgr(void)
{
}

HTEXTURE CResMgr::GetHTexture( const char* pFileName )
{
	std::map < std::string, HTEXTURE >::iterator it = m_mapTexture.find( pFileName );
	HTEXTURE hTempTexture = 0;
	if( it != m_mapTexture.end() )
	{
		hTempTexture = it->second;
	}
	else
	{
		if( CWndBase::m_pDevice && CWndBase::m_pDevice->hge )
		{
			hTempTexture = CWndBase::m_pDevice->hge->Texture_Load( pFileName );
			std::string tempStr = pFileName;
			m_mapTexture.insert( make_pair(tempStr, hTempTexture ));
		}
	}
	return hTempTexture;
}