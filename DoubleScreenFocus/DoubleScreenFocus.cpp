
// DoubleScreenFocus.cpp
//

#include "pch.h"
#include "framework.h"
#include "DoubleScreenFocus.h"
#include "DoubleScreenFocusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDoubleScreenFocusApp
BEGIN_MESSAGE_MAP(CDoubleScreenFocusApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDoubleScreenFocusApp
CDoubleScreenFocusApp::CDoubleScreenFocusApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CDoubleScreenFocusApp theApp;


LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;

	int x = p->pt.x;
	int y = p->pt.y;

	static auto cx = ::GetSystemMetrics(SM_CXSCREEN);
	static auto cy = ::GetSystemMetrics(SM_CYSCREEN);

	static auto xv = ::GetSystemMetrics(SM_XVIRTUALSCREEN);
	static auto yv = ::GetSystemMetrics(SM_YVIRTUALSCREEN);
	static auto cxv = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);
	static auto cyv = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);

	static bool is_main_screen = false;

	if (x <= cx)
	{
		if (!is_main_screen)
		{
			theApp.m_pMainWnd->SetWindowPos(&CWnd::wndTopMost, cx, yv, cxv, cyv, SWP_SHOWWINDOW);
			is_main_screen = true;
		}
	}
	else
	{
		if (is_main_screen)
		{
			theApp.m_pMainWnd->SetWindowPos(&CWnd::wndTopMost, 0, 0, cx, cy, SWP_SHOWWINDOW);
			is_main_screen = false;
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

BOOL CDoubleScreenFocusApp::InitInstance()
{
	TCHAR lpszTempPath[256] = { 0 };
	CString sTempFile;
	CFile myFile;
	CFileException fileException;
	
	GetTempPath(256, lpszTempPath);
	sTempFile.Format(L"%s/DSF_TEMP_5B614B92-FD0E-422C-831E-CDC7E3FDB124.txt", lpszTempPath);

	// mutex
	if (!myFile.Open(sTempFile, CFile::modeCreate | CFile::modeReadWrite, &fileException))
	{
		return FALSE;
	}

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	CDoubleScreenFocusDlg dlg;
	m_pMainWnd = &dlg;

	// two screen
	auto monitors = ::GetSystemMetrics(SM_CMONITORS);
	if (monitors != 2) return FALSE;

	// Set mouse hook
	HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, theApp.m_hInstance, NULL);

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
	}

	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	UnhookWindowsHookEx(mouseHook);

	return FALSE;
}

