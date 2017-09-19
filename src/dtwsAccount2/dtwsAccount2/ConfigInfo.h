#pragma once
#include "CStorage/CStorageAPI.h"
#include <stdint.h>

#define GetConfig(num, T) ConfigInfo::Instance()[(num)].toValue<T>()

class ConfigInfo : public CStorage
{
private:
	ConfigInfo();
	~ConfigInfo();
public:
	static ConfigInfo& Instance();

private:
	xyls::Rect GetRectForNine(int32_t id);

private:
	/** ��Ļ��
	*/
	int32_t m_screenWidth = 0;

	/** ��Ļ��
	*/
	int32_t m_screenHeight = 0;
};

enum
{
	/** �Ź���
	*   1 2 3
	*   4 5 6
	*   7 8 9
	*/
	RECT_NINE_1,
	RECT_NINE_2,
	RECT_NINE_3,
	RECT_NINE_4,
	RECT_NINE_5,
	RECT_NINE_6,
	RECT_NINE_7,
	RECT_NINE_8,
	RECT_NINE_9,

};