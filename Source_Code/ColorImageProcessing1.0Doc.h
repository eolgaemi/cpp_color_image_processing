
// ColorImageProcessing1.0Doc.h: CColorImageProcessing10Doc 클래스의 인터페이스
//


#pragma once


class CColorImageProcessing10Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessing10Doc() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessing10Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CColorImageProcessing10Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;


	unsigned char** OnMalloc2D(int height, int width);

	template <typename T>
	void OnFree2D(T** memory, int height);
	void OnFreeInimage();
	void OnFreeOutimage();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnGrayScale();
	void OnArith();
	void OnArithCal(double value, char select);
	unsigned char* OnHSI2RGB(double H, double S, double I);
	double* OnRGB2HSI(int R, int G, int B);
	void OnGamma();
	void OnPara();
	void OnHistStretch();
	void OnHistEndin();
	void OnHistEqual();
	void OnEmboss();
	double** OnMalloc2D_double(int height, int width);
	void OnBlur();
	void OnHighFreq();
	void OnRotate();
	int m_degree = 0;
	unsigned char** m_backImage = NULL;
	unsigned char** m_backImageR = NULL;
	unsigned char** m_backImageG = NULL;
	unsigned char** m_backImageB = NULL;
	int m_backH = 0;
	int m_backW = 0;
	void OnFreeBackimage();
	void OnGaussian();
	void OnAlterSaturation();
	void OnExtractHue();
	void OnLogical();
	void OnLogicalCal(int value, char select);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnBow();
	void OnReverse();
	void OnPrewitt();
	void OnLog();
	void OnZoomOut();
	void OnZoomIn();
};
