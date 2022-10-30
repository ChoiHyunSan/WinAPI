
// ChildView.h: CChildView 클래스의 인터페이스
//
#pragma once
#include <vector>
using namespace std;
using std::vector;

// CChildView 창

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

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	vector<shape> m_shapes;

	BRUSH_TYPE brushType;

	CPoint m_ltPos;
	CPoint m_rbPos;

	bool isLMouseDown = false;
// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

