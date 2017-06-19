#pragma once
#include <string>
#include <map>
#include <vector>
#include "MulRect/MulRectAPI.h"
#include "CScreenMacro.h"
using namespace std;

class CScreenAPI ColorCast{
public:
	ColorCast();
	ColorCast(const string& strColorCast);

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string RC;
	string GC;
	string BC;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
	string toString()const;
};

class CScreenAPI Color{
public:
	Color();
	Color(const string& strColor);
	Color(const string& strRGB, const string& strRCGCBC);

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	string R;
	string G;
	string B;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	
	ColorCast colorCast;
	string toString()const;
	string toReserveString()const;
};

class CScreenAPI CScreen{
public:
	//?�����ֿ��ʹ���ֿ⣬�ֿ��ź��ֿ�·��������ʹ�õ��ֿ���
	static bool initDict(const map<int, string>& mapDict, int use);
	//?��Ļ�����ͼΪBMP
	static bool SaveBmp(const MulRect& MulRect, const string& path);
	//?��Ļ�����ͼΪGIF�������������ʱ�䣬��λ���Ǻ��룬ʵ���Ͼ��ǰѶ���ͼƬ������һ��GIF������
	static bool SaveGif(const MulRect& MulRect, int delay, int time, const string& path);
	//?��Ļ�����ͼΪJPG��ѹ������1-100��1Ϊ���ѹ���̶�
	static bool SaveJpg(const MulRect& MulRect, int quality, const string& path);
	//?��Ļ�����ͼΪPNG
	static bool SavePng(const MulRect& MulRect, const string& path);
	//?�ȽϾ���������ɫ����ɫ�������10�������ƶ�0.1-1.0
	static bool ComparePointColor(const MulPoint& point, const Color& color, double sim = 1.0);
	static bool ComparePointColor(const MulPoint& point, const vector<Color>& color, double sim = 1.0);
	//?��ָ�������ڲ���ָ����ɫ���ҵ�����x��yֵ
	//?dir��0���������£�1���������ϣ�2���������£�3���������ϣ�4���������⣬5���������ң�6����������7���������ң�8����������
	static bool FindColor(const MulRect& MulRect, const Color& color, int& x, int& y, double sim = 1.0, int dir = 0);
	static bool FindColor(const MulRect& MulRect, const vector<Color>& vecColor, int& x, int& y, double sim = 1.0, int dir = 0);
	//?��⵱ǰ�����Ƿ��б���ͼƬ��ͼƬ��ʽΪbmp��ͼƬ��������4������ɫһ���Ļ����ͼƬĬ�ϴ���Ϊ͸��ɫ
	//?dir��0���������£�1���������ϣ�2���������£�3����������
	static bool FindPic(const MulRect& MulRect, const string& picPath, int& x, int& y, const ColorCast& colorCast = string("000000"), double sim = 1.0, int dir = 0);
	static bool FindPic(const MulRect& MulRect, const vector<string>& vecPicPath, int& x, int& y, const ColorCast& colorCast = string("000000"), double sim = 1.0, int dir = 0);
	//?��ȡͼƬ��С��ʹ��GetWidth��GetHeight����ȡ����
	static MulRect GetPicSize(const string& picPath);
	//?ת��ͼƬ��ʽ
	static bool ChangeToBmp(const string& picPathDst, const string& picPathSrc);
	//?����ͼƬ·�����������·��
	static vector<string> MatchPicName(const string& picPath);
	//?��⵱ǰ�����Ƿ������֣����ƶȣ����������x��y�з�������
	static bool FindStr(const MulRect& MulRect, const string& str, const Color& color, int& x, int& y, double sim = 1.0);
};