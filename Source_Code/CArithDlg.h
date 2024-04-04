#pragma once
#include "afxdialogex.h"


// CArithDlg 대화 상자

class CArithDlg : public CDialog
{
	DECLARE_DYNAMIC(CArithDlg)

public:
	CArithDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CArithDlg();
	afx_msg void OnRangeRadioArith(UINT id);
	UINT m_radioIndex;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARITH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_arithVal;
	virtual BOOL OnInitDialog();
	char m_arithRadio;
};
