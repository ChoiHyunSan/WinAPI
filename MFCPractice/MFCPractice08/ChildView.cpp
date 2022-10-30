
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPractice08.h"
#include "ChildView.h"
#include <string>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	: dt(3.f)
{
	m_pos.x = 100;
	m_pos.y = 100;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(rect);
	CBitmap bitmap; // 그림을 저장할 bitmap 공간 마련
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap); // Bitmap 공간을 가상 DC에 연결
	Rectangle(memDC, -10, -10, rect.Width() + 10, rect.Height() + 10);

	CBrush cbrush(RGB(cValue, 0 , 0));
	memDC.SelectObject(&cbrush);

	Ellipse(memDC,
		m_pos.x - dtSize,
		m_pos.y - dtSize,
		m_pos.x + dtSize,
		m_pos.y + dtSize
	);
	Ellipse(memDC,
		0,
		0,
		100,
		100
	);

	wstring count = L"wow";
	TextOut(memDC, 500, 500, count.c_str(), count.size());
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pos = point;
	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0)
	{
		if (isBig)
			dt = 3;
		else
			dt = -3;

		if (isBig == true && dtSize > 50.f) isBig = false;
		else if (isBig == false && dtSize < 30.f) isBig = true;

		if (Color)
			cDt = 5;
		else
			cDt = -5;

		if (Color == true && cValue > 200.f) Color = false;
		else if (Color == false && cValue < 10.f) Color = true;

		dtSize += dt;
		cValue += cDt;
		
		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 33, NULL);		// 타이머 0

	return 0;
}
