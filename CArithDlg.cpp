// CArithDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CArithDlg.h"


// CArithDlg 대화 상자

IMPLEMENT_DYNAMIC(CArithDlg, CDialog)

CArithDlg::CArithDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ARITH, pParent)
	,m_radioIndex(0),m_arithRadio(0),m_arithVal(0)
{

}

CArithDlg::~CArithDlg()
{
}

void CArithDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radioIndex);
	DDX_Text(pDX, IDC_ARITH_VAL, m_arithVal);
	DDV_MinMaxDouble(pDX, m_arithVal, 0.0, 255.0);
}

// CArithDlg 메시지 처리기
BEGIN_MESSAGE_MAP(CArithDlg, CDialog)
	ON_CONTROL_RANGE(IDOK, IDC_RADIO1, IDC_RADIO4, &CArithDlg::OnRangeRadioArith)
END_MESSAGE_MAP()

void CArithDlg::OnRangeRadioArith(UINT id) {
	
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);
	switch (id)
	{
	case IDC_RADIO1:
		m_arithRadio = '+';
		break;
	case IDC_RADIO2:
		m_arithRadio = '-';
		break;
	case IDC_RADIO3:
		m_arithRadio = '*';
		break;
	case IDC_RADIO4:
		m_arithRadio = '/';
		break;
	}
	
	m_arithRadio = 'a';

}

BOOL CArithDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
