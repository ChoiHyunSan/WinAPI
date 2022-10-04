
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "B877039_CHS_MFC_HW1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	: isLMouseDown(false)
	, isRMouseDown(false)
	, isMMouseDown(false)
{

}

CChildView::~CChildView()
{
	// 동적으로 할당하여 저장한 도형들을 제거한다.
	for (auto& shape : shapes)
	{
		if(shape != nullptr)
			delete shape;
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONUP()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

void CChildView::setRbPos(CPoint point)
{
	tempShape.rbPos.x = point.x;
	tempShape.rbPos.y = point.y;
}

void CChildView::setLtPos(CPoint point)
{
	tempShape.ltPos.x = point.x;
	tempShape.ltPos.y = point.y;
}

void CChildView::addObject(SHAPE_TYPE type)
{
	Shape* shape = new Shape(tempShape.ltPos, tempShape.rbPos, type);

	if(shape != nullptr)
		shapes.push_back(shape);
}

void CChildView::setDrawingTool(HDC dc, PEN_TYPE pType, BRUSH_TYPE bType)
{
	setBrush(dc, bType);
	setPen(dc,pType);
}

void CChildView::setPen(HDC dc, PEN_TYPE type)
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	switch (type)
	{
	case PEN_TYPE::RED:
		pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		break;
	case PEN_TYPE::BLUE:
		pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		break;
	case PEN_TYPE::GREEN:
		pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		break;
	}

	HPEN prevPen = (HPEN)SelectObject(dc, pen);
	DeleteObject(prevPen);
}

void CChildView::setBrush(HDC dc, BRUSH_TYPE type)
{
	// 비트맵 그리고 추가할 예정
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);

	switch (type)
	{
	case BRUSH_TYPE::SINGLE:
		brush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case BRUSH_TYPE::OBITMAP:
		brush = CreatePatternBrush(bitmap);
		break;
	}

	HBRUSH prevBrush = (HBRUSH)SelectObject(dc, brush);
	DeleteObject(prevBrush);
}

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

	for (auto& const shape : shapes)
	{
		switch (shape->type)
		{
		case SHAPE_TYPE::RECTANGLE:
			setDrawingTool(dc, PEN_TYPE::RED, BRUSH_TYPE::SINGLE);
			Ellipse(dc, 
				shape->ltPos.x,
				shape->ltPos.y,
				shape->rbPos.x,
				shape->rbPos.y);
			break;

		case SHAPE_TYPE::ELLIPSE:
			// 브러시 타입 수정 필요 (BITMAP)
			setDrawingTool(dc, PEN_TYPE::RED, BRUSH_TYPE::OBITMAP);
			Rectangle(dc,
				shape->ltPos.x,
				shape->ltPos.y,
				shape->rbPos.x,
				shape->rbPos.y);
			break;
		}
	}

	if (isLMouseDown)
	{
		Ellipse(dc,
			tempShape.ltPos.x,
			tempShape.ltPos.y,
			tempShape.rbPos.x,
			tempShape.rbPos.y);
	}
	if (isRMouseDown)
	{
		Rectangle(dc,
			tempShape.ltPos.x,
			tempShape.ltPos.y,
			tempShape.rbPos.x,
			tempShape.rbPos.y);
	}
	if (isMMouseDown)
	{

	}

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isMMouseDown = true;
	Invalidate();
	CWnd::OnMButtonDown(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isLMouseDown = true;

	setLtPos(point);
	
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isLMouseDown = false;

	setRbPos(point);
	addObject(SHAPE_TYPE::RECTANGLE);

	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isRMouseDown = true;

	setLtPos(point);

	Invalidate();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isRMouseDown = false;

	setRbPos(point);
	addObject(SHAPE_TYPE::ELLIPSE);

	Invalidate();

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	setRbPos(point);

	Invalidate();

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isMMouseDown = false;
	Invalidate();

	CWnd::OnMButtonUp(nFlags, point);
}
