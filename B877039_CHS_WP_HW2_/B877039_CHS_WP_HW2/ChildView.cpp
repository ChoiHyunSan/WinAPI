
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "B877039_CHS_WP_HW2.h"
#include "ChildView.h"
#include <string>

using namespace std;
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
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CChildView::OnUpdateDrawCircle)
	ON_COMMAND(ID_DRAW_REC, &CChildView::OnDrawRec)
	ON_UPDATE_COMMAND_UI(ID_DRAW_REC, &CChildView::OnUpdateDrawRec)
	ON_COMMAND(ID_MOVE_ERASER, &CChildView::OnMoveEraser)
	ON_UPDATE_COMMAND_UI(ID_MOVE_ERASER, &CChildView::OnUpdateMoveEraser)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_COLOR_BLACK, &CChildView::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CChildView::OnUpdateColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_WM_ERASEBKGND()
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
	CPaintDC dc(this);

	CDC memDC; // 그리기를 위한 디바이스 컨텍스트입니다.
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(rect);
	CBitmap bitmap; // 그림을 저장할 bitmap 공간 마련
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap); // Bitmap 공간을 가상 DC에 연결
	Rectangle(memDC, -10, -10, rect.Width() + 10, rect.Height() + 10);

	// 지우개를 그리고 좌상단 꼭지점고 우하단 꼭지점을 지정한다.
	CPoint ltPos;
	CPoint rbPos;
	{
		if (erase_FirstPos.x > erase_SecondPos.x) { ltPos.x = erase_SecondPos.x; rbPos.x = erase_FirstPos.x; }
		else { ltPos.x = erase_FirstPos.x;  rbPos.x = erase_SecondPos.x; }

		if (erase_FirstPos.y > erase_SecondPos.y) { ltPos.y = erase_SecondPos.y; rbPos.y = erase_FirstPos.y; }
		else { ltPos.y = erase_FirstPos.y;  rbPos.y = erase_SecondPos.y; }

		// Draw Eraser
		Rectangle(memDC,
			ltPos.x,
			ltPos.y,
			rbPos.x,
			rbPos.y);
	}

	//



	// 지우개와 영역이 곂치는 도형들을 리스트에서 제거한다.
	if (!shapes.IsEmpty())
	{
		POSITION pos = shapes.GetHeadPosition();
		CList<shape> tempList;
		while (pos != NULL)
		{
			shape temp = shapes.GetNext(pos);
			if ((temp.point.x >= ltPos.x && temp.point.x <= rbPos.x)
				&& (temp.point.y >= ltPos.y && temp.point.y <= rbPos.y))
			{
				
			}
			else
			{
				tempList.AddTail(temp);
			}

		}
		shapes.RemoveAll();
		
		pos = tempList.GetHeadPosition();
		while (pos != NULL)
		{
			shapes.AddTail(tempList.GetNext(pos));
		}

		pos = shapes.GetHeadPosition();
		while (pos != NULL)
		{
			shape temp = shapes.GetNext(pos);

			CPen pen(PS_SOLID,1,temp.color);
			CBrush brush = temp.color;
			memDC.SelectObject(&brush);
			memDC.SelectObject(&pen);

			if(temp.type == DRAW_TYPE::RECT)
				Rectangle(memDC,
					temp.point.x - 5,
					temp.point.y - 5,
					temp.point.x + 5,
					temp.point.y + 5);
			else
				Ellipse(memDC,
					temp.point.x - 5,
					temp.point.y - 5,
					temp.point.x + 5,
					temp.point.y + 5);
		}		
	}

	wstring count = L"Shape Count : " + to_wstring(shapes.GetSize());
	TextOut(memDC, 10, 10, count.c_str(), count.size());

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}



void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{

}

void CChildView::OnDrawCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	eDrawType = DRAW_TYPE::CIRCLE;

	Invalidate();
}


void CChildView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (eDrawType == DRAW_TYPE::CIRCLE)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);


	Invalidate();
}

void CChildView::OnDrawRec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	eDrawType = DRAW_TYPE::RECT;

	Invalidate();
}


void CChildView::OnUpdateDrawRec(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (eDrawType == DRAW_TYPE::RECT)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
	
	Invalidate();
}


void CChildView::OnMoveEraser()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (isEraserMove) 
	{ 
		isEraserMove = false; 
		m_dtX = 0.f;
		m_dtY = 0.f;
	}
	else 
	{ 
		isEraserMove = true; 
		m_dtX = 0.f;
		m_dtY = 0.f;
	}

	Invalidate();
}


void CChildView::OnUpdateMoveEraser(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (isEraserMove)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);

	Invalidate();
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (isRButtonDown) erase_SecondPos = point;

	if (isLButtonDown)
	{
		shapes.AddTail(shape(point, color, eDrawType));
	}
	
	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isLButtonDown = false;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	isLButtonDown = true;

	shapes.AddTail(shape(point, color, eDrawType));

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	erase_FirstPos = point;
	erase_SecondPos = point;
	isRButtonDown = true;

	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isRButtonDown = false;


	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	color = RGB(0, 0, 0);

	Invalidate();
}


void CChildView::OnUpdateColorBlack(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (color == RGB(0, 0, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	color = RGB(0, 0, 255);
	Invalidate();
}


void CChildView::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (color == RGB(0, 0, 255))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	color = RGB(0, 255, 0);
	Invalidate();

}


void CChildView::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (color == RGB(0, 255, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	color = RGB(255, 0, 0);
	Invalidate();
}


void CChildView::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (color == RGB(255, 0, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!isEraserMove) return;
	
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
		if (!isEraserMove) return;

		CRect rect;
		GetClientRect(rect);

		CPoint m_pos;

		CPoint ltPos;
		CPoint rbPos;
		{
			if (erase_FirstPos.x > erase_SecondPos.x) { ltPos.x = erase_SecondPos.x; rbPos.x = erase_FirstPos.x; }
			else { ltPos.x = erase_FirstPos.x;  rbPos.x = erase_SecondPos.x; }

			if (erase_FirstPos.y > erase_SecondPos.y) { ltPos.y = erase_SecondPos.y; rbPos.y = erase_FirstPos.y; }
			else { ltPos.y = erase_FirstPos.y;  rbPos.y = erase_SecondPos.y; }
		}

		if (ltPos == rbPos) return;

		// 벽에 부딪히면 x,y 변화량에 -1를 곱한다.
		//if (ltPos.x <= 0.f || rbPos.x >= rect.Width()) m_dtX *= -1;
		if (ltPos.x <= 0.f)
		{
			m_dtX = 10.f;
		}
		else if (rbPos.x >= rect.Width())
		{
			m_dtX = -10.f;
		}
		//else if (ltPos.y <= 0.f || rbPos.y >= rect.Height()) m_dtY *= -1;
		if (ltPos.y <= 0.f)
		{
			m_dtY = 10.f;
		}
		else if (rbPos.y >= rect.Height())
		{
			m_dtY = -10.f;
		}

		erase_FirstPos.x += m_dtX;
		erase_SecondPos.x += m_dtX;
		erase_FirstPos.y += m_dtY;
		erase_SecondPos.y += m_dtY;

		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}
