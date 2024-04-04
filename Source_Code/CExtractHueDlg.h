#pragma once
#include "afxdialogex.h"


// CExtractHueDlg 대화 상자

class CExtractHueDlg : public CDialog
{
	DECLARE_DYNAMIC(CExtractHueDlg)

public:
	CExtractHueDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CExtractHueDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTRACT_HUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_extractLeft;
	int m_extractRight;
};
