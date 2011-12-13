#pragma once
#include "wndbase.h"
#include <hge.h>
#include "DllExport.h"
class WNDLIB_EXPORT CWndDesktop :
	public CWndBase
{
public:
	CWndDesktop(void);
	virtual ~CWndDesktop(void);
	virtual void OnUpdate( float ft );
	virtual int OnMouseInput();
	virtual int OnKeyboardMessage( const hgeInputEvent& rEvent );
private:
	hgeInputEvent m_event;
	int m_nLastKey;
	bool m_bKeyProcess;
};

extern WNDLIB_EXPORT CWndDesktop* g_pDesktop;