#pragma once
#include <string>
using namespace std;
#include "CEncodeDecodeMacro.h"

class CEncodeDecodeAPI CEncodeDecode{
public:
	//���ؾ���MD5ת������ַ���
	string MD5Decode(string src);

	//���ܽ��ܵ�key����һ�������ؼ��ܽ��ܺ���ַ���
	string AESEncode(string key,string src);
	string AESDecode(string key,string src);
};