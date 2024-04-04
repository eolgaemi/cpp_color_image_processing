
// ColorImageProcessing1.0Doc.cpp: CColorImageProcessing10Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageProcessing1.0.h"
#endif

#include "ColorImageProcessing1.0Doc.h"
#include "CArithDlg.h"
#include "CGammaDlg.h"
#include "CParaDlg.h"
#include "CEndInDlg.h"
#include "CRotateDlg.h"
#include "CSaturationDlg.h"
#include "CExtractHueDlg.h"
#include "CLogicalDlg.h"
#include "CZoomOutDlg.h"
#include "CZoomInDlg.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImageProcessing10Doc

IMPLEMENT_DYNCREATE(CColorImageProcessing10Doc, CDocument)

BEGIN_MESSAGE_MAP(CColorImageProcessing10Doc, CDocument)
END_MESSAGE_MAP()


// CColorImageProcessing10Doc 생성/소멸

CColorImageProcessing10Doc::CColorImageProcessing10Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImageProcessing10Doc::~CColorImageProcessing10Doc()
{
}

BOOL CColorImageProcessing10Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}

// CColorImageProcessing10Doc serialization

void CColorImageProcessing10Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CColorImageProcessing10Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CColorImageProcessing10Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImageProcessing10Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorImageProcessing10Doc 진단

#ifdef _DEBUG
void CColorImageProcessing10Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImageProcessing10Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImageProcessing10Doc 명령

// 2차원 unsigned char 배열 메모리 할당
unsigned char** CColorImageProcessing10Doc::OnMalloc2D(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;

	memory = new unsigned char* [height];

	for (int h = 0; h < height; h++) {
		memory[h] = new unsigned char[width];
	}

	return memory;
}
// 2차원 모든 자료형 배열 메모리 할당
template <typename T>
void CColorImageProcessing10Doc::OnFree2D(T** memory, int height)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL) {
		return;
	}
	else {
		for (int h = 0; h < height; h++) {
			delete memory[h];
		}
		delete[] memory;
	}
}

// 입력 이미지 메모리 해제
void CColorImageProcessing10Doc::OnFreeInimage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_inImageR != NULL) {

		OnFree2D(m_inImageR, m_inH);
		OnFree2D(m_inImageG, m_inH);
		OnFree2D(m_inImageB, m_inH);

		m_inImageR = m_inImageG = m_inImageB = NULL;

		m_inH = 0;
		m_inW = 0;
	}
}

// 출력 이미지 메모리 해제
void CColorImageProcessing10Doc::OnFreeOutimage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = 0;
		m_outW = 0;
	}
}


BOOL CColorImageProcessing10Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CImage image;
	image.Load(lpszPathName);

	OnFreeInimage();
	OnFreeOutimage();
	OnFreeBackimage();

	m_inH = image.GetHeight();
	m_inW = image.GetWidth();

	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);

	COLORREF px;

	for (int h = 0; h < m_inH; h++) {
		for (int w = 0; w < m_inW; w++) {
			px = image.GetPixel(w, h);
			m_inImageR[h][w] = GetRValue(px);
			m_inImageG[h][w] = GetGValue(px);
			m_inImageB[h][w] = GetBValue(px);
		}
	}

	return TRUE;
}


void CColorImageProcessing10Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);

	// 출력이미지 메모리 해제
	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);

	OnFree2D(m_backImageR, m_backH);
	OnFree2D(m_backImageG, m_backH);
	OnFree2D(m_backImageB, m_backH);

	CDocument::OnCloseDocument();
}


void CColorImageProcessing10Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int h = 0; h < m_outH; h++) {
		for (int w = 0; w < m_outW; w++) {
			m_outImageR[h][w] = m_inImageR[h][w];
			m_outImageG[h][w] = m_inImageG[h][w];
			m_outImageB[h][w] = m_inImageB[h][w];
		}
	}

}


void CColorImageProcessing10Doc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int h = 0; h < m_outH; h++) {
		for (int w = 0; w < m_outW; w++) {
			double avg = double((m_inImageR[h][w] + m_inImageG[h][w] + m_inImageB[h][w])) / 3.0;
			m_outImageR[h][w] = unsigned char(avg);
			m_outImageG[h][w] = unsigned char(avg);
			m_outImageB[h][w] = unsigned char(avg);
		}
	}
}

// 산술연산
void CColorImageProcessing10Doc::OnArith()
{
	// TODO: 여기에 구현 코드 추가.
	CArithDlg arith;
	if (arith.DoModal() != IDOK) {
		return;
	}
	else {
		// 기존 출력 이미지 메모리 해제
		OnFreeOutimage();
		OnFreeBackimage();
		// 출력 이미지 크기 복사
		m_outH = m_inH;
		m_outW = m_inW;

		// 출력 이미지 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int index = arith.m_radioIndex;
		char select = '+';
		switch (index) {
		case 0:
			select = '+';
			break;
		case 1:
			select = '-';
			break;
		case 2:
			select = '*';
			break;
		case 3:
			select = '/';
			break;
		}
		double value = arith.m_arithVal;
		OnArithCal(value, select);
	}
}

// 실제 산술연산
void CColorImageProcessing10Doc::OnArithCal(double value, char select)
{
	switch (select) {
	case '+':
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				int R, G, B;

				R = int(m_inImageR[h][w]);
				G = int(m_inImageG[h][w]);
				B = int(m_inImageB[h][w]);
				
				R += int(value);
				G += int(value);
				B += int(value);

				// Red 클리핑
				if (R < 0) {
					R = 0;
				}
				else if (R > 255) {
					R = 255;
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}
				// Green 클리핑
				if (G < 0) {
					G = 0;
				}
				else if (G > 255) {
					G = 255;
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}
				// Blue 클리핑
				if (B < 0) {
					B = 0;
				}
				else if (B > 255) {
					B = 255;
				}
				else{
					m_outImageB[h][w] = unsigned char(B);
				}		
			}
		}
		break;
	case '-':
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				int R, G, B;

				R = m_inImageR[h][w];
				G = m_inImageG[h][w];
				B = m_inImageB[h][w];

				R -= int(value);
				G -= int(value);
				B -= int(value);

				// Red 클리핑
				if (R < 0) {
					R = 0;
					m_outImageR[h][w] = unsigned char(R);
				}
				else if (R > 255) {
					R = 255;
					m_outImageR[h][w] = unsigned char(R);
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}
				// Green 클리핑
				if (G < 0) {
					G = 0;
					m_outImageG[h][w] = unsigned char(G);
				}
				else if (G > 255) {
					G = 255;
					m_outImageG[h][w] = unsigned char(G);
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}
				// Blue 클리핑
				if (B < 0) {
					B = 0;
					m_outImageB[h][w] = unsigned char(B);
				}
				else if (B > 255) {
					B = 255;
					m_outImageB[h][w] = unsigned char(B);
				}
				else {
					m_outImageB[h][w] = unsigned char(B);
				}
			}
		}
		break;
	case '*':
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				int R, G, B;

				R = m_inImageR[h][w];
				G = m_inImageG[h][w];
				B = m_inImageB[h][w];


				R *= value;
				G *= value;
				B *= value;

				// Red 클리핑
				if (R < 0.0) {
					R = 0.0;
					m_outImageR[h][w] = unsigned char(R);
				}
				else if (R > 255.0) {
					R = 255.0;
					m_outImageR[h][w] = unsigned char(R);
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}
				// Green 클리핑
				if (G < 0.0) {
					G = 0.0;
					m_outImageG[h][w] = unsigned char(G);
				}
				else if (G > 255.0) {
					G = 255.0;
					m_outImageG[h][w] = unsigned char(G);
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}
				// Blue 클리핑
				if (B < 0.0) {
					B = 0.0;
					m_outImageB[h][w] = unsigned char(B);
				}
				else if (B > 255.0) {
					B = 255.0;
					m_outImageB[h][w] = unsigned char(B);
				}
				else {
					m_outImageB[h][w] = unsigned char(B);
				}
			}
		}
		break;
	case '/':
		if (value == 0.0) {
			value = 1.0;
		}
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				double R, G, B;

				R = double(m_inImageR[h][w]);
				G = double(m_inImageG[h][w]);
				B = double(m_inImageB[h][w]);

				R /= value;
				G /= value;
				B /= value;

				// Red 클리핑
				if (R < 0.0) {
					R = 0.0;
					m_outImageR[h][w] = unsigned char(R);
				}
				else if (R > 255.0) {
					R = 255.0;
					m_outImageR[h][w] = unsigned char(R);
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}
				// Green 클리핑
				if (G < 0.0) {
					G = 0.0;
					m_outImageG[h][w] = unsigned char(G);
				}
				else if (G > 255.0) {
					G = 255.0;
					m_outImageG[h][w] = unsigned char(G);
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}
				// Blue 클리핑
				if (B < 0.0) {
					B = 0.0;
					m_outImageB[h][w] = unsigned char(B);
				}
				else if (B > 255.0) {
					B = 255.0;
					m_outImageB[h][w] = unsigned char(B);
				}
				else {
					m_outImageB[h][w] = unsigned char(B);
				}
			}
		}
		break;
	}
}

// HSI -> RGB
unsigned char* CColorImageProcessing10Doc::OnHSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;

	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}

	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}

// RGB -> HSI
double* CColorImageProcessing10Doc::OnRGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;

	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


void CColorImageProcessing10Doc::OnGamma()
{
	// TODO: 여기에 구현 코드 추가.
	CGammaDlg gamma;

	if (gamma.DoModal() == IDOK) {

		OnFreeOutimage();
		OnFreeBackimage();
		// 출력 이미지 크기 복사
		m_outH = m_inH;
		m_outW = m_inW;

		// 출력 이미지 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		double gammaVal = gamma.m_gamma;

		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				// 감마연산
				double R, G, B;

				R = double(m_inImageR[h][w]);
				G = double(m_inImageG[h][w]);
				B = double(m_inImageB[h][w]);

				R = pow(R, 1.0 / gammaVal);
				G = pow(G, 1.0 / gammaVal);
				B = pow(B, 1.0 / gammaVal);

				// Red 클리핑
				if (R < 0.0) {
					R = 0.0;
				}
				else if (R > 255.0) {
					R = 255.0;
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}

				// Green 클리핑
				if (G < 0.0) {
					G = 0.0;
				}
				else if (G > 255.0) {
					G = 255.0;
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}

				// Blue 클리핑
				if (B < 0.0) {
					B = 0.0;
				}
				else if (B > 255.0) {
					B = 255.0;
				}
				else {
					m_outImageB[h][w] = unsigned char(B);
				}
			}
		}
	}
}


void CColorImageProcessing10Doc::OnPara()
{
	// TODO: 여기에 구현 코드 추가.
	CParaDlg para;

	if (para.DoModal() == IDOK) {
		OnFreeOutimage();
		OnFreeBackimage();
		// 출력 이미지 크기 복사
		m_outH = m_inH;
		m_outW = m_inW;

		// 출력 이미지 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		// PARA연산 선택
		int select = para.m_radioIndex;

		if (select == 0) {

			// PARA_CAP 적용
			for (int h = 0; h < m_inH; h++) {
				for (int w = 0; w < m_inW; w++) {

					double R, G, B;

					R = double(m_inImageR[h][w]);
					G = double(m_inImageG[h][w]);
					B = double(m_inImageB[h][w]);

					R = 255 * pow((R / 127 - 1), 2);
					G = 255 * pow((G / 127 - 1), 2);
					B = 255 * pow((B / 127 - 1), 2);

					// Red 클리핑
					if (R < 0.0) {
						R = 0.0;
					}
					else if (R > 255.0) {
						R = 255.0;
					}
					else {
						m_outImageR[h][w] = unsigned char(R);
					}

					// Green 클리핑
					if (G < 0.0) {
						G = 0.0;
					}
					else if (G > 255.0) {
						G = 255.0;
					}
					else {
						m_outImageG[h][w] = unsigned char(G);
					}

					// Blue 클리핑
					if (B < 0.0) {
						B = 0.0;
					}
					else if (B > 255.0) {
						B = 255.0;
					}
					else {
						m_outImageB[h][w] = unsigned char(B);
					}
				}
			}

		}
		else if (select == 1) {
			for (int h = 0; h < m_inH; h++) {
				for (int w = 0; w < m_inW; w++) {

					// PARA_CUP 적용
					double R, G, B;

					R = double(m_inImageR[h][w]);
					G = double(m_inImageG[h][w]);
					B = double(m_inImageB[h][w]);

					R = -255 * pow((R / 127 - 1), 2) + 255;
					G = -255 * pow((G / 127 - 1), 2) + 255;
					B = -255 * pow((B / 127 - 1), 2) + 255;

					// Red 클리핑
					if (R < 0.0) {
						R = 0.0;
					}
					else if (R > 255.0) {
						R = 255.0;
					}
					else {
						m_outImageR[h][w] = unsigned char(R);
					}

					// Green 클리핑
					if (G < 0.0) {
						G = 0.0;
					}
					else if (G > 255.0) {
						G = 255.0;
					}
					else {
						m_outImageG[h][w] = unsigned char(G);
					}

					// Blue 클리핑
					if (B < 0.0) {
						B = 0.0;
					}
					else if (B > 255.0) {
						B = 255.0;
					}
					else {
						m_outImageB[h][w] = unsigned char(B);
					}
				}
			}
		}
	}
}

void CColorImageProcessing10Doc::OnHistStretch()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();
	// 출력 이미지 크기 복사
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);


	// RED HISTOGRAM STRECH
	{
		double highestR = 0.0;
		double lowestR = 255.0;

		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {
				if (m_inImageR[h][w] > highestR) {
					highestR = m_inImageR[h][w];
				}
				if (m_inImageR[h][w] < lowestR) {
					lowestR = m_inImageR[h][w];
				}
			}
		}
		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {
				int oldVal = m_inImageR[h][w];
				int newVal = int(((oldVal - lowestR) / (highestR - lowestR)) * 255.0);
				m_outImageR[h][w] = newVal;
			}
		}
	}
	// GREEN HISTOGRAM STRECH
	{
		double highestG = 0.0;
		double lowestG = 255.0;

		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {
				if (m_inImageG[h][w] > highestG) {
					highestG = m_inImageG[h][w];
				}
				if (m_inImageG[h][w] < lowestG) {
					lowestG = m_inImageG[h][w];
				}
			}
		}
		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {
				int oldVal = m_inImageG[h][w];
				int newVal = int(((oldVal - lowestG) / (highestG - lowestG)) * 255.0);
				m_outImageG[h][w] = newVal;
			}
		}
	}

	// BLUE HISTOGRAM STRECH
	{
		double highestB = 0.0;
		double lowestB = 255.0;

		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {
				if (m_inImageB[h][w] > highestB) {
					highestB = m_inImageB[h][w];
				}
				if (m_inImageB[h][w] < lowestB) {
					lowestB = m_inImageB[h][w];
				}
			}
		}
		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {
				int oldVal = m_inImageB[h][w];
				int newVal = int(((oldVal - lowestB) / (highestB - lowestB)) * 255.0);
				m_outImageB[h][w] = newVal;
			}
		}
	}
}


void CColorImageProcessing10Doc::OnHistEndin()
{
	// TODO: 여기에 구현 코드 추가.
	CEndInDlg endin;
	if (endin.DoModal() == IDOK) {

		int endinVal = endin.m_endin;
		OnFreeOutimage();
		OnFreeBackimage();
		// 출력 이미지 크기 복사
		m_outH = m_inH;
		m_outW = m_inW;

		// 출력 이미지 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		// RED HISTOGRAM ENDIN
		{
			double highestR = 0.0;
			double lowestR = 255.0;

			for (int h = 0; h < m_outH; h++) {
				for (int w = 0; w < m_outW; w++) {
					if (m_inImageR[h][w] > highestR) {
						highestR = m_inImageR[h][w];
					}
					if (m_inImageR[h][w] < lowestR) {
						lowestR = m_inImageR[h][w];
					}
				}
			}

			highestR -= endinVal;
			lowestR += endinVal;

			for (int h = 0; h < m_outH; h++) {
				for (int w = 0; w < m_outW; w++) {
					int oldVal = m_inImageR[h][w];
					int newVal = int(((oldVal - lowestR) / (highestR - lowestR)) * 255.0);
					if (newVal < 0) {
						m_outImageR[h][w] = 0;
					}
					else if (newVal > 255) {
						m_outImageR[h][w] = 255;
					}
					else {
						m_outImageR[h][w] = newVal;
					}
					
				}
			}
		}
		// GREEN HISTOGRAM ENDIN
		{
			double highestG = 0.0;
			double lowestG = 255.0;

			for (int h = 0; h < m_outH; h++) {
				for (int w = 0; w < m_outW; w++) {
					if (m_inImageG[h][w] > highestG) {
						highestG = m_inImageG[h][w];
					}
					if (m_inImageG[h][w] < lowestG) {
						lowestG = m_inImageG[h][w];
					}
				}
			}

			// 상한값과 하한값을 입력값으로 조정
			highestG -= endinVal;
			lowestG += endinVal;

			// 조정된 값을 바탕으로 히스토그램 스트레치
			for (int h = 0; h < m_outH; h++) {
				for (int w = 0; w < m_outW; w++) {
					int oldVal = m_inImageG[h][w];
					int newVal = int(((oldVal - lowestG) / (highestG - lowestG)) * 255.0);
					if (newVal < 0) {
						m_outImageG[h][w] = 0;
					}
					else if (newVal > 255) {
						m_outImageG[h][w] = 255;
					}
					else {
						m_outImageG[h][w] = newVal;
					}
				}
			}
		}

		// BLUE HISTOGRAM ENDIN
		{
			double highestB = 0.0;
			double lowestB = 255.0;

			for (int h = 0; h < m_outH; h++) {
				for (int w = 0; w < m_outW; w++) {
					if (m_inImageB[h][w] > highestB) {
						highestB = m_inImageB[h][w];
					}
					if (m_inImageB[h][w] < lowestB) {
						lowestB = m_inImageB[h][w];
					}
				}
			}

			highestB -= endinVal;
			lowestB += endinVal;

			for (int h = 0; h < m_outH; h++) {
				for (int w = 0; w < m_outW; w++) {
					int oldVal = m_inImageB[h][w];
					int newVal = int(((oldVal - lowestB) / (highestB - lowestB)) * 255.0);
					if (newVal < 0) {
						m_outImageB[h][w] = 0;
					}
					else if (newVal > 255) {
						m_outImageB[h][w] = 255;
					}
					else {
						m_outImageB[h][w] = newVal;
					}
				}
			}
		}

	}
}


void CColorImageProcessing10Doc::OnHistEqual()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();
	// 출력 이미지 크기 복사
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 총 화소 수
	long long pixel_n = m_inH * m_inW;

	// RED HISTOGRAM EQUAL
	{
		double highestR = 0.0;
		// 기본 히스토그램 (도수분포표) 메모리 할당
		int* hist = (int*)malloc(sizeof(int) * 256);

		// 기본 히스토그램 (도수분포표) 0으로 초기화
		for (int idx = 0; idx <= 255; idx++) {
			hist[idx] = 0;
		}

		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {
				if (m_inImageR[h][w] > highestR) {
					highestR = m_inImageR[h][w];
				}
				// 기본 히스토그램 (도수분포표) 작성
				hist[m_inImageR[h][w]] += 1;
			}
		}

		// 누적 히스토그램 (누적도수분포표) 메모리 할당
		double* sum_hist = (double*)malloc(sizeof(double) * 256);

		// 누적 히스토그램 (누적도수분포표) 0으로 초기화
		for (int idx = 0; idx <= 255; idx++) {
			sum_hist[idx] = 0.0;
		}

		// 누적 히스토 그램 첫 요소만 복사
		sum_hist[0] = hist[0];

		// 누적 도수분포표 작성

		for (int idx = 1; idx <= 255; idx++) {
			sum_hist[idx] = sum_hist[idx - 1] + hist[idx];
		}
		// 필요 없어진 도수분포표 메모리 해제
		free(hist);

		//  정규화 된 누적 히스토그램 메모리 할당
		double* norm_hist = (double*)malloc(sizeof(double) * 256);

		for (int idx = 0; idx <= 255; idx++) {
			norm_hist[idx] = sum_hist[idx] * (1.0 / pixel_n) * highestR;
		}
		// 필요 없어진 누적도수분포표 메모리 해제
		free(sum_hist);

		// 정규화 된 누적 히스토그램 -> outImage에 복사
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {
				m_outImageR[h][w] = unsigned char(norm_hist[m_inImageR[h][w]]);
			}
		}
		// 필요 없어진 정규화 된 누적 히스토그램 메모리 해제
		free(norm_hist);
	}

	// GREEN HISTOGRAM EQUAL
	{
		double highestG = 0.0;
		// 기본 히스토그램 (도수분포표) 메모리 할당
		int* hist = (int*)malloc(sizeof(int) * 256);

		// 기본 히스토그램 (도수분포표) 0으로 초기화
		for (int idx = 0; idx <= 255; idx++) {
			hist[idx] = 0;
		}

		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {
				if (m_inImageG[h][w] > highestG) {
					highestG = m_inImageG[h][w];
				}
				// 기본 히스토그램 (도수분포표) 작성
				hist[m_inImageG[h][w]] += 1;
			}
		}

		// 누적 히스토그램 (누적도수분포표) 메모리 할당
		double* sum_hist = (double*)malloc(sizeof(double) * 256);

		// 누적 히스토그램 (누적도수분포표) 0으로 초기화
		for (int idx = 0; idx <= 255; idx++) {
			sum_hist[idx] = 0.0;
		}

		// 누적 히스토 그램 첫 요소만 복사
		sum_hist[0] = hist[0];

		// 누적 도수분포표 작성

		for (int idx = 1; idx <= 255; idx++) {
			sum_hist[idx] = sum_hist[idx - 1] + hist[idx];
		}
		// 필요 없어진 도수분포표 메모리 해제
		free(hist);

		//  정규화 된 누적 히스토그램 메모리 할당
		double* norm_hist = (double*)malloc(sizeof(double) * 256);

		for (int idx = 0; idx <= 255; idx++) {
			norm_hist[idx] = sum_hist[idx] * (1.0 / pixel_n) * highestG;
		}
		// 필요 없어진 누적도수분포표 메모리 해제
		free(sum_hist);

		// 정규화 된 누적 히스토그램 -> outImage에 복사
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {
				m_outImageG[h][w] = unsigned char(norm_hist[m_inImageG[h][w]]);
			}
		}
		// 필요 없어진 정규화 된 누적 히스토그램 메모리 해제
		free(norm_hist);
	}

	// BLUE HISTOGRAM EQUAL
	{
		double highestB = 0.0;
		// 기본 히스토그램 (도수분포표) 메모리 할당
		int* hist = (int*)malloc(sizeof(int) * 256);

		// 기본 히스토그램 (도수분포표) 0으로 초기화
		for (int idx = 0; idx <= 255; idx++) {
			hist[idx] = 0;
		}

		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {
				if (m_inImageB[h][w] > highestB) {
					highestB = m_inImageB[h][w];
				}
				// 기본 히스토그램 (도수분포표) 작성
				hist[m_inImageB[h][w]] += 1;
			}
		}

		// 누적 히스토그램 (누적도수분포표) 메모리 할당
		double* sum_hist = (double*)malloc(sizeof(double) * 256);

		// 누적 히스토그램 (누적도수분포표) 0으로 초기화
		for (int idx = 0; idx <= 255; idx++) {
			sum_hist[idx] = 0.0;
		}

		// 누적 히스토 그램 첫 요소만 복사
		sum_hist[0] = hist[0];

		// 누적 도수분포표 작성

		for (int idx = 1; idx <= 255; idx++) {
			sum_hist[idx] = sum_hist[idx - 1] + hist[idx];
		}
		// 필요 없어진 도수분포표 메모리 해제
		free(hist);

		//  정규화 된 누적 히스토그램 메모리 할당
		double* norm_hist = (double*)malloc(sizeof(double) * 256);

		for (int idx = 0; idx <= 255; idx++) {
			norm_hist[idx] = sum_hist[idx] * (1.0 / pixel_n) * highestB;
		}
		// 필요 없어진 누적도수분포표 메모리 해제
		free(sum_hist);

		// 정규화 된 누적 히스토그램 -> outImage에 복사
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {
				m_outImageB[h][w] = unsigned char(norm_hist[m_inImageB[h][w]]);
			}
		}
		// 필요 없어진 정규화 된 누적 히스토그램 메모리 해제
		free(norm_hist);
	}
}


void CColorImageProcessing10Doc::OnEmboss()
{	
	OnFreeOutimage();
	OnFreeBackimage();

	// 중요 ! 출력 이미지 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 엠보싱 마스크
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { 
		{-1.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, .0, 1.0} };

	// 임시 메모리 할당
	double** tmpInImageR; double** tmpInImageG; double** tmpInImageB;
	double** tmpOutImageR; double** tmpOutImageG; double** tmpOutImageB;
	double** tmpInImageH; double** tmpInImageS; double** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	// 임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// RGB 모델 --> HSI 모델
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k];
			G = tmpInImageG[i][k];
			B = tmpInImageB[i][k];
			hsi = OnRGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageI[i][k] += 127;

	// HSI --> RGB
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = OnHSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}
	}

	// 임시 출력 이미지 --> 출력 이미지
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpInImageH, m_inH + 2);
	OnFree2D(tmpInImageS, m_inH + 2);
	OnFree2D(tmpInImageI, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}

// 2차원 더블형 배열 할당
double** CColorImageProcessing10Doc::OnMalloc2D_double(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	double** memory;
	memory = new double* [height];
	for (int h = 0; h < height; h++)
		memory[h] = new double[width];
	return memory;
}

// 블러링
void CColorImageProcessing10Doc::OnBlur()
{
	// 기존 메모리 해제
	OnFreeOutimage();

	// 중요 ! 출력 이미지 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 블러링 마스크
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { 
		{1. / 9, 1. / 9, 1. / 9},
		{1. / 9, 1. / 9, 1. / 9},
		{1. / 9, 1. / 9, 1. / 9} };

	// 임시 메모리 할당
	double** tmpInImageR; double** tmpInImageG; double** tmpInImageB;
	double** tmpOutImageR; double** tmpOutImageG; double** tmpOutImageB;
	double** tmpInImageH; double** tmpInImageS; double** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// RGB --> HSI
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k];
			G = tmpInImageG[i][k];
			B = tmpInImageB[i][k];
			hsi = OnRGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	//회선 연산
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// HSI --> RGB
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = OnHSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}
	}

	// 임시 출력 이미지 --> 출력 이미지
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_outH + 2); OnFree2D(tmpInImageG, m_outH + 2); OnFree2D(tmpInImageB, m_outH + 2);
	OnFree2D(tmpInImageH, m_outH + 2); OnFree2D(tmpInImageS, m_outH + 2); OnFree2D(tmpInImageI, m_outH + 2);
	OnFree2D(tmpOutImageR, m_outH); OnFree2D(tmpOutImageG, m_outH); OnFree2D(tmpOutImageB, m_outH);
}

// 고주파 샤프닝
void CColorImageProcessing10Doc::OnHighFreq()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutimage();
	OnFreeBackimage();
	// 중요 ! 출력 이미지 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	
	// 고주파 샤프닝 마스크
	const int MSIZE = 3;
	double boundary = -1.0 / 9;
	double center = 8.0 / 9;

	double mask[MSIZE][MSIZE] = {  
		{boundary , boundary , boundary },
		{boundary , center	 , boundary },
		{boundary , boundary , boundary } };

	// 임시 메모리 할당
	double** tmpInImageR; double** tmpInImageG; double** tmpInImageB;
	double** tmpOutImageR; double** tmpOutImageG; double** tmpOutImageB;
	double** tmpInImageH; double** tmpInImageS; double** tmpInImageI;
	

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// RGB --> HSI
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k];
			G = tmpInImageG[i][k];
			B = tmpInImageB[i][k];
			hsi = OnRGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	//회선 연산
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];

			double temp = tmpInImageI[i][k] + S_VALUE;
			if (temp > 255.0)
				tmpInImageI[i][k] = 255.0;
			else if (temp < 0.0)
				tmpInImageI[i][k] = 0.0;
			else
				tmpInImageI[i][k] = temp;
		}
	}

	// HSI --> RGB
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = OnHSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}
	}

	// 임시 출력 이미지 --> 출력 이미지
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_outH + 2); OnFree2D(tmpInImageG, m_outH + 2); OnFree2D(tmpInImageB, m_outH + 2);
	OnFree2D(tmpInImageH, m_outH + 2); OnFree2D(tmpInImageS, m_outH + 2); OnFree2D(tmpInImageI, m_outH + 2);
	OnFree2D(tmpOutImageR, m_outH); OnFree2D(tmpOutImageG, m_outH); OnFree2D(tmpOutImageB, m_outH);
}

// 회전
void CColorImageProcessing10Doc::OnRotate()
{
	// TODO: 여기에 구현 코드 추가.
	CRotateDlg rotate;

	// 취소 누르면 바로 리턴
	if (rotate.DoModal() == IDOK) {
		// 다이얼로그 창의 더블형 입력받기
		m_degree += rotate.m_rotateVal;
		if (m_degree > 360) {
			m_degree -= 360;
		}
		else if (m_degree < -360) {
			m_degree += 360;
		}

		// 입력한 각도 -> 라디안 값을 저장할 변수
		double radian = 0.0;

		// radian_0 , radian_90은 (90-radian) 값을 저장하는 변수
		// 배경의 크기를 구하기 위한 변수임
		double radian_0 = 0.0;
		double radian_90 = 0.0;

		// 배경의 높이와 너비 값을 저장하는 변수
		m_backH = 0;
		m_backW = 0;

		// 각도 -> 라디안
		radian = m_degree * 3.141592 / 180.0;

		// radian_90은 (90-radian) 값을 저장하는 변수
		if (m_degree > 0 && m_degree <= 90) {
			radian_0 = radian;
			radian_90 = (90 - m_degree) * 3.141592 / 180.0;
		}
		else if (m_degree > 90 && m_degree <= 180) {
			radian_0 = (90 - m_degree) * 3.141592 / 180.0;
			radian_90 = (180 - m_degree) * 3.141592 / 180.0;
		}
		else if (m_degree > 180 && m_degree <= 270) {
			radian_0 = (180 - m_degree) * 3.141592 / 180.0;
			radian_90 = (270 - m_degree) * 3.141592 / 180.0;
		}
		else if (m_degree > 270 && m_degree <= 360) {
			radian_0 = (270 - m_degree) * 3.141592 / 180.0;
			radian_90 = (360 - m_degree) * 3.141592 / 180.0;
		}
		else if (m_degree < 0 && -90 <= m_degree) {
			radian_0 = -1 * radian;
			radian_90 = (-90 - m_degree) * 3.141592 / 180.0;
		}
		else if (m_degree < -90 && -180 <= m_degree) {
			radian_0 = (-90 - m_degree) * 3.141592 / 180.0;
			radian_90 = (-180 - m_degree) * 3.141592 / 180.0;
		}
		else if (m_degree < -180 && -270 <= m_degree) {
			radian_0 = (-180 - m_degree) * 3.141592 / 180.0;
			radian_90 = (-270 - m_degree) * 3.141592 / 180.0;
		}
		else if (m_degree < -270 && -360 <= m_degree) {
			radian_0 = (-270 - m_degree) * 3.141592 / 180.0;
			radian_90 = (-360 - m_degree) * 3.141592 / 180.0;
		}

		// 드디어 배경의 높이와 너비를 구했다.
		int bigger = 0;
		if (m_inH > m_inW) {
			bigger = m_inH;
		}
		else {
			bigger = m_inW;
		}

		m_backH = int(cos(radian_0) * bigger + cos(radian_90) * bigger);
		m_backW = int(cos(radian_90) * bigger + cos(radian_0) * bigger);

		// 홀수 처리부
		if (m_backH % 2) {
			m_backH += 1;
		}

		if (m_backW % 2) {
			m_backW += 1;
		}

		// 배경의 높이와 너비로 tempImage 만들기
		m_backImageR = OnMalloc2D(m_backH, m_backW);
		m_backImageG = OnMalloc2D(m_backH, m_backW);
		m_backImageB = OnMalloc2D(m_backH, m_backW);

		// tempImage의 배경을 검은색으로
		for (int h = 0; h < m_backH; h++) {
			for (int w = 0; w < m_backW; w++) {
				m_backImageR[h][w] = 0;
				m_backImageG[h][w] = 0;
				m_backImageB[h][w] = 0;
			}
		}

		// 중심점 잡기
		int in_center_height = m_inH / 2;
		int in_center_width = m_inW / 2;

		int back_center_height = m_backH / 2;
		int back_center_width = m_backW / 2;

		// 회전
		for (int h = 0; h < m_backH; h++) {
			for (int w = 0; w < m_backW; w++) {

				int xd = h;
				int yd = w;

				// 배경의 크기 만큼 내려주었다가
				int xs = (cos(radian) * (xd - back_center_height)) - (sin(radian) * (yd - back_center_width));
				int ys = (sin(radian) * (xd - back_center_width)) + (cos(radian) * (yd - back_center_width));

				// 입력 이미지 크기 만큼 다시 올려주기
				xs += in_center_height;
				ys += in_center_width;

				if ((0 <= xs && xs < m_inH) && (0 <= ys && ys < m_inW)) {
					m_backImageR[xd][yd] = m_inImageR[xs][ys];
					m_backImageG[xd][yd] = m_inImageG[xs][ys];
					m_backImageB[xd][yd] = m_inImageB[xs][ys];
				}
			}
		}
	}
}


void CColorImageProcessing10Doc::OnFreeBackimage()
{
	// TODO: 여기에 구현 코드 추가.
		if (m_backImageR != NULL) {

			OnFree2D(m_backImageR, m_backH);
			OnFree2D(m_backImageG, m_backH);
			OnFree2D(m_backImageB, m_backH);

			m_backImageR = m_backImageG = m_backImageB = NULL;

			m_backH = 0;
			m_backW = 0;
		}
}


void CColorImageProcessing10Doc::OnGaussian()
{
	OnFreeOutimage();
	OnFreeBackimage();
	// 중요 ! 출력 이미지 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = { // 가우시안 스무딩 마스크
		{1. / 16, 1. / 8, 1. / 16},
		{1. / 8, 1. / 4, 1. / 8},
		{1. / 16, 1. / 8, 1. / 16} };


	// 임시 메모리 할당
	double** tmpInImageR; double** tmpInImageG; double** tmpInImageB;
	double** tmpOutImageR; double** tmpOutImageG; double** tmpOutImageB;
	double** tmpInImageH; double** tmpInImageS; double** tmpInImageI;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageG = OnMalloc2D_double(m_inH, m_inW);
	tmpOutImageB = OnMalloc2D_double(m_inH, m_inW);

	// 임시 메모리 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;
		}
	}

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// RGB 모델 --> HSI 모델
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k];
			G = tmpInImageG[i][k];
			B = tmpInImageB[i][k];
			hsi = OnRGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}


	// HSI --> RGB
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = OnHSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}
	}

	// 임시 출력 이미지 --> 출력 이미지
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpInImageH, m_inH + 2);
	OnFree2D(tmpInImageS, m_inH + 2);
	OnFree2D(tmpInImageI, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImageProcessing10Doc::OnAlterSaturation()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	CSaturationDlg satDlg;
	if (satDlg.DoModal() == IDOK) {
		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {

				// 다른언어에서는 다를지도
				// H:(색상 0~360)
				// S:(0.0~1.0)
				// I:(0~255)

				// RGB -> HSI
				double H, S, I;
				unsigned char R, G, B;

				R = m_inImageR[h][w];
				G = m_inImageG[h][w];
				B = m_inImageB[h][w];

				double* hsi = OnRGB2HSI(R, G, B);

				H = hsi[0];
				S = hsi[1];
				I = hsi[2];

				// 채도 변경
				S += satDlg.m_saturation;
				if (S < 0.0) 
					S = 0.0;
				else if (S > 1.0)
					S = 1.0;

				// 다시 RGB로
				unsigned char* rgb = OnHSI2RGB(H, S, I);
				R = rgb[0];		G = rgb[1];		B = rgb[2];

				m_outImageR[h][w] = R;
				m_outImageG[h][w] = G;
				m_outImageB[h][w] = B;
			}
		}
	}

}


void CColorImageProcessing10Doc::OnExtractHue()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();

	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	CExtractHueDlg extractDlg;

	if (extractDlg.DoModal() == IDOK) {
		for (int h = 0; h < m_outH; h++) {
			for (int w = 0; w < m_outW; w++) {
				// 다른언어에서는 다를지도
				// H:(색상 0~360)
				// S:(0.0~1.0)
				// I:(0~255)
				// RGB -> HSI

				double H, S, I;
				unsigned char R, G, B;

				R = m_inImageR[h][w];
				G = m_inImageG[h][w];
				B = m_inImageB[h][w];

				double* hsi = OnRGB2HSI(R, G, B);

				H = hsi[0];
				S = hsi[1];
				I = hsi[2];

				// 빨강 추출 (h 값 0~20, 330~360)
				int left = extractDlg.m_extractLeft;
				int right = extractDlg.m_extractRight;

				// 지정된 범위 사이의 값은 그대로 나머지는 Gray Sclae로 출력
				if (right < left) {
					if ((right >= H && 0 <= H) || (H >= left && H <= 360)) {
						m_outImageR[h][w] = m_inImageR[h][w];
						m_outImageG[h][w] = m_inImageG[h][w];
						m_outImageB[h][w] = m_inImageB[h][w];
					}
					else {
						double avg = (m_inImageR[h][w] + m_inImageG[h][w] + m_inImageB[h][w]) / 3.0;
						m_outImageR[h][w] = unsigned char(avg);
						m_outImageG[h][w] = unsigned char(avg);
						m_outImageB[h][w] = unsigned char(avg);
					}
				}
				// 원형인 HSI 모델의 H를 고려하여 좁은 범위 탐색 가능하게 구현
				else {
					if (left <= H && H <= right) {
						m_outImageR[h][w] = m_inImageR[h][w];
						m_outImageG[h][w] = m_inImageG[h][w];
						m_outImageB[h][w] = m_inImageB[h][w];
					}
					else {
						double avg = (m_inImageR[h][w] + m_inImageG[h][w] + m_inImageB[h][w]) / 3.0;
						m_outImageR[h][w] = unsigned char(avg);
						m_outImageG[h][w] = unsigned char(avg);
						m_outImageB[h][w] = unsigned char(avg);
					}
				}
			}
		}
	}
}

// 논리 연산 구현
void CColorImageProcessing10Doc::OnLogical() {
	// TODO: 여기에 구현 코드 추가.
	CLogicalDlg logical;
	if (logical.DoModal() != IDOK) {
		return;
	}
	else {
		// 기존 출력 이미지 메모리 해제
		OnFreeOutimage();
		OnFreeBackimage();

		// 출력 이미지 크기 복사
		m_outH = m_inH;
		m_outW = m_inW;

		// 출력 이미지 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		// 논리 연산자 선택
		int index = logical.m_radioIndex;
		char select = '&';
		switch (index) {
		case 0:
			select = '&';
			break;
		case 1:
			select = '|';
			break;
		case 2:
			select = '^';
			break;
		}
		int value = logical.m_logicalVal;
		OnLogicalCal(value, select);
	}
}

// 실제 논리 연산 함수
void CColorImageProcessing10Doc::OnLogicalCal(int value, char select) {
	switch (select) {
	case '&':
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				int R, G, B;

				R = int(m_inImageR[h][w]); 
				G = int(m_inImageG[h][w]); 
				B = int(m_inImageB[h][w]);

				R &= value;		
				G &= value;		
				B &= value;
				
				// Red 클리핑
				if (R < 0.0) {
					R = 0.0;
				}
				else if (R > 255.0) {
					R = 255.0;
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}

				// Green 클리핑
				if (G < 0.0) {
					G = 0.0;
				}
				else if (G > 255.0) {
					G = 255.0;
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}

				// Blue 클리핑
				if (B < 0.0) {
					B = 0.0;
				}
				else if (B > 255.0) {
					B = 255.0;
				}
				else {
					m_outImageB[h][w] = unsigned char(B);
				}
			}
		}
		break;
	case '|':
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				int R, G, B;

				R = int(m_inImageR[h][w]);
				G = int(m_inImageG[h][w]);
				B = int(m_inImageB[h][w]);

				R |= value;
				G |= value;
				B |= value;

				// Red 클리핑
				if (R < 0.0) {
					R = 0.0;
				}
				else if (R > 255.0) {
					R = 255.0;
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}

				// Green 클리핑
				if (G < 0.0) {
					G = 0.0;
				}
				else if (G > 255.0) {
					G = 255.0;
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}

				// Blue 클리핑
				if (B < 0.0) {
					B = 0.0;
				}
				else if (B > 255.0) {
					B = 255.0;
				}
				else {
					m_outImageB[h][w] = unsigned char(B);
				}
			}
		}
		break;
	case '^':
		for (int h = 0; h < m_inH; h++) {
			for (int w = 0; w < m_inW; w++) {

				int R, G, B;

				R = m_inImageR[h][w];
				G = m_inImageG[h][w];
				B = m_inImageB[h][w];

				R ^= value;
				G ^= value;
				B ^= value;

				// Red 클리핑
				if (R < 0.0) {
					R = 0.0;
				}
				else if (R > 255.0) {
					R = 255.0;
				}
				else {
					m_outImageR[h][w] = unsigned char(R);
				}

				// Green 클리핑
				if (G < 0.0) {
					G = 0.0;
				}
				else if (G > 255.0) {
					G = 255.0;
				}
				else {
					m_outImageG[h][w] = unsigned char(G);
				}

				// Blue 클리핑
				if (B < 0.0) {
					B = 0.0;
				}
				else if (B > 255.0) {
					B = 255.0;
				}
				else {
					m_outImageB[h][w] = unsigned char(B);
				}
			}
		}
		break;
	}
}



BOOL CColorImageProcessing10Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.if (m_outImageR == NULL)
	return FALSE;

	CImage image;
	image.Create(m_outW, m_outH, 32);

	unsigned char R, G, B;
	COLORREF px;

	for (int i = 0; i < m_outW; i++) {
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);

	return TRUE;
}

// 반전처리 ~ Not 연산자로 구현
void CColorImageProcessing10Doc::OnReverse()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();

	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);


	for (int h = 0; h < m_inH; h++) {
		for (int w = 0; w < m_inW; w++) {
			
			m_outImageR[h][w] = ~m_inImageR[h][w];
			m_outImageG[h][w] = ~m_inImageG[h][w];
			m_outImageB[h][w] = ~m_inImageB[h][w];

		}
	}
}

// 이진화
void CColorImageProcessing10Doc::OnBow()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();

	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);


	for (int h = 0; h < m_inH; h++) {
		for (int w = 0; w < m_inW; w++) {

			if (m_inImageR[h][w] > 127) {
				m_outImageR[h][w] = 255;
			}
			else {
				m_outImageR[h][w] = 0;
			}

			if (m_inImageG[h][w] > 127) {
				m_outImageG[h][w] = 255;
			}
			else {
				m_outImageG[h][w] = 0;
			}

			if (m_inImageB[h][w] > 127) {
				m_outImageB[h][w] = 255;
			}
			else {
				m_outImageB[h][w] = 0;
			}
		}
	}
}

// 1차원 프리윗 마스크
void CColorImageProcessing10Doc::OnPrewitt()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();

	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int h = 0; h < m_outH; h++) {
		for (int w = 0; w < m_outW; w++) {
			double avg = double((m_inImageR[h][w] + m_inImageG[h][w] + m_inImageB[h][w])) / 3.0;
			m_outImageR[h][w] = unsigned char(avg);
			m_outImageG[h][w] = unsigned char(avg);
			m_outImageB[h][w] = unsigned char(avg);
		}
	}

	const int MSIZE = 3;
	// 행 검출 마스크
	double mask_col[MSIZE][MSIZE] = { {-1.0,-1.0,-1.0},
								{0.0,0.0,0.0},
								{1.0,1.0,1.0} };

	// 열 검출 마스크
	double mask_row[MSIZE][MSIZE] = { {1.0,0.0,-1.0},
								{1.0,0.0,-1.0},
								{1.0,0.0,-1.0} };

	double** tmpoutImageCol = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	double** tmpoutImageRow = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	// 임시 메모리 초기화
	for (int i = 0; i < m_outH + 2; i++) {
		for (int k = 0; k < m_outW + 2; k++) {
			tmpoutImageCol[i][k] = 127.0;
			tmpoutImageRow[i][k] = 127.0;
		}
	}

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpoutImageCol[i + 1][k + 1] = m_outImageR[i][k];
			tmpoutImageRow[i + 1][k + 1] = m_outImageR[i][k];
		}
	}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double C_VALUE = 0.0;
			double R_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					C_VALUE += tmpoutImageCol[i + m][k + n] * mask_col[m][n];
					R_VALUE += tmpoutImageRow[i + m][k + n] * mask_row[m][n];
				}				
			m_outImageR[i][k] = C_VALUE + R_VALUE;
			m_outImageG[i][k] = C_VALUE + R_VALUE;
			m_outImageB[i][k] = C_VALUE + R_VALUE;
		}
	}

}

// 2차원 LoG 마스크
void CColorImageProcessing10Doc::OnLog()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	OnFreeBackimage();

	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int h = 0; h < m_outH; h++) {
		for (int w = 0; w < m_outW; w++) {
			double avg = double((m_inImageR[h][w] + m_inImageG[h][w] + m_inImageB[h][w])) / 3.0;
			m_outImageR[h][w] = unsigned char(avg);
			m_outImageG[h][w] = unsigned char(avg);
			m_outImageB[h][w] = unsigned char(avg);
		}
	}

	const int MSIZE = 3;
	// 가우시안 마스크
	double mask_gau[MSIZE][MSIZE] =		{ {1.0 / 16,1.0 / 8,1.0 / 16},
										{1.0 / 8,1.0 / 4,1.0 / 8},
										{1.0 / 16,1.0 / 8,1.0 / 16} };
	// 라플라시안 마스크
	double mask_lap[MSIZE][MSIZE] =		{ {-1.0,-1.0,-1.0},
										{-1.0,8.0,-1.0},
										{-1.0,-1.0,-1.0} };

				  

	double** tmpoutImage = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	

	// 임시 메모리 초기화
	for (int i = 0; i < m_outH + 2; i++) {
		for (int k = 0; k < m_outW + 2; k++) {
			tmpoutImage[i][k] = 127.0;
		}
	}

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpoutImage[i + 1][k + 1] = m_outImageR[i][k];		
		}
	}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double G_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					G_VALUE += tmpoutImage[i + m][k + n] * mask_gau[m][n];
				}
			tmpoutImage[i + 1][k + 1] = G_VALUE;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double L_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					L_VALUE += tmpoutImage[i + m][k + n] * mask_lap[m][n];
				}
			m_outImageR[i][k] = L_VALUE;
			m_outImageG[i][k] = L_VALUE;
			m_outImageB[i][k] = L_VALUE;
		}
	}
}

// 축소
void CColorImageProcessing10Doc::OnZoomOut()
{
	// TODO: 여기에 구현 코드 추가.
	CZoomOutDlg zdlg;
	if(zdlg.DoModal() == IDOK) {
		int scale = (int)zdlg.m_zoomout;
		// 기존 메모리 해제
		OnFreeOutimage();
		OnFreeBackimage();
		// (중요!) 출력 메모리 크기 결정
		m_outH = (int)(m_inH / scale) + 1;
		m_outW = (int)(m_inW / scale) + 1;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		// 출력 이미지 영상 처리
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				m_outImageR[(int)(i / scale)][(int)(k / scale)] = m_inImageR[i][k];
				m_outImageG[(int)(i / scale)][(int)(k / scale)] = m_inImageG[i][k];
				m_outImageB[(int)(i / scale)][(int)(k / scale)] = m_inImageB[i][k];
			}
		}
	}
}

// 확대
void CColorImageProcessing10Doc::OnZoomIn()
{
	// TODO: 여기에 구현 코드 추가.
	CZoomInDlg zdlg;
	if (zdlg.DoModal() == IDOK) {
		int scale = (int)zdlg.m_zoomin;
		// 기존 메모리 해제
		OnFreeOutimage();
		OnFreeBackimage();
		// (중요!) 출력 메모리 크기 결정
		m_outH = (int)(m_inH * scale);
		m_outW = (int)(m_inW * scale);
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// 출력 이미지 영상 처리
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				m_outImageR[i][k] = m_inImageR[(int)(i / scale)][(int)(k / scale)];
				m_outImageG[i][k] = m_inImageG[(int)(i / scale)][(int)(k / scale)];
				m_outImageB[i][k] = m_inImageB[(int)(i / scale)][(int)(k / scale)];
			}
		}
	}
}
