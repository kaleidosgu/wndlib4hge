#include "HGEDevice.h"
#include <hge.h>
HGEDevice* g_pDevice = NULL;
#include <string>
HGEDevice::HGEDevice(void)
:m_pHge(0)
{
	m_pHge = hgeCreate(HGE_VERSION);
}

HGEDevice::~HGEDevice(void)
{
}

void HGEDevice::RenderLine( int x1, int y1, int x2, int y2,unsigned int cr )
{
	float fx1 = (float)x1;
	float fx2 = (float)x2;
	float fy1 = (float)y1;
	float fy2 = (float)y2;

	m_pHge->Gfx_RenderLine(fx1,fy1,fx2,fy2,cr);
}

void HGEDevice::Draw2DRectDr( DWORD dwColor, RECT rcToDraw )
{

	float x1,y1,x2,y2;
	x1 = (float)rcToDraw.left;
	y1 = (float)rcToDraw.top;
	x2 = (float)rcToDraw.right;
	y2 = (float)rcToDraw.bottom;


	m_pHge->Gfx_RenderLine(x1,y1,x2,y1,dwColor);
	m_pHge->Gfx_RenderLine(x2,y1,x2,y2,dwColor);
	m_pHge->Gfx_RenderLine(x2,y2,x1,y2,dwColor);
	m_pHge->Gfx_RenderLine(x1,y2,x1,y1,dwColor);
}

void HGEDevice::Init( HWND wnid )
{
	m_pHge = hgeCreate(HGE_VERSION);
	// Set desired system states and initialize HGE
	m_pHge->System_SetState(HGE_LOGFILE, "SuperPig.log");
	//m_pHge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	//m_pHge->System_SetState(HGE_RENDERFUNC, &QD3DWidget::RenderFunc);
	m_pHge->System_SetState(HGE_TITLE, "SuperPigChess");
	m_pHge->System_SetState(HGE_FPS, 100);
	m_pHge->System_SetState(HGE_USESOUND, true);
	m_pHge->System_SetState(HGE_WINDOWED, true);
	m_pHge->System_SetState(HGE_SCREENWIDTH, 800);
	m_pHge->System_SetState(HGE_SCREENHEIGHT, 600);
	m_pHge->System_SetState(HGE_SCREENBPP, 32);
	m_pHge->System_SetState(HGE_SHOWSPLASH,false); 
	m_pHge->System_SetState(HGE_DONTSUSPEND,true); 
	m_pHge->System_SetState(HGE_ZBUFFER,true);

	if(m_pHge->System_Initiate(wnid))
	{
		m_pHge->System_Start();
	}
}

void HGEDevice::Gfx_BeginScene()
{
	m_pHge->Gfx_BeginScene();
	m_pHge->Gfx_Clear(0);
}

void HGEDevice::Gfx_EndScene()
{
	m_pHge->Gfx_EndScene();
}

void HGEDevice::Gfx_EndScene( HWND hwnd )
{
	m_pHge->Gfx_EndScene(hwnd);
}

void HGEDevice::Release()
{
	m_pHge->System_Shutdown();
	m_pHge->Release();
}

HTEXTURE HGEDevice::Texture_Load( const char* pchar )
{
	std::string strTemp = pchar;
	std::map < std::string, HTEXTURE >::iterator it = m_mapTexture.find( strTemp );
	HTEXTURE hTemp = NULL;
	if( it == m_mapTexture.end() )
	{
		hTemp = m_pHge->Texture_Load( strTemp.c_str() );
		m_mapTexture.insert( make_pair( strTemp, hTemp));
	}
	else
	{
		hTemp = it->second;
	}
	return hTemp;
}