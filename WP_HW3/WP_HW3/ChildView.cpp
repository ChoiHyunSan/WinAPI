
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WP_HW3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	:
	isReplay(false),
	color(RGB(0, 0, 0))
{

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	//	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_COMMAND(ID_CLEAR, &CChildView::OnClear)
	ON_UPDATE_COMMAND_UI(ID_CLEAR, &CChildView::OnUpdateClear)
	ON_COMMAND(ID_SAVE, &CChildView::OnSave)
	ON_UPDATE_COMMAND_UI(ID_SAVE, &CChildView::OnUpdateSave)
	ON_COMMAND(ID_LOAD, &CChildView::OnLoad)
	ON_UPDATE_COMMAND_UI(ID_LOAD, &CChildView::OnUpdateLoad)
	ON_COMMAND(ID_REPLAY, &CChildView::OnReplay)
	ON_UPDATE_COMMAND_UI(ID_REPLAY, &CChildView::OnUpdateReplay)
	ON_COMMAND(ID_STOP, &CChildView::OnStop)
	ON_UPDATE_COMMAND_UI(ID_STOP, &CChildView::OnUpdateStop)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

void CChildView::DrawShape(TYPE _type, CPoint _pos, CDC _dc)
{
	if (_type == TYPE::RECT)
	{
		Rectangle(_dc,
			_pos.x - 40,
			_pos.y - 40,
			_pos.x + 40,
			_pos.y + 40
		);
	}
	else if (_type == TYPE::CIRCLE)
	{
		Ellipse(_dc,
			_pos.x - 40,
			_pos.y - 40,
			_pos.x + 40,
			_pos.y + 40
		);
	}
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	CDC memDC; // 그리기를 위한 디바이스 컨텍스트입니다.
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(rect);

	CBitmap bitmap; // 그림을 저장할 bitmap 공간 마련
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	memDC.SelectObject(&bitmap); // Bitmap 공간을 가상 DC에 연결
	Rectangle(memDC, -10, -10, rect.Width() + 10, rect.Height() + 10);


	// 도형이 하나 이상인 경우에 도형을 이어주는 실선을 그린다.
	if (shapes.size() > 1)
	{
		color = RGB(0, 0, 0);
		HPEN pen = CreatePen(PS_DOT, 1, color);
		memDC.SelectObject(pen);

		for (int i = 0; i < shapes.size() - 1; i++)
		{
			memDC.MoveTo(shapes[i].pos.x, shapes[i].pos.y);
			memDC.LineTo(shapes[i + 1].pos.x, shapes[i + 1].pos.y);
		}
	}

	// 도형을 그린다. * Replay시에는 그리지 않는다.
	if (!isReplay)
	{

		if (shapes.empty()) return;

		// 마지막을 제외한 도형들을 그린다.
		for (int i = 0; i < shapes.size(); i++)
		{
			if (i != selectIndex)
			{
				// 검정색 브러시를 선택하여 그린다.
				color = RGB(0, 0, 0);
				HPEN pen = CreatePen(PS_SOLID, 5, color);
				memDC.SelectObject(pen);
			}
			else
			{
				color = RGB(255, 0, 0);
				HPEN pen = CreatePen(PS_SOLID, 5, color);
				memDC.SelectObject(pen);
			}


			if (shapes[i].type == TYPE::RECT)
			{
				Rectangle(memDC,
					shapes[i].pos.x - 40,
					shapes[i].pos.y - 40,
					shapes[i].pos.x + 40,
					shapes[i].pos.y + 40
				);
			}
			else if (shapes[i].type == TYPE::CIRCLE)
			{
				Ellipse(memDC,
					shapes[i].pos.x - 40,
					shapes[i].pos.y - 40,
					shapes[i].pos.x + 40,
					shapes[i].pos.y + 40
				);
			}
		}
		//else
		//{
		//	// 마지막 도형을 빨간색으로 칠해서 그린다.
		//	if (!shapes.empty())
		//	{
		//		color = RGB(255, 0, 0);
		//		HPEN pen = CreatePen(PS_SOLID, 5, color);
		//		memDC.SelectObject(pen);

		//		int index = shapes.size() - 1;

		//		if (shapes[index].type == TYPE::RECT)
		//		{
		//			Rectangle(memDC,
		//				shapes[index].pos.x - 40,
		//				shapes[index].pos.y - 40,
		//				shapes[index].pos.x + 40,
		//				shapes[index].pos.y + 40
		//			);
		//		}
		//		else if (shapes[index].type == TYPE::CIRCLE)
		//		{
		//			Ellipse(memDC,
		//				shapes[index].pos.x - 40,
		//				shapes[index].pos.y - 40,
		//				shapes[index].pos.x + 40,
		//				shapes[index].pos.y + 40
		//			);
		//		}
		//	}

	}
	// RePlay 모드 시, 실선을 따라 사각형이 움직인다.
	else
	{
		color = RGB(0, 0, 0);
		HPEN pen = CreatePen(PS_SOLID, 2, color);
		memDC.SelectObject(pen);

		RoundRect(memDC,
			ReplayPos.x - 40,
			ReplayPos.y - 40,
			ReplayPos.x + 40,
			ReplayPos.y + 40,
			ratioOfRect,
			ratioOfRect
			);

	}


	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (isReplay) return;

	Shape shape(point, TYPE::RECT);
	shapes.push_back(shape);

	selectIndex = shapes.size() - 1;
	scrollBar.SetScrollRange(0, shapes.size()-1);
	scrollBar.SetScrollPos(shapes.size() - 1);
	CWnd::OnLButtonDown(nFlags, point);
	Invalidate();
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (isReplay) return;

	Shape shape(point, TYPE::CIRCLE);
	shapes.push_back(shape);

	selectIndex = shapes.size() - 1;
	scrollBar.SetScrollRange(0, shapes.size()-1);
	scrollBar.SetScrollPos(shapes.size() - 1);
	CWnd::OnRButtonDown(nFlags, point);
	Invalidate();
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 버튼을 생성하고 아이디를 지정한다.

	clearButton.Create(_T("CLEAR"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 100, 30), this, ID_CLEAR);

	saveButton.Create(_T("SAVE"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 0, 200, 30), this, ID_SAVE);

	loadButton.Create(_T("LOAD"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(200, 0, 300, 30), this, ID_LOAD);

	replayButton.Create(_T("REPLAY"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(300, 0, 400, 30), this, ID_REPLAY);

	stopButton.Create(_T("STOP"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(400, 0, 500, 30), this, ID_STOP);

	scrollBar.Create(SBS_HORZ, CRect(500,0,1000,30),this, ID_SCROLLBAR);

	scrollBar.ShowWindow(true);
	scrollBar.SetScrollRange(0, 0);
	scrollBar.SetScrollPos(0);

	SetTimer(0, 50, NULL);

	return 0;
}



void CChildView::OnClear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (isReplay) return;

	shapes.clear();

	Invalidate();

}


void CChildView::OnUpdateClear(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.


}


void CChildView::OnSave()
{
	if (isReplay) return;

	CFile file(_T("circle.dat"), CFile::modeWrite | CFile::modeCreate);

	CArchive ar(&file, CArchive::store);


	int num = shapes.size();
	ar << num;

	for (const auto& shape : shapes)
	{
		CPoint pt = shape.pos;
		ar << pt;

		TYPE type = shape.type;
		ar << static_cast<int>(type);
	}

	ar.Close();
	file.Close();
}


void CChildView::OnUpdateSave(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnLoad()
{
	if (isReplay) return;

	CFile file(_T("circle.dat"), CFile::modeRead);

	shapes.clear();

	CArchive ar(&file, CArchive::load);
	int num;
	ar >> num;

	for (int i = 0; i < num; i++)
	{
		CPoint pt;
		ar >> pt;

		int type;
		ar >> type;

		Shape temp(pt,static_cast<TYPE>(type));

		shapes.push_back(temp);
	}

	ar.Close();
	file.Close();

	Invalidate();
}


void CChildView::OnUpdateLoad(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnReplay()
{
	// Replay 모드를 활성화시킨다.
	isReplay = true;

	// 실선의 처음 부분부터 이동하게끔 만든다.

	if (shapes.empty()) return;

	curIndex = 0;
	ReplayPos = shapes[0].pos;

	curPos = shapes[0].pos;
	scrollBar.SetScrollPos(0);

	if (shapes[0].type == TYPE::RECT)
	{
		isChangeToRect = false;
		ratioOfRect = 0.f;
	}
	else
	{
		isChangeToRect = true;
		ratioOfRect = 80.f;
	}

	if (shapes.size() == 1)
	{
		nextPos = shapes[0].pos;
	}
	else
	{
		nextPos = shapes[1].pos;
	}
	count = 0;
	Invalidate();
}


void CChildView::OnUpdateReplay(CCmdUI* pCmdUI)
{

}


void CChildView::OnStop()
{
	// Replay 모드를 비활성화 시킨다.
	isReplay = false;
	
	scrollBar.SetScrollPos(selectIndex);

	Invalidate();
}


void CChildView::OnUpdateStop(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{

	if (nIDEvent == 0 && isReplay == true)
	{
		if(count == 14)
		{
			if (curIndex == shapes.size() - 2)
			{
				curIndex = 0;
				
				if (shapes[curIndex].type == TYPE::RECT)
				{
					ratioOfRect = 0.f;
				}
				else
				{
					ratioOfRect = 80.f;
				}

				if (shapes[curIndex].type == TYPE::RECT)
				{
					isChangeToRect = true;
				}
				else
				{
					isChangeToRect = false;
				}
			}
			else
			{
				curIndex++;

				if (shapes[curIndex].type == TYPE::RECT)
				{
					isChangeToRect = true;
				}
				else
				{
					isChangeToRect = false;
				}

			}
			ReplayPos = shapes[curIndex].pos;
			scrollBar.SetScrollPos(curIndex);
			count = 0;
		}

		if (shapes.empty()) return;

		if (shapes.size() != 1)
		{
			curPos = shapes[curIndex].pos;
			nextPos = shapes[curIndex + 1].pos;
		}
		// 거리에 비례해서 이동 속도를 조절한다.
		dx = (nextPos.x - curPos.x);
		dy = (nextPos.y - curPos.y);

		ReplayPos.x += dx / 15;
		ReplayPos.y += dy / 15;

		// 현재 타입과 다음 타입이 같지 않다면 모양을 변경한다.
		if (shapes.size() != 1 
			&& shapes[curIndex].type != shapes[curIndex+1].type)
		{
			if (isChangeToRect)
			{
				ratioOfRect -= 80 / 15.f;
			}
			else
			{
				ratioOfRect += 80 / 15.f;
			}
		}

		count++;
		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}

void CChildView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.





	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (pScrollBar != NULL) {
		if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION
			&& !isReplay) {
			selectIndex = nPos;
			pScrollBar->SetScrollPos(nPos);
		}

		if (nSBCode == SB_LINELEFT)
		{
			if (!isReplay)
			{
				if (selectIndex != 0)
				{
					selectIndex--;
				}
				pScrollBar->SetScrollPos(selectIndex);
			}
			else
			{
				if (curIndex != 0)
				{
					curIndex--;
				}

				pScrollBar->SetScrollPos(curIndex);
				ReplayPos = shapes[curIndex].pos;
				count == 0;
			}
		}
		else if (nSBCode == SB_LINERIGHT)
		{
			if (!isReplay)
			{
				if (selectIndex != shapes.size() - 1)
				{
					selectIndex++;
				}
				pScrollBar->SetScrollPos(selectIndex);
			}
			else
			{
				if (curIndex != shapes.size() - 1)
				{
					curIndex++;
				}
				ReplayPos = shapes[curIndex].pos;
				count == 0;
				pScrollBar->SetScrollPos(curIndex);
			}

		}
	}

	Invalidate();

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}
