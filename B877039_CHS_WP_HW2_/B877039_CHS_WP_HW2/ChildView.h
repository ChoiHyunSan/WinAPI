
// ChildView.h: CChildView 클래스의 인터페이스
//
#include <afxtempl.h>

#pragma once
enum class DRAW_TYPE
{
	RECT = 0,
	CIRCLE
};

enum class MOVE_DIR
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	DEFAULT
};

struct shape
{
	CPoint point;
	COLORREF color;
	DRAW_TYPE type;

	shape(CPoint _point, COLORREF _color, DRAW_TYPE _type) :
		point(_point), color(_color), type(_type)
	{

	}

	shape()
	{

	}
};

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	DRAW_TYPE	eDrawType = DRAW_TYPE::RECT;	// 현재 지원하는 그리기 모드
	bool		isEraserMove = false;			// 지우개가 움직일 수 있는지 체크
	COLORREF	color = RGB(0,0,0);

	CList<shape> shapes;

	CPoint erase_FirstPos;
	CPoint erase_SecondPos;
	MOVE_DIR erase_dir = MOVE_DIR::DEFAULT;

	bool isRButtonDown = false;
	bool isLButtonDown = false;

	float m_dtX = 0;
	float m_dtY = 0;

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
protected:

public:
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnDrawRec();
	afx_msg void OnUpdateDrawRec(CCmdUI* pCmdUI);
	afx_msg void OnMoveEraser();
	afx_msg void OnUpdateMoveEraser(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnColorBlack();
	afx_msg void OnUpdateColorBlack(CCmdUI* pCmdUI);
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnColorGreen();
	afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnColorRed();
	afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

