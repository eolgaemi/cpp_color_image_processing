// CRotateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing1.0.h"
#include "afxdialogex.h"
#include "CRotateDlg.h"


// CRotateDlg 대화 상자

IMPLEMENT_DYNAMIC(CRotateDlg, CDialog)

CRotateDlg::CRotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ROTATE, pParent)
	, m_rotateVal(0)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROTATE_VAL, m_rotateVal);
	DDV_MinMaxInt(pDX, m_rotateVal, -360, 360);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
END_MESSAGE_MAP()


// CRotateDlg 메시지 처리기
