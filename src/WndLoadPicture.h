#ifndef _WNDLOADPICTURE_H__
#define _WNDLOADPICTURE_H__
#include "wndbase.h"
#include "hge.h"
#include "DllExport.h"
class hgeSprite;
class WNDLIB_EXPORT CWndLoadPicture :
	public CWndBase
{
public:
	CWndLoadPicture(void);
	virtual ~CWndLoadPicture(void);
	virtual bool Create( int x, int y, const char* pPath, CWndBase* pParent, int nID, bool bDrawSprite, int ptDrawX, int ptDrawY, int ptDrawW, int ptDrawH );
	virtual void OnDraw();
	void ResetRes( const char* pPath, bool bDrawSprite, int ptDrawX, int ptDrawY, int ptDrawW, int ptDrawH );
	void SetFlip(bool bX,bool bY,bool bHotSpot = false );
	void SetColor( DWORD col, int i= -1 );
	void SetBlendMode(int blend);
	void SetZoom( float hScale, float vScale );
	void SetHotSpot( float x, float y );
public:
	std::string m_strResPath;
private:
	HTEXTURE m_Texture;
	hgeSprite* m_pSprite;
	float m_fhScale;
	float m_fvScale;
};


#endif
