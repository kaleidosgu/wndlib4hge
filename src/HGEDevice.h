#pragma once
#include <map>
#include "datadefine.h"
#include <WTypes.h>
#include <hge.h>
#include "DllExport.h"
class HGE;
class hgeSprite;
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
class WNDLIB_EXPORT HGEDevice
{
public:
	HGEDevice(void);
	virtual ~HGEDevice(void);
	virtual void RenderLine( int x1, int y1, int x2, int y2,unsigned int cr );
	virtual void Draw2DRectDr(DWORD dr, RECT rcToDraw );

	void Init( HWND wnid );
	void InitState( HWND wnid );
	void InitSystem( HWND wnid );
	void Gfx_BeginScene();
	void Gfx_EndScene();
	void Gfx_EndScene( HWND hwnd );
	void Release();
	HTEXTURE Texture_Load( const char* pchar );

	HGE* m_pHge;
private:
	std::map < std::string, HTEXTURE > m_mapTexture;
};
extern WNDLIB_EXPORT HGEDevice* g_pDevice;