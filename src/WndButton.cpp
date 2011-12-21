#include "Wndbutton.h"
#include "WndLoadPicture.h"
#include "UIDefine.h"
CWndButton::CWndButton(void)
:m_pPicture(NULL),m_nBtnState(-1)
{
	m_nDrawX = 0;
	m_nDrawY = 0;
	m_nDrawCX = 0;
	m_nDrawCY = 0;

	m_strPath = "";
	m_nWndType = UI_CREATE_WNDBUTTON;
}
CWndButton::~CWndButton(void)
{
}
bool CWndButton::Create( int x, int y, int cx, int cy,const char* pPath, CWndBase* pParent, int nID )
{
	m_strPath = pPath;
	m_pPicture = new CWndLoadPicture;
	m_pPicture->Create(0,0,pPath,this,0,false,0,0,0,0);
	m_pPicture->SetEditProcess( false );
	return CWndBase::Create(x,y,cx,cy,pParent,nID);
}

int CWndButton::OnMouseMoveIn( const UINT &nFlags,const POINT &point )
{
	if( m_bLPressed )
	{
		SetBtnState( down );
	}
	else
	{
		SetBtnState( focus );
	}
	return CWndBase::OnMouseMoveIn( nFlags, point );
}

int CWndButton::OnMouseMoveOut( const UINT &nFlags,const POINT &point )
{
	SetBtnState( normal );
	return CWndBase::OnMouseMoveOut( nFlags, point );
}

int CWndButton::OnMouseMove( const UINT &nFlags,const POINT &point )
{
	if( m_bLPressed )
	{
		SetBtnState( down );
	}
	else
	{
		if ( m_nBtnState != focus )
		{
			SetBtnState( focus );
		}
	}
	return CWndBase::OnMouseMove( nFlags, point );
}

int CWndButton::OnLButtonDown( const UINT &nFlags,const POINT &point )
{
	if( m_pWndCursorIn == this )
	{
		SetBtnState( down );
	}
	return WND_RESULT_YES;
	//return CWndBase::OnLButtonDown( nFlags, point );
}


int CWndButton::OnLButtonUp( const UINT &nFlags,const POINT &point )
{
	return WND_RESULT_YES;
}
int CWndButton::OnLButtonClick( const UINT &nFlags, const POINT &point )
{
	if( m_pWndCursorIn == this )
	{
		SetBtnState( focus );
	}
	OnClick();
	return WND_RESULT_YES;
}

void CWndButton::SetBtnState( int nBtnState )
{
	if ( m_nBtnState != nBtnState )
	{
		m_nBtnState = nBtnState;
		if( (int)m_vecRes.size() > nBtnState && nBtnState >= 0 )
		{
			const ResStruct& rRes = m_vecRes[nBtnState];
			m_nDrawX		= rRes.x;
			m_nDrawY		= rRes.y;
			m_nDrawCX		= rRes.w;
			m_nDrawCY		= rRes.h;
			m_pPicture->ResetRes(m_strPath.c_str(),true,m_nDrawX,m_nDrawY,m_nDrawCX,m_nDrawCY);
		}
	}
	
	/*
	if ( m_nBtnState != nBtnState )
	{
		m_pPicture->ResetRes(m_strPath.c_str(),true,0,378,33,34);
	}
	*/
}

void CWndButton::OnDraw()
{
	CWndBase::OnDraw();
}

void CWndButton::AddRes( int x, int y, int cx, int cy )
{
	ResStruct rStruct;
	rStruct.x = x;
	rStruct.y = y;
	rStruct.w = cx;
	rStruct.h = cy;
	m_vecRes.push_back( rStruct );
	SetBtnState(normal);
}

void CWndButton::OnClick()
{
	SendMessageToParent(WND_CLICK,m_nDlgID);
}

void CWndButton::SetDataFile( const char* pFilePath, int xStart, int yStart, int nWidth, int nHeight )
{
	m_vecRes.clear();
	m_strPath = pFilePath;
	bool bHorizontal = true;
	if( nWidth < nHeight )
	{
		bHorizontal = false;
	}
	int cx = 0;
	int cy = 0;
	if( bHorizontal )
	{
		cx = nWidth / 4;
		cy = nHeight;
	}
	else
	{
		cx = nWidth;
		cy = nHeight / 4;
	}
	for( size_t szIdx = 0; szIdx < 4; szIdx++ )
	{
		ResStruct rStruct;
		if( bHorizontal )
		{
			rStruct.x = xStart + szIdx * cx;
			rStruct.y = yStart;
		}
		else
		{
			rStruct.x = xStart;
			rStruct.y = yStart + szIdx * cy;
		}
		rStruct.w = cx;
		rStruct.h = cy;
		m_vecRes.push_back( rStruct );
	}
	ResizeWindow(cx,cy);
	SetBtnState(-1);
	SetBtnState(normal);
}