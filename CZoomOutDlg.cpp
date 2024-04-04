// CZoomOutDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CZoomOutDlg.h"


// CZoomOutDlg 대화 상자

IMPLEMENT_DYNAMIC(CZoomOutDlg, CDialog)

CZoomOutDlg::CZoomOutDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ZOOM_OUT, pParent)
	, m_zoomout(0)
{

}

CZoomOutDlg::~CZoomOutDlg()
{
}

void CZoomOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZOOM_OUT, m_zoomout);
	DDV_MinMaxInt(pDX, m_zoomout, 1, 5);
}


BEGIN_MESSAGE_MAP(CZoomOutDlg, CDialog)
END_MESSAGE_MAP()


// CZoomOutDlg 메시지 처리기
