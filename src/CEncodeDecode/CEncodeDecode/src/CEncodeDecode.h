#pragma once
#include <string>
using namespace std;
#include "CEncodeDecodeMacro.h"

class CEncodeDecodeAPI CEncodeDecode{
public:
	//���ؾ���MD5ת������ַ���
	static string MD5Decode(string src);

	//���ܽ��ܵ�key����һ�������ؼ��ܽ��ܺ���ַ���
	static string AESEncode(string key, string src);
	static string AESDecode(string key, string src);
};