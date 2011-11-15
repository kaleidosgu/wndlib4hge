#include "WndDesktop.h"
#include "HGEDevice.h"
#include "wnddatadefine.h"
#include <hge.h>
CWndDesktop::CWndDesktop(void)
{
	memset(&m_event,0,sizeof(hgeInputEvent));
	m_nLastKey = 0;
	m_bKeyProcess = false;
}

CWndDesktop::~CWndDesktop(void)
{
}

void CWndDesktop::OnUpdate( float ft )
{
	if( m_pDevice && m_pDevice->hge )
	{
		if ( m_bKeyProcess )
		{
			memset(&m_event,0,sizeof(hgeInputEvent));
			m_bKeyProcess = false;
		}

		if( !m_bKeyProcess )
		{
			int nTempKey = m_pDevice->hge->Input_GetKey();
			int keychar = m_pDevice->hge->Input_GetChar();
			if( m_nLastKey > 0 )
			{
				bool bKeyUp = m_pDevice->hge->Input_KeyUp(m_nLastKey);
				if ( bKeyUp )
				{
					m_event.type = INPUT_KEYUP;
					m_event.key = m_nLastKey;
					m_nLastKey = nTempKey;
					m_bKeyProcess = true;
				}
			}
			if ( nTempKey > HGEK_MBUTTON )
			{	
				m_nLastKey = nTempKey;
				if( m_nLastKey > 0 )
				{
					bool bKeyDown = m_pDevice->hge->Input_KeyDown(m_nLastKey);
					m_event.type = INPUT_KEYDOWN;
					m_bKeyProcess = true;
					m_event.key = m_nLastKey;
					m_event.chr = keychar;
				}
			}

			if( m_event.type == INPUT_KEYDOWN )
			{
				OnKeyboardMessage( m_event );
			}
			else if( m_event.type == INPUT_KEYUP )
			{
				OnKeyboardMessage( m_event );
			}
			float fx = 0;
			float fy = 0;
			m_pDevice->hge->Input_GetMousePos(&fx,&fy);
			m_ptMouse.x = (LONG)fx;
			m_ptMouse.y = (LONG)fy;

			//m_bLPressed  = m_pDevice->hge->Input_KeyDown(HGEK_LBUTTON);
			m_bLPressed = m_pDevice->hge->Input_GetKeyState(HGEK_LBUTTON);
			m_bLReleased = m_pDevice->hge->Input_KeyUp(HGEK_LBUTTON);
			m_bRPressed  = m_pDevice->hge->Input_KeyDown(HGEK_RBUTTON);
			m_bRReleased = m_pDevice->hge->Input_KeyUp(HGEK_RBUTTON);
		}
	}
	CWndBase::OnUpdate( ft );
}

int CWndDesktop::OnMouseInput()
{
	CWndBase* pWnd = NULL;
	int lRet = WND_RESULT_NO;

	if( false )
	{
	}
	else
	{
		if(lRet == WND_RESULT_NO)
		{
			pWnd = GetChildWndPtIn(m_ptMouse);
			if( !pWnd )
			{
				m_pWndCursorIn = this;
			}
			if ( pWnd )
			{
				pWnd->OnMouseInput();
			}
		}
	}

	if(m_pWndCursorInLast != m_pWndCursorIn)
	{
		POINT pt = {-65535, -65535};
		if (m_pWndCursorInLast) 
		{
			if(m_pWndCursorInLast->IsWindowEnabled())
			{
				m_pWndCursorInLast->OnMouseMoveOut(0, pt);
			}
		}
		if( m_pWndCursorIn )
		{
			m_pWndCursorIn->OnMouseMoveIn(0,m_ptMouse);
		}
		m_pWndCursorInLast = m_pWndCursorIn;
	}

	return WND_RESULT_NO;
}

int CWndDesktop::OnKeyboardMessage( const hgeInputEvent& rEvent )
{
	int nRes = WND_RESULT_NO;
	if( rEvent.type == INPUT_KEYDOWN || rEvent.type == INPUT_KEYUP )
	{
		if (nRes == WND_RESULT_NO && m_pWndFocus != NULL && m_pWndFocus != this) 
		{
			nRes = m_pWndFocus->ProcessKeyboardMessage( rEvent );
		}

		if ( nRes == WND_RESULT_NO )
		{
			//if(m_listModalWnd.size() > 0)
			if( false )
			{
				//nRes = m_listModalWnd.back()->OnKeyboardMessage( rEvent );
			}
			else
			{
				//���Ǽ��ټ��򽻸����ϲ㴰�ڴ���
				std::list< CWndBase* >::reverse_iterator itChild = m_listChildren.rbegin();
				while( nRes == WND_RESULT_NO && itChild != m_listChildren.rend())
				{
					nRes = (*itChild)->OnKeyboardMessage( rEvent );
					itChild ++;
				}
			}
		}
	}

	return nRes;
}