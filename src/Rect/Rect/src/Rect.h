#pragma once
#include "RectMacro.h"
#include "Point/PointAPI.h"

#ifdef _WIN32
#include <windows.h>
#endif

class RectAPI Rect{
public:
	int left;
	int top;
	int right;
	int bottom;
	Rect();

#ifdef _WIN32
    Rect(const RECT& rect);
#endif

	Rect(int left, int top, int right, int bottom);
	Rect(const Point& point);
	void SetRect(int left, int top, int right, int bottom);
	void SetRect(Point point);
	int GetWidth()const;
	int GetHeight()const;
	bool isPoint()const;
	bool isLine()const;

	//? ������Ӧ���뱳��bkRect��
	//? param [in] bkRect ��������
	//? return ������Ӧ֮��ľ��Σ������С��Ŵ���Ӧ
	Rect Adapt(const Rect& bkRect);

	//? ���з��뱳��bkRect��
	//? param [in] bkRect ��������
	//? return ����֮��ľ��Σ������С����Ŵ�
	Rect SetIn(const Rect& bkRect);

	//? ��ȡ�ص�����
	//? param [in] bkRect ��������
	//? return �����ص����ֵľ���
	Rect Over(const Rect& bkRect);

	//? ��ȡtan�ǣ���/��
	//? ����tan��
	double Gettan()const;

#ifdef _WIN32
    operator RECT();
#endif
};