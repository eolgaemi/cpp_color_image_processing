
// ColorImageProcessing1.0View.h: CColorImageProcessing10View 클래스의 인터페이스
//

#pragma once


class CColorImageProcessing10View : public CView
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessing10View() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessing10View)

// 특성입니다.
public:
	CColorImageProcessing10Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CColorImageProcessing10View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGrayScale();
	afx_msg void OnArith();
	afx_msg void OnGamma();
	afx_msg void OnPara();
	afx_msg void OnHistStretch();
	afx_msg void OnHistEndin();
	afx_msg void OnHistEqual();
	afx_msg void OnEmboss();
	afx_msg void OnBlur();
	afx_msg void OnHighFreq();
	afx_msg void OnRotate();
	afx_msg void OnGaussian();
	afx_msg void OnAlterSaturation();
	afx_msg void OnExtractHue();
	afx_msg void OnLogical();
	afx_msg void OnBow();
	afx_msg void OnReverse();
	afx_msg void OnPrewitt();
	afx_msg void OnLog();
	afx_msg void OnZoomOut();
	afx_msg void OnZoomIn();
};

#ifndef _DEBUG  // ColorImageProcessing1.0View.cpp의 디버그 버전
inline CColorImageProcessing10Doc* CColorImageProcessing10View::GetDocument() const
   { return reinterpret_cast<CColorImageProcessing10Doc*>(m_pDocument); }
#endif

