// 串口助手Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm1.h"
//}}AFX_INCLUDES

#if !defined(AFX_DLG_H__FA5C65B1_9DAF_4719_ADBB_E2819653E2D5__INCLUDED_)
#define AFX_DLG_H__FA5C65B1_9DAF_4719_ADBB_E2819653E2D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	CStatusBar m_StatusBar;
	COLORREF m_colorEditText; // edit控件的字体颜色
	COLORREF m_colorEditBK;  // edit控件的背景颜色
	CBrush* m_pEditBkBrush;
// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CComboBox	m_combo5_5;
	CComboBox	m_combo4_4;
	CComboBox	m_combo3_3;
	CComboBox	m_combo2_2;
	CComboBox	m_combo1_1;
	CEdit	m_edit1_1;
	CMSComm	m_mscomm;
	CString	m_edit1;
	int		m_combo1;
	int		m_combo2;
	int		m_combo3;
	int		m_combo4;
	int		m_combo5;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__FA5C65B1_9DAF_4719_ADBB_E2819653E2D5__INCLUDED_)
