#pragma once
#include "ColorMacro.h"
#include <string>

namespace xyls
{

class ColorAPI Color
{
public:
	/** ���캯��
	@param [in] r ��ɫrֵ
	@param [in] g ��ɫgֵ
	@param [in] b ��ɫbֵ
	*/
	Color(unsigned char r, unsigned char g, unsigned char b);

	/** ���캯��
	@param [in] r ��ɫrֵ
	@param [in] g ��ɫgֵ
	@param [in] b ��ɫbֵ
	@param [in] r ƫɫrֵ
	@param [in] g ƫɫgֵ
	@param [in] b ƫɫbֵ
	*/
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char rc, unsigned char gc, unsigned char bc);

public:
	/** �����ɫ�ַ�������ĸСд
	@return ������ɫ�ַ�������ĸСд
	*/
	std::string toString() const;

	/** ���������ɫ�ַ�������ĸСд
	@return ���ط�����ɫ�ַ�������ĸСд
	*/
	std::string toReserveString() const;

	/** �����ɫ�ַ�����ƫɫ����ĸСд
	@return ������ɫ�ַ�����ƫɫ����ĸСд
	*/
	std::string toCastString() const;

	/** ���������ɫ�ַ�����ƫɫ����ĸСд
	@return ���ط�����ɫ�ַ�����ƫɫ����ĸСд
	*/
	std::string toReserveCastString() const;

private:
	int m_r;
	int m_g;
	int m_b;
	int m_rc;
	int m_gc;
	int m_bc;
};

}
