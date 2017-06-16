#pragma once
#include "MulRectMacro.h"
#include "Point/PointAPI.h"

#ifdef _WIN32
#include <windows.h>
#endif

class MulRectAPI MulRect{
public:
	int left;
	int top;
	int right;
	int bottom;
	MulRect();

#ifdef _WIN32
    MulRect(const RECT& rect);
#endif

	MulRect(int left, int top, int right, int bottom);
	MulRect(const Point& point);
	void SetMulRect(int left, int top, int right, int bottom);
	void SetMulRect(Point point);
	int GetWidth()const;
	int GetHeight()const;
	bool isPoint()const;
	bool isLine()const;

    //?�Ƿ���ˮƽ��
    bool isHorizontalLine()const;
    //?�Ƿ��Ǵ�ֱ��
    bool isVerticalLine()const;

	//? ������Ӧ���뱳��bkMulRect��
	//? param [in] bkMulRect ��������
	//? return ������Ӧ֮��ľ��Σ������С��Ŵ���Ӧ
	MulRect Adapt(const MulRect& bkMulRect);

	//? ���з��뱳��bkMulRect��
	//? param [in] bkMulRect ��������
	//? return ����֮��ľ��Σ������С����Ŵ�
	MulRect SetIn(const MulRect& bkMulRect);

	//? ��ȡ�ص�����
	//? param [in] bkMulRect ��������
	//? return �����ص����ֵľ���
	MulRect Over(const MulRect& bkMulRect);

	//? ��ȡtan�ǣ���/��
	//? ����tan��
	double Gettan()const;

#ifdef _WIN32
    operator RECT()const;
#endif
};