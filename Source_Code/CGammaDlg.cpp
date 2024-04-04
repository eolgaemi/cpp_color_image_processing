// CGammaDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CGammaDlg.h"


// CGammaDlg 대화 상자

IMPLEMENT_DYNAMIC(CGammaDlg, CDialog)

CGammaDlg::CGammaDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GAMMA, pParent)
	, m_gamma(0)
{

}

CGammaDlg::~CGammaDlg()
{
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAMMA, m_gamma);
	DDV_MinMaxDouble(pDX, m_gamma, 0.0, 2.0);
}


BEGIN_MESSAGE_MAP(CGammaDlg, CDialog)
END_MESSAGE_MAP()


// CGammaDlg 메시지 처리기
