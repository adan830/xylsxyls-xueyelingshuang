#pragma once
#include <string>
#include <map>
#include <vector>
#include "Rect/RectAPI.h"
#include "CScreenMacro.h"

class CScreenAPI ColorCast
{
public:
	ColorCast();
	ColorCast(const std::string& strColorCast);

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	std::string RC;
	std::string GC;
	std::string BC;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
	std::string toString()const;
};

class CScreenAPI Color
{
public:
	Color();
	Color(const std::string& strColor);
	Color(const std::string& strRGB, const std::string& strRCGCBC);

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	std::string R;
	std::string G;
	std::string B;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
	ColorCast colorCast;
	std::string toString()const;
	std::string toReserveString()const;
};

class CScreenAPI CScreen
{
public:
	//?�����ֿ��ʹ���ֿ⣬�ֿ��ź��ֿ�·��������ʹ�õ��ֿ���
	static bool initDict(const std::map<int, std::string>& mapDict, int use);
	//?��Ļ�����ͼΪBMP
	static bool SaveBmp(const xyls::Rect& rect, const std::string& path);
	//?��Ļ�����ͼΪGIF�������������ʱ�䣬��λ���Ǻ��룬ʵ���Ͼ��ǰѶ���ͼƬ������һ��GIF������
	static bool SaveGif(const xyls::Rect& rect, int delay, int time, const std::string& path);
	//?��Ļ�����ͼΪJPG��ѹ������1-100��1Ϊ���ѹ���̶�
	static bool SaveJpg(const xyls::Rect& rect, int quality, const std::string& path);
	//?��Ļ�����ͼΪPNG
	static bool SavePng(const xyls::Rect& rect, const std::string& path);
	//?�ȽϾ���������ɫ����ɫ�������10�������ƶ�0.1-1.0
	static bool ComparePointColor(const xyls::Point& point, const Color& color, double sim = 1.0);
	static bool ComparePointColor(const xyls::Point& point, const std::vector<Color>& color, double sim = 1.0);
	//?��ָ�������ڲ���ָ����ɫ���ҵ�����x��yֵ
	//?dir��0���������£�1���������ϣ�2���������£�3���������ϣ�4���������⣬5���������ң�6����������7���������ң�8����������
	static bool FindColor(const xyls::Rect& rect, const Color& color, int& x, int& y, double sim = 1.0, int dir = 0);
	static bool FindColor(const xyls::Rect& rect, const std::vector<Color>& vecColor, int& x, int& y, double sim = 1.0, int dir = 0);
	//?��⵱ǰ�����Ƿ��б���ͼƬ��ͼƬ��ʽΪbmp��ͼƬ��������4������ɫһ���Ļ����ͼƬĬ�ϴ���Ϊ͸��ɫ
	//?dir��0���������£�1���������ϣ�2���������£�3����������
	static bool FindPic(const xyls::Rect& rect, const std::string& picPath, int& x, int& y, const ColorCast& colorCast = std::string("000000"), double sim = 1.0, int dir = 0);
	static bool FindPic(const xyls::Rect& rect, const std::vector<std::string>& vecPicPath, int& x, int& y, const ColorCast& colorCast = std::string("000000"), double sim = 1.0, int dir = 0);
	//?��ȡͼƬ��С��ʹ��GetWidth��GetHeight����ȡ����
	static xyls::Rect GetPicSize(const std::string& picPath);
	//?ת��ͼƬ��ʽ
	static bool ChangeToBmp(const std::string& picPathDst, const std::string& picPathSrc);
	//?����ͼƬ·�����������·��
	static std::vector<std::string> MatchPicName(const std::string& picPath);
	//?��⵱ǰ�����Ƿ������֣����ƶȣ����������x��y�з�������
	static bool FindStr(const xyls::Rect& rect, const std::string& str, const Color& color, int& x, int& y, double sim = 1.0);
};