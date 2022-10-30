
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPractice05.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_pos.x = 100;
	m_pos.y = 100;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
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

	float r = 100.f;
	for (int x = 0; x < 256; ++x)
	{
		for (int y = 0; y < 256; ++y)
		{
			if((x - r)*(x - r) + (y - r)*(y - r) < r * r)
				memDC.SetPixelV(m_pos.x + x, m_pos.y + y, RGB(x, 0, y));
		}
	}
	// (x – r)(x – r) + (y – r)(y – r) < r * r

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pos = point;

	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
