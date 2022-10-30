
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPractice07.h"
#include "ChildView.h"
#include < cstdlib >
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
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
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

	Rectangle(memDC, 
		m_pos.x - size, 
		m_pos.y - size, 
		m_pos.x + size,
		m_pos.y + size);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	check = true;
	float sum = sqrt(abs((double)point.x - (double)m_pos.x) + abs((double)point.y - (double)m_pos.y));
	m_dtX = (point.x - m_pos.x) / sum;
	m_dtY = (point.y - m_pos.y) / sum;

	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	check = false;
	switch (nChar)
	{
	case VK_LEFT:
		m_dtX = -10.f;
		m_dtY = 0.f;
		break;
	case VK_RIGHT:
		m_dtX = 10.f;
		m_dtY = 0.f;
		break;
	case VK_UP:
		m_dtX = 0.f;
		m_dtY = -10.f;
		break;
	case VK_DOWN:
		m_dtX = 0.f;
		m_dtY = 10.f;
		break;
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	SetTimer(0, 50, NULL);
	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0)
	{
		CRect rect;
		GetClientRect(rect);

		// 벽에 부딪히면 x,y 변화량에 -1를 곱한다.
		if (m_pos.x - size <= 0.f || m_pos.x + size > rect.Width()
			|| m_pos.y - size < 0.f || m_pos.y + size > rect.Height())
		{
			if (check)
			{
				if (m_pos.x - size <= 0.f || m_pos.x + size > rect.Width()) m_dtX *= -1;
				else if (m_pos.y - size <= 0.f || m_pos.y + size > rect.Height()) m_dtY *= -1;
			}
			else
			{
				m_dtY *= -1;
				m_dtX *= -1;
			}
		}

		m_pos.x += m_dtX;
		m_pos.y += m_dtY;

		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}
