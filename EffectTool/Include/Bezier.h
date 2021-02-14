#pragma once
#ifndef __BEZIER_H__
#define __BEZIER_H__

#include "Nalmak_Include.h"

// Cubic Bezier Curve (3��)
// 4���� ���� �ְ� Bezier ��� �����, 
// �� �� GetBezierPoint�Լ��� ���� ��4���� ������� ����� x����(t)�� ���� �ش��ϴ� y���� ���� ( t  = [0 ~ 1] )
// SetPoint�Լ��� ���� ���������� �������� �̷���� ��� ���� �� ����
class NALMAK_DLL Bezier
{
	/////////////////////////////////
	//                             // 
	//    (0,1) *-------* (1,1)	   //
	//          |       |		   //
	//          |	    |		   //
	//          |       |		   //
	//    (0,0) *-------* (1,0)	   //
	//							   //
	/////////////////////////////////
public:
	Bezier();
	explicit Bezier(const float& _x1, const float& _y1, const float& _x2, const float& _y2, const float& _x3, const float& _y3, const float& _x4, const float& _y4);
	explicit Bezier(const Vector2& _p1, const Vector2& _p2, const Vector2& _p3, const Vector2& _p4);
	~Bezier();
public:
	void SetInterpolationType(INTERPOLATION_TYPE _type);
	Vector2 GetPoint(float _t) const;
	float GetYvalue(float _t) const;

private:
	Vector2 m_bezierPoints[4]; // ������ � �� (����)
};

#endif // !__BEZIER_H__
