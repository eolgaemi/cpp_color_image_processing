// CZoomInDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CZoomInDlg.h"


// CZoomInDlg 대화 상자

IMPLEMENT_DYNAMIC(CZoomInDlg, CDialog)

CZoomInDlg::CZoomInDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ZOOMIN, pParent)
	, m_zoomin(0)
{

}

CZoomInDlg::~CZoomInDlg()
{
}

void CZoomInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZOOM_IN, m_zoomin);
	DDV_MinMaxInt(pDX, m_zoomin, 1, 5);
}


BEGIN_MESSAGE_MAP(CZoomInDlg, CDialog)
END_MESSAGE_MAP()


// CZoomInDlg 메시지 처리기
