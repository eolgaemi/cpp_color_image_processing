// CLogicalDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CLogicalDlg.h"


// CLogicalDlg 대화 상자

IMPLEMENT_DYNAMIC(CLogicalDlg, CDialog)

CLogicalDlg::CLogicalDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LOGICAL, pParent)
	, m_radioIndex(0)
	, m_logicalVal(0)
{

}

CLogicalDlg::~CLogicalDlg()
{
}

void CLogicalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radioIndex);
	DDX_Text(pDX, IDC_LOGIC_VAL, m_logicalVal);
	DDV_MinMaxInt(pDX, m_logicalVal, 0, 255);
}


BEGIN_MESSAGE_MAP(CLogicalDlg, CDialog)
END_MESSAGE_MAP()


// CLogicalDlg 메시지 처리기


BOOL CLogicalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
