#pragma once
#include <string>
using namespace std;
#include "CCharsetMacro.h"

class CCharsetAPI CCharset{
public:
	/***********************************************************************************
	* name       : StrFormat
	* description: ���ݴ���ĸ�ʽ�����ַ����ĸ�ʽ��;�ýӿ�ֻ�ܸ�ʽ���󳤶�Ϊ512���ַ���
	* input      : szFormat:�ַ����ĸ�ʽ; ...:�ɱ����;
	* output     : NA
	* return     : ת������ַ���
	* remark     : NA
	***********************************************************************************/
    static std::string StrFormat (  const char* szFormat, ... );

	/***********************************************************************************
	* name       : IntToStr
	* description: ������ת��Ϊ�ַ���
	* input      : nValue:Ҫת����������ֵ; bHex:�Ƿ���ʮ������������
	* output     : NA
	* return     : ת������ַ���
	* remark     : NA
	***********************************************************************************/
    static std::string IntToStr ( int nValue, bool bHex = false );

	/***********************************************************************************
	* name       : StrToInt
	* description: ������ת��Ϊ�ַ���
	* input      : strSrc:Ҫת�����ַ���; bHex:�Ƿ���ʮ������������
	* output     : NA
	* return     : ת�����������
	* remark     : NA
	***********************************************************************************/
	static int StrToInt ( const std::string& strSrc, bool bHex = false );

	/***********************************************************************************
	* name       : CharToHex
	* description: ���ַ�ת��Ϊ16���Ʊ���
	* input      : szChar:Ҫת�����ַ�;
	* output     : NA
	* return     : ���ص�ʮ�����Ʊ���
	* remark     : NA
	***********************************************************************************/
	static int CharToHex( const char szChar );

	/***********************************************************************************
	* name       : StrToHex
	* description: ��һ���ַ���ת��Ϊʮ�������ַ�������
	* input      : strSrc:Ҫת�����ַ���;
	* output     : NA
	* return     : ���ص�ʮ�����Ʊ�����ַ���
	* remark     : NA
	***********************************************************************************/
	static std::string StrToHex ( const std::string& strSrc );

	/***********************************************************************************
	* name       : HexToStr
	* description: ��ʮ�����Ƶ��ַ���ת��Ϊһ���ַ���
	* input      : strSrc:Ҫת�����ַ���;
	* output     : NA
	* return     : ת������ַ���
	* remark     : NA
	***********************************************************************************/
	static std::string HexToStr ( const std::string& strSrc );

	/***********************************************************************************
	* name       : Utf8ToUnicode
	* description: �ַ���ת��: UTF8 - Unicode	
	* input      : strSrc:Ҫת����Utf8�ַ���������ַ���;
	* output     : NA
	* return     : ת�����Unicode�ַ���������ַ���
	* remark     : NA
	***********************************************************************************/
	static std::wstring Utf8ToUnicode ( const std::string& strSrc );

	/***********************************************************************************
	* name       : UnicodeToUtf8
	* description: �ַ���ת��: Unicode - UTF8	
	* input      : wstrSrc:Ҫת����Unicode�ַ���������ַ���;
	* output     : NA
	* return     : ת�����UTF8�ַ���������ַ���
	* remark     : NA
	***********************************************************************************/
	static std::string UnicodeToUtf8 ( const std::wstring& wstrSrc );

	/***********************************************************************************
	* name       : Utf8ToAnsi
	* description: �ַ���ת��: UTF8 - Ansi
	* input      : strSrc:Ҫת����UTF8�ַ���������ַ���;
	* output     : NA
	* return     : ת�����Ansi�ַ���������ַ���
	* remark     : NA
	***********************************************************************************/
	static std::string Utf8ToAnsi( const std::string& strSrc );

	/***********************************************************************************
	* name       : AnsiToUtf8
	* description: �ַ���ת��: Ansi - UTF8
	* input      : strSrc:Ҫת����Ansi�ַ���������ַ���;
	* output     : NA
	* return     : ת�����UTF8�ַ���������ַ���
	* remark     : NA
	***********************************************************************************/
	static std::string AnsiToUtf8 ( const std::string& strSrc );

	/***********************************************************************************
	* name       : AnsiToUnicode
	* description: �ַ���ת��: Ansi - Unicode
	* input      : strSrc:Ҫת����Ansi�ַ���������ַ���;
	* output     : NA
	* return     : ת�����Unicode�ַ���������ַ���
	* remark     : NA
	***********************************************************************************/
	static std::wstring AnsiToUnicode (const std::string& strSrc );

	/***********************************************************************************
	* name       : UnicodeToAnsi
	* description: �ַ���ת��: Unicode - Ansi
	* input      : strSrc:Ҫת����Unicode�ַ���������ַ���;
	* output     : NA
	* return     : ת�����Ansi�ַ���������ַ���
	* remark     : NA
	***********************************************************************************/
	static std::string UnicodeToAnsi ( const std::wstring& wstrSrc );

	///***********************************************************************************
	//* name       : Utf8ToBSTR
	//* description: �ַ���ת��: UTF8 - BSTR
	//* input      : strSrc:Ҫת����UTF8�ַ���������ַ���;
	//* output     : NA
	//* return     : ת����ĵ�BSTR�ַ���
	//* remark     : NA
	//***********************************************************************************/
	//static BSTR Utf8ToBSTR( const std::string& strSrc );

	///***********************************************************************************
	//* name       : BSTRToUtf8
	//* description: �ַ���ת��: BSTR - UTF8
	//* input      : bstrSrc:Ҫת����BSTR�ַ���;
	//* output     : NA
	//* return     : ת�����UTF8�ַ���������ַ���
	//* remark     : NA
	//***********************************************************************************/
	//static std::string BSTRToUtf8 ( const BSTR& bstrSrc );
};