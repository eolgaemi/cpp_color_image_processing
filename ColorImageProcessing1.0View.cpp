
// ColorImageProcessing1.0View.cpp: CColorImageProcessing10View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageProcessing1.0.h"
#endif

#include "ColorImageProcessing1.0Doc.h"
#include "ColorImageProcessing1.0View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorImageProcessing10View

IMPLEMENT_DYNCREATE(CColorImageProcessing10View, CView)

BEGIN_MESSAGE_MAP(CColorImageProcessing10View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CColorImageProcessing10View::OnEqualImage)
	ON_COMMAND(IDM_GRAY_SCALE, &CColorImageProcessing10View::OnGrayScale)
	ON_COMMAND(IDM_ARITH, &CColorImageProcessing10View::OnArith)
	ON_COMMAND(IDM_GAMMA, &CColorImageProcessing10View::OnGamma)
	ON_COMMAND(IDM_PARA, &CColorImageProcessing10View::OnPara)
	ON_COMMAND(IDM_HIST_STRETCH, &CColorImageProcessing10View::OnHistStretch)
	ON_COMMAND(IDM_HIST_ENDIN, &CColorImageProcessing10View::OnHistEndin)
	ON_COMMAND(IDM_HIST_EQUAL, &CColorImageProcessing10View::OnHistEqual)
	ON_COMMAND(IDM_EMBOSS, &CColorImageProcessing10View::OnEmboss)
	ON_COMMAND(IDM_BLUR, &CColorImageProcessing10View::OnBlur)
	ON_COMMAND(IDM_HIGH_FREQ, &CColorImageProcessing10View::OnHighFreq)
	ON_COMMAND(IDM_ROTATE, &CColorImageProcessing10View::OnRotate)
	ON_COMMAND(ID_GAUSSIAN, &CColorImageProcessing10View::OnGaussian)
	ON_COMMAND(IDM_ALTER_SATURATION, &CColorImageProcessing10View::OnAlterSaturation)
	ON_COMMAND(IDM_EXTRACT_HUE, &CColorImageProcessing10View::OnExtractHue)
	ON_COMMAND(IDM_LOGICAL, &CColorImageProcessing10View::OnLogical)
	ON_COMMAND(IDM_BOW, &CColorImageProcessing10View::OnBow)
	ON_COMMAND(IDM_REVERSE, &CColorImageProcessing10View::OnReverse)
	ON_COMMAND(IDM_Prewitt, &CColorImageProcessing10View::OnPrewitt)
	ON_COMMAND(IDM_LoG, &CColorImageProcessing10View::OnLog)
	ON_COMMAND(IDM_ZOOM_OUT, &CColorImageProcessing10View::OnZoomOut)
	ON_COMMAND(IDM_ZOOM_IN, &CColorImageProcessing10View::OnZoomIn)
END_MESSAGE_MAP()

// CColorImageProcessing10View 생성/소멸

CColorImageProcessing10View::CColorImageProcessing10View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CColorImageProcessing10View::~CColorImageProcessing10View()
{
}

BOOL CColorImageProcessing10View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CColorImageProcessing10View 그리기

void CColorImageProcessing10View::OnDraw(CDC* pDC)
{
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 + 화면 크기 조절
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 화면 크기에 따라 출력 크기 자동 조절
	double MAXSIZE = 800;

	int modifiedInH = pDoc->m_inH;
	int modifiedInW = pDoc->m_inW;

	// 건너 뛸 크기 설정 (1.0이면 그대로, 소수점 이하는 반올림)
	double hop = 1.0;

	if (modifiedInH > MAXSIZE || modifiedInW > MAXSIZE) {
		// 홉을 새로 계산
		if (modifiedInW > modifiedInH) {
			hop = int((modifiedInW / MAXSIZE));
		}
		else {
			hop = int((modifiedInH / MAXSIZE));
		}
		modifiedInH = int(modifiedInH / hop);
		modifiedInW = int(modifiedInW / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < modifiedInH; i++) {
		for (k = 0; k < modifiedInW; k++) {
			int h = i * hop;
			int w = k * hop;
			R = pDoc->m_inImageR[h][w];
			G = pDoc->m_inImageG[h][w];
			B = pDoc->m_inImageB[h][w];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	MAXSIZE = 800;

	int modifiedOutH = pDoc->m_outH;
	int modifiedOutW = pDoc->m_outW;

	// 건너 뛸 크기 설정 (1.0이면 그대로, 소수점 이하는 반올림)
	hop = 1.0;

	if (modifiedOutH > MAXSIZE || modifiedOutW > MAXSIZE) {
		// 홉을 새로 계산
		if (modifiedOutW > modifiedOutH) {
			hop = int((modifiedOutH / MAXSIZE));
		}
		else {
			hop = int((modifiedOutH / MAXSIZE));
		}
		modifiedOutH = int(modifiedOutH / hop);
		modifiedOutW = int(modifiedOutW / hop);
	}


	// 메모리 DC에 그리기
	for (i = 0; i < modifiedOutH; i++) {
		for (k = 0; k < modifiedOutW; k++) {
			int h = i * hop;
			int w = k * hop;
			R = pDoc->m_outImageR[h][w];
			G = pDoc->m_outImageG[h][w];
			B = pDoc->m_outImageB[h][w];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(modifiedInW + 10, 5, modifiedOutW, modifiedOutH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////////////
	if (pDoc->m_backImageR != NULL) {
		// 화면 DC와 호환되는 메모리 DC 객체를 생성
		memDC.CreateCompatibleDC(pDC);

		// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
		bitmap.CreateCompatibleBitmap(pDC, pDoc->m_backH, pDoc->m_backW);

		pOldBitmap = memDC.SelectObject(&bitmap);
		memDC.PatBlt(0, 0, pDoc->m_backW, pDoc->m_backH, WHITENESS); // 흰색으로 초기화

		MAXSIZE = 800;

		int modifiedBackH = pDoc->m_backH;
		int modifiedBackW = pDoc->m_backW;

		// 건너 뛸 크기 설정 (1.0이면 그대로, 소수점 이하는 반올림)
		hop = 1.0;

		if (modifiedBackH > MAXSIZE || modifiedBackW > MAXSIZE) {
			// 홉을 새로 계산
			if (modifiedBackW > modifiedBackH) {
				hop = int((modifiedBackH / MAXSIZE));
			}
			else {
				hop = int((modifiedBackH / MAXSIZE));
			}
			modifiedBackH = int(modifiedBackH / hop);
			modifiedBackW = int(modifiedBackW / hop);
		}


		// 메모리 DC에 그리기
		for (i = 0; i < modifiedBackH; i++) {
			for (k = 0; k < modifiedBackW; k++) {
				int h = i * hop;
				int w = k * hop;
				R = pDoc->m_backImageR[h][w];
				G = pDoc->m_backImageG[h][w];
				B = pDoc->m_backImageB[h][w];
				memDC.SetPixel(k, i, RGB(R, G, B));
			}
		}
		// 메모리 DC를 화면 DC에 고속 복사
		pDC->BitBlt(modifiedInW + modifiedOutW + 10, 5, modifiedBackW, modifiedBackH, &memDC, 0, 0, SRCCOPY);

		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
		bitmap.DeleteObject();
	}

}


// CColorImageProcessing10View 인쇄

BOOL CColorImageProcessing10View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CColorImageProcessing10View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CColorImageProcessing10View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CColorImageProcessing10View 진단

#ifdef _DEBUG
void CColorImageProcessing10View::AssertValid() const
{
	CView::AssertValid();
}

void CColorImageProcessing10View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorImageProcessing10Doc* CColorImageProcessing10View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorImageProcessing10Doc)));
	return (CColorImageProcessing10Doc*)m_pDocument;
}
#endif //_DEBUG


// CColorImageProcessing10View 메시지 처리기


void CColorImageProcessing10View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnGrayScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGrayScale();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnArith()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnArith();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnGamma()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGamma();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnPara()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnPara();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnHistStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistStretch();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnHistEndin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistEndin();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnHistEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistEqual();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnEmboss()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEmboss();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBlur();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnHighFreq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHighFreq();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRotate();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGaussian();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnAlterSaturation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAlterSaturation();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnExtractHue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnExtractHue();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnLogical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLogical();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnBow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBow();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnReverse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnReverse();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnPrewitt();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnLog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLog();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnZoomOut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnZoomOut();
	Invalidate(TRUE);
}


void CColorImageProcessing10View::OnZoomIn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessing10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnZoomIn();
	Invalidate(TRUE);
}
