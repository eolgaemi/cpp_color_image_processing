#pragma once
#include "afxdialogex.h"


// CSaturationDlg 대화 상자

class CSaturationDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaturationDlg)

public:
	CSaturationDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSaturationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SATURATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_saturation;
};
