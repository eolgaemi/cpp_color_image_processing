// CEndInDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CEndInDlg.h"


// CEndInDlg 대화 상자

IMPLEMENT_DYNAMIC(CEndInDlg, CDialog)

CEndInDlg::CEndInDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HIST_ENDIN, pParent)
	, m_endin(0)
{

}

CEndInDlg::~CEndInDlg()
{
}

void CEndInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HIST_ENDIN, m_endin);
	DDV_MinMaxInt(pDX, m_endin, 0, 255);
}


BEGIN_MESSAGE_MAP(CEndInDlg, CDialog)
END_MESSAGE_MAP()


// CEndInDlg 메시지 처리기
