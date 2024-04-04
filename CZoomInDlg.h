#pragma once
#include "afxdialogex.h"


// CZoomInDlg 대화 상자

class CZoomInDlg : public CDialog
{
	DECLARE_DYNAMIC(CZoomInDlg)

public:
	CZoomInDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZoomInDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_zoomin;
};
