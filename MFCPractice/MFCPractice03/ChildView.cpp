
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPractice03.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
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

	Rectangle(memDC, -1,-1, rect.Width()+1, rect.Height()+1);

	CBrush red(RGB(255, 0, 0));
	CBrush green(RGB(0, 255, 0));
	CBrush blue(RGB(0, 0, 255));

	// Paint
	if (!m_shapes.empty())
	{
		for (const auto& shape : m_shapes)
		{
			if (shape.type == BRUSH_TYPE::RED)
			{
				memDC.SelectObject(&red);
			}
			else if (shape.type == BRUSH_TYPE::GREEN)
			{
				memDC.SelectObject(&green);
			}
			else if (shape.type == BRUSH_TYPE::BLUE)
			{
				memDC.SelectObject(&blue);
			}

			Rectangle(memDC,
				shape.ltPos.x,
				shape.ltPos.y,
				shape.rbPos.x,
				shape.rbPos.y
			);
		}	
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (isLMouseDown)
		m_rbPos = point;

	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	isLMouseDown = true;

	m_ltPos = point;

	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	isLMouseDown = false;

	shape tempShape;
	tempShape.ltPos = m_ltPos;
	tempShape.rbPos = m_rbPos;
	tempShape.type = BRUSH_TYPE::RED;
	
	m_shapes.push_back(tempShape);

	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int back = m_shapes.size();

	if (!m_shapes.empty())
	{
		switch (nChar)
		{
		case 0x52:
			m_shapes.at(back - 1).type = BRUSH_TYPE::RED;
			break;
		case 0x47:
			m_shapes.at(back - 1).type = BRUSH_TYPE::GREEN;
			break;
		case 0x42:
			m_shapes.at(back - 1).type = BRUSH_TYPE::BLUE;
			break;
		}
	}
	Invalidate();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
