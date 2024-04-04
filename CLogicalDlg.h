#pragma once
#include "afxdialogex.h"


// CLogicalDlg 대화 상자

class CLogicalDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogicalDlg)

public:
	CLogicalDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLogicalDlg();
	UINT m_radioIndex;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGICAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_logicalVal;
	virtual BOOL OnInitDialog();
};
