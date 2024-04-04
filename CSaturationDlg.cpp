// CSaturationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CSaturationDlg.h"


// CSaturationDlg 대화 상자

IMPLEMENT_DYNAMIC(CSaturationDlg, CDialog)

CSaturationDlg::CSaturationDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SATURATION, pParent)
	, m_saturation(0)
{

}

CSaturationDlg::~CSaturationDlg()
{
}

void CSaturationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SATURATION, m_saturation);
	DDV_MinMaxDouble(pDX, m_saturation, -1.0, 1.0);
}


BEGIN_MESSAGE_MAP(CSaturationDlg, CDialog)
END_MESSAGE_MAP()


// CSaturationDlg 메시지 처리기
