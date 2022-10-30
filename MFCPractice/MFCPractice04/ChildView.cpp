
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPractice04.h"
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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(rect);

	CBitmap bitmap; // 그림을 저장할 bitmap 공간 마련
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap); // Bitmap 공간을 가상 DC에 연결

	Rectangle(memDC, -1, -1, rect.Width() + 1, rect.Height() + 1);
	CBrush yellow(RGB(255,255, 0));
	CBrush white(RGB(255, 255, 255));

	//
	if (!m_shapes.empty())
	{
		for (int i = 0; i < m_shapes.size(); i++)
		{
			if (i == selectCount)
			{
				memDC.SelectObject(&yellow);
			}
			Rectangle(memDC,
				m_shapes[i].ltPos.x,
				m_shapes[i].ltPos.y,
				m_shapes[i].rbPos.x,
				m_shapes[i].rbPos.y);
			memDC.SelectObject(&white);
		}
	}
	//
	
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isLMouseDown = true;
	m_ltPos = point; 

	if (!isSelect)
	{
		if (!m_shapes.empty())
		{
			for (int i = m_shapes.size() - 1; i >= 0; i--)
			{
				if (
					(m_shapes[i].ltPos.x <= point.x && m_shapes[i].rbPos.x >= point.x ) &&
					(m_shapes[i].ltPos.y <= point.y && m_shapes[i].rbPos.y >= point.y)
					)
				{
					selectCount = i;
					isSelect = true;
					Invalidate();
					CWnd::OnLButtonDown(nFlags, point);
					return;
				}
			}
		}
	}

	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.	
	isLMouseDown = false;

	if (!isSelect)
	{
		shape tempShape;

		tempShape.ltPos = m_ltPos;
		tempShape.rbPos = m_rbPos;

		m_shapes.push_back(tempShape);
	}
	else
	{
		isSelect = false;
		selectCount = -1;
	}


	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if(isLMouseDown == true)
		m_rbPos = point;

	if (isSelect)
	{
		float width = m_shapes[selectCount].rbPos.x - m_shapes[selectCount].ltPos.x;
		float height = m_shapes[selectCount].rbPos.y - m_shapes[selectCount].ltPos.y;
		m_shapes[selectCount].ltPos.x = point.x - width / 2;
		m_shapes[selectCount].ltPos.y = point.y - height / 2;
		m_shapes[selectCount].rbPos.x = point.x + width / 2;
		m_shapes[selectCount].rbPos.y = point.y + height / 2;
	}
	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
