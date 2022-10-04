
// ChildView.h: CChildView 클래스의 인터페이스
//

#include <vector>
using std::vector;

#pragma once
// CChildView 창

// 질문 사항 혹은 궁금한 사항
// 1. 사각형과 원을 그리는 기능이 동시에 실행되지 않게끔 조절?	
// 2. 배열 대신 vector 컨테이너를 사용해도 되는가?

// 처리해야 하는 사항
// 1. 다각형 그리기
// 2. 더블 버퍼링


// 도형 모양을 열거형으로 정리
enum SHAPE_TYPE
{
	RECTANGLE = 0,
	ELLIPSE,
	POLYGON,
};

enum PEN_TYPE
{
	RED = 0,
	BLUE,
	GREEN,
};

enum BRUSH_TYPE
{
	SINGLE = 0,
	OBITMAP,
};

struct Shape
{
	// 도형의 위치값을 지정 
	CPoint ltPos;	// 좌상단
	CPoint rbPos;	// 우하단
	
	SHAPE_TYPE type;	// 도형의 타입
	Shape() :
		ltPos(CPoint(0,0)),
		rbPos(CPoint(0, 0))
	{

	}
	Shape(CPoint _ltPos, CPoint _rbPos, SHAPE_TYPE _type)
	{
		ltPos = _ltPos;
		rbPos = _rbPos;
		type = _type;
	}
};

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:


private:
	vector<Shape*> shapes;

	Shape tempShape;

	bool isLMouseDown;
	bool isRMouseDown;
	bool isMMouseDown;

	HINSTANCE Instance;
private:
	void setRbPos(CPoint point);
	void setLtPos(CPoint point);
	
	void addObject(SHAPE_TYPE type);

	void setDrawingTool(HDC dc, PEN_TYPE pType, BRUSH_TYPE bType);
	void setPen(HDC dc, PEN_TYPE type);
	void setBrush(HDC dc, BRUSH_TYPE type);

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
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};

