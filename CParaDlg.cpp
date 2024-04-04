// CParaDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CParaDlg.h"


// CParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CParaDlg, CDialog)

CParaDlg::CParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PARA, pParent)
	,m_radioIndex(0)
{

}

CParaDlg::~CParaDlg()
{
}

void CParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_PARA_RADIO1, (int&)m_radioIndex);
}


BEGIN_MESSAGE_MAP(CParaDlg, CDialog)
END_MESSAGE_MAP()


// CParaDlg 메시지 처리기
