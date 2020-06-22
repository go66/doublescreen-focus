
// DoubleScreenFocus.h
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"


// CDoubleScreenFocusApp:
//

class CDoubleScreenFocusApp : public CWinApp
{
public:
	CDoubleScreenFocusApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CDoubleScreenFocusApp theApp;
