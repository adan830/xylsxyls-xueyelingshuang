#pragma once
#include <windows.h>
#include <vector>
#include "Rect/RectAPI.h"
#include "CMouseMacro.h"
using namespace std;

class CMouseAPI CMouse{
	//? sleepTime 0��ʾ���̵�� - 1��ʾ���ʱ�䣬Ĭ���������λ�Ǻ���
public:
	//?����������
	static bool LeftDown();
	//?��������Ҽ�
	static bool RightDown();
	//?��������м�
	//?����������
	static bool LeftUp();
	//?��������Ҽ�
	static bool RightUp();
	//?��������м�
	//?��������������Χ100-300����
	static bool LeftClick(int sleepTime = -1);
	//?�����Ҽ�
	static bool RightClick(int sleepTime = -1);
	//?�����м�
	//?˫����������ʱ�䷶ΧΪ100 - 300����
	static bool LeftDoubleClick(int sleepTime = -1);
	//?˫���Ҽ�
	static bool RightDoubleClick(int sleepTime = -1);
	//?˫���м�
	//?������
	static bool LeftManyClick(int times, int sleepTime = -1);
	//?����Ҽ�
	static bool RightManyClick(int times, int sleepTime = -1);
	//?����м�
	//?�ƶ����ӵ㵽�㣬�������꣬���ʱ�䣬�й켣����ΧΪ50 - 1000�����е�һ�֣�����г��룬ʵ�����ʱ�����Ԥ�����ʱ��
	static bool MoveAbsolute(xyls::Rect rect, int sleepTime = -1);
	//?�ƶ����ӵ㵽�㣬������꣬���ʱ�䣬�й켣
	static bool MoveOpposite(xyls::Rect rect, int sleepTime = -1);
	//?����м����¹����������м�һ��
	static bool MidWheelDown();
	//?����м����Ϲ���
	static bool MidWheelUp();
	//?��ȡ��굱ǰλ�ã���������
	static xyls::Point GetCurrentPos();
};