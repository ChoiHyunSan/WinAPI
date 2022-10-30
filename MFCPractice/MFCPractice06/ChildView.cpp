
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPractice06.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	CBitmap brushBitmap;
	brushBitmap.LoadBitmap(IDB_BITMAP1);

	brush = CreatePatternBrush(brushBitmap);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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

	CBitmap _bitmap;
	_bitmap.LoadBitmap(IDB_BITMAP1);
	BITMAP bmpinfo;
	_bitmap.GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(&memDC);
	dcmem.SelectObject(&_bitmap);

	CBitmap bitmap; // 그림을 저장할 bitmap 공간 마련
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap); // Bitmap 공간을 가상 DC에 연결
	Rectangle(memDC, -10, -10, rect.Width() + 10, rect.Height() + 10);
	
	memDC.SelectObject(brush);

	memDC.StretchBlt(
		(rect.Width() / 2) - (rect.Height() * 0.5 / 2),
		0,
		rect.Height() * 0.5,
		rect.Height(),
		&dcmem,
		0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
