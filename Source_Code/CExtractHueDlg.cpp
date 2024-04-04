// CExtractHueDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CExtractHueDlg.h"


// CExtractHueDlg 대화 상자

IMPLEMENT_DYNAMIC(CExtractHueDlg, CDialog)

CExtractHueDlg::CExtractHueDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EXTRACT_HUE, pParent)
	, m_extractLeft(0)
	, m_extractRight(0)
{

}

CExtractHueDlg::~CExtractHueDlg()
{
}

void CExtractHueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EXL, m_extractLeft);
	DDV_MinMaxInt(pDX, m_extractLeft, 0, 360);
	DDX_Text(pDX, IDC_EXR, m_extractRight);
	DDV_MinMaxInt(pDX, m_extractRight, 0, 360);
}


BEGIN_MESSAGE_MAP(CExtractHueDlg, CDialog)
END_MESSAGE_MAP()


// CExtractHueDlg 메시지 처리기
