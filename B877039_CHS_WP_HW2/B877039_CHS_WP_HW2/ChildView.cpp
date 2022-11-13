
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "B877039_CHS_WP_HW2.h"
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


	// 지우개를 그리고 좌상단 꼭지점고 우하단 꼭지점을 지정한다.
	CPoint ltPos;
	CPoint rbPos;
	{
		if (erase_FirstPos.x > erase_SecondPos.x) { ltPos.x = erase_SecondPos.x; rbPos.x = erase_FirstPos.x; }
		else { ltPos.x = erase_FirstPos.x;  rbPos.x = erase_SecondPos.x; }

		if (erase_FirstPos.y > erase_SecondPos.y) { ltPos.y = erase_SecondPos.y; rbPos.y = erase_FirstPos.y; }
		else { ltPos.y = erase_FirstPos.y;  rbPos.y = erase_SecondPos.y; }

		// Draw Eraser
		Rectangle(dc,
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

			CBrush brush = temp.color;
			dc.SelectObject(&brush);

			if(temp.type == DRAW_TYPE::CIRCLE)
				Rectangle(dc,
					temp.point.x - 5,
					temp.point.y - 5,
					temp.point.x + 5,
					temp.point.y + 5);
			else
				Ellipse(dc,
					temp.point.x - 5,
					temp.point.y - 5,
					temp.point.x + 5,
					temp.point.y + 5);
		}		
	}
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

	Invalidate();
}


void CChildView::OnDrawRec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	eDrawType = DRAW_TYPE::CIRCLE;

	Invalidate();
}


void CChildView::OnUpdateDrawRec(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	

	Invalidate();
}


void CChildView::OnMoveEraser()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (isEraserMove) isEraserMove = false;
	else isEraserMove = true;

	Invalidate();
}


void CChildView::OnUpdateMoveEraser(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.


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
