
// ChildView.h: CChildView 클래스의 인터페이스
//
#include <iostream>
#include <vector>
using namespace std;
using std::vector;
#pragma once


// CChildView 창

struct Pos
{
	CPoint ltPos;
	CPoint rbPos;

	Pos()
	{

	}
	Pos(CPoint lt, CPoint rb):
		ltPos(lt), rbPos(rb)
	{

	}
};

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	vector<Pos> m_Lines;

	CPoint m_ltPos;
	CPoint m_rbPos;

	bool isLMouseDown;
	bool isRMouseDown;

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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

