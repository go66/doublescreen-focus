
// DoubleScreenFocusDlg.h
//

#pragma once


// CDoubleScreenFocusDlg
class CDoubleScreenFocusDlg : public CDialogEx
{

public:
	CDoubleScreenFocusDlg(CWnd* pParent = nullptr);


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOUBLESCREENFOCUS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
