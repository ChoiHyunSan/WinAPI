
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include <afxtempl.h>
#include <vector>

using std::vector;

enum class TYPE
{
	RECT = 0,
	CIRCLE
};

struct Shape
{
	CPoint pos;
	TYPE type;

	Shape()
	{

	}

	Shape(CPoint _pos, TYPE _type) : pos(_pos), type(_type)
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
	vector<Shape> shapes;
	COLORREF color;

	bool isReplay;

	// 작업입니다.
public:
	void DrawShape(TYPE _type, CPoint _pos, CDC _dc);

	// 재정의입니다.
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	CButton clearButton;
	CButton saveButton;
	CButton loadButton;
	CButton replayButton;
	CButton stopButton;
	CScrollBar scrollBar;

	// Replay 모드를 위한 변수
	int curIndex;
	CPoint curPos;
	CPoint nextPos;

	CPoint ReplayPos;

	float dx;
	float dy;

	bool isChangeToRect;
	float ratioOfRect;
	
	int count = 0;

	int selectIndex = 0;
	// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnClear();
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
	afx_msg void OnSave();
	afx_msg void OnUpdateSave(CCmdUI* pCmdUI);
	afx_msg void OnLoad();
	afx_msg void OnUpdateLoad(CCmdUI* pCmdUI);
	afx_msg void OnReplay();
	afx_msg void OnUpdateReplay(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

