#pragma once
#include "afxdialogex.h"


// CZoomOutDlg 대화 상자

class CZoomOutDlg : public CDialog
{
	DECLARE_DYNAMIC(CZoomOutDlg)

public:
	CZoomOutDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZoomOutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOM_OUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_zoomout;
};
