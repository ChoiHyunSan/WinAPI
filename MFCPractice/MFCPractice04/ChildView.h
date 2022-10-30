
// ChildView.h: CChildView 클래스의 인터페이스
//

#include <iostream>
#include <vector>
using std::vector;

#pragma once
enum class BRUSH_TYPE
{
	RED = 0,
	GREEN,
	BLUE,
	YELLOW
};

struct shape
{
	CPoint ltPos;
	CPoint rbPos;

	BRUSH_TYPE type;

};

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	vector<shape> m_shapes;

	CPoint m_ltPos;
	CPoint m_rbPos;

	bool isLMouseDown = false;
	bool isSelect = false;

	int selectCount = -1;
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

