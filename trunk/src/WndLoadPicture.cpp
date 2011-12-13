#include "WndLoadPicture.h"
#include <hge.h>
#include <hgesprite.h>
#include "HGEDevice.h"
CWndLoadPicture::CWndLoadPicture(void):m_pSprite(NULL)
,m_fhScale(1.0f),m_fvScale(1.0f),m_strResPath("")
{
	m_bNeedMouseInput = false;
}

CWndLoadPicture::~CWndLoadPicture(void)
{
	delete m_pSprite;
	m_pSprite = NULL;
}

bool CWndLoadPicture::Create( int x, int y, const char* pPath, CWndBase* pParent, int nID, bool bDrawSprite, int ptDrawX, int ptDrawY, int ptDrawW, int ptDrawH )
{
	bool bRes = false;
	if( g_pDevice ) 
	{
		ResetRes(pPath,bDrawSprite,ptDrawX,ptDrawY,ptDrawW,ptDrawH);
		CWndBase::Create( x,y,m_size.cx,m_size.cy,pParent,nID);
	}
	else
	{
		//assert(false);
	}
	return bRes;
}
void CWndLoadPicture::OnDraw()
{
	DrawBox();
	if( m_pSprite )
	{
		g_pDevice->m_pHge->Gfx_SetTransform((float)m_rcAbsWnd.left,(float)m_rcAbsWnd.top,0,0,0,m_fhScale,m_fvScale);
		m_pSprite->Render((float)m_rcAbsWnd.left,(float)m_rcAbsWnd.top);
		g_pDevice->m_pHge->Gfx_SetTransform(0,0,0,0,0,1,1);
		
	}
	CWndBase::OnDraw();
}

void CWndLoadPicture::ResetRes( const char* pPath, bool bDrawSprite, int ptDrawX, int ptDrawY, int ptDrawW, int ptDrawH )
{
	int xStart = 0;
	int yStart = 0;
	int cx = 0;
	int cy = 0;
	if( g_pDevice && g_pDevice->m_pHge )
	{
		m_Texture = g_pDevice->Texture_Load( pPath );

		if( bDrawSprite || (m_Texture == 0) )
		{
			cx		= ptDrawW;
			cy		= ptDrawH;
			xStart	= ptDrawX;
			yStart	= ptDrawY;
		}
		else
		{
			cx = g_pDevice->m_pHge->Texture_GetWidth( m_Texture );
			cy = g_pDevice->m_pHge->Texture_GetHeight( m_Texture );
		}

		if( m_Texture != 0 )
		{
			m_strResPath = pPath;
		}

		SetWindowPos(NULL,0,0,cx,cy,0);

		if( !m_pSprite )
		{
			m_pSprite = new hgeSprite( m_Texture, (float)xStart, (float)yStart, (float)cx, (float)cy );
			m_pSprite->SetZ(0.5);
		}
		else
		{
			m_pSprite->SetTextureRect( (float)xStart, (float)yStart, (float)cx, (float)cy );
		}
	}
}
void CWndLoadPicture::SetFlip(bool bX,bool bY,bool bHotSpot )
{
	if( m_pSprite )
	{
		m_pSprite->SetFlip( bX, bY, bHotSpot );
	}
}

void CWndLoadPicture::SetColor( DWORD col, int i )
{
	if( m_pSprite )
	{
		m_pSprite->SetColor( col, i );
	}
}

void CWndLoadPicture::SetBlendMode( int blend )
{
	if ( m_pSprite )
	{
		m_pSprite->SetBlendMode( blend );
	}
}

void CWndLoadPicture::SetZoom( float hScale, float vScale )
{
	m_fhScale = hScale;
	m_fvScale = vScale;
}

void CWndLoadPicture::SetHotSpot( float x, float y )
{
	if( m_pSprite )
	{
		m_pSprite->SetHotSpot( x, y );
	}
}