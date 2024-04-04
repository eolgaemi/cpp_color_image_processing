#pragma once
#include "afxdialogex.h"


// CParaDlg 대화 상자

class CParaDlg : public CDialog
{
	DECLARE_DYNAMIC(CParaDlg)

public:
	CParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	afx_msg void OnRangeRadioPara(UINT id);
	UINT m_radioIndex;
	virtual ~CParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
