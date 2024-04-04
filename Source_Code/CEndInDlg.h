#pragma once
#include "afxdialogex.h"


// CEndInDlg 대화 상자

class CEndInDlg : public CDialog
{
	DECLARE_DYNAMIC(CEndInDlg)

public:
	CEndInDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEndInDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIST_ENDIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_endin;
};
