
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPractice02.h"
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
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
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
	
	for (const auto& Point : m_Points)
	{
		Rectangle(dc,
			Point.x - 2,
			Point.y - 2,
			Point.x + 2,
			Point.y + 2
		);
	}
	if(isRMouseDown)
		Rectangle(dc, m_ltPos.x, m_ltPos.y, m_rbPos.x, m_rbPos.y);

	wstring count = L"" + to_wstring(m_Points.size());

	TextOut(dc, 100, 100, count.c_str(), count.size());

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (isLMouseDown)
		m_Points.push_back(point);
	
	if (isRMouseDown)
		m_rbPos = point;


	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isLMouseDown = true;


	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isLMouseDown = false;


	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	isRMouseDown = true;
	m_ltPos = point;

	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isRMouseDown = false;

	vector<CPoint> tempPoints;

	if (!m_Points.empty())
	{
		for (const auto& Point : m_Points)
		{
			// 사각형 내부에 들어가는지 검사
			if (!((Point.x >= m_ltPos.x && Point.x <= m_rbPos.x)
				&& (Point.y >= m_ltPos.y && Point.y <= m_rbPos.y)))
				tempPoints.push_back(Point);
		}
	}
	m_Points.clear();
	m_Points = tempPoints;

	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}
