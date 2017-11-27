#pragma once

/** ��ָ����
*/
#define SAFE(p,method) if(p != nullptr){method;}

/** ����������ɫ
*/
#define LABEL_TEXT_COLOR QColor(145, 169, 226)

/** �Ҳ�ؼ��߿���ɫ
*/
#define CONTROL_BORDER_COLOR QColor(67, 81, 117, 255)

/** �Ҳ�ؼ�������ɫ
*/
#define CONTROL_TEXT_COLOR QColor(233, 234, 237, 255)

/** ���水ť�߿���ɫ
*/
#define SAVE_BORDER_COLOR QColor(84, 97, 138, 255)

/** ����
*/
#define GAME_INFO_FONT_FACE QString::fromStdWString(L"΢���ź�")

/** �ؼ�������ɫ
*/
#define CONTROL_BACKGROUND_COLOR QColor(39, 50, 83, 255)

/** ������hover��ɫ
*/
#define LIST_HOVER_COLOR QColor(80, 98, 146, 255)

enum
{
	/** ���崰�ڿ��
	*/
	GAME_INFO_WIDGET_WIDTH = 254,

	/** ����3����ť�ĸ߶�
	*/
	WIDGET_BUTTON_HEIGHT = 29,

	/** ÿ����ť��Ӧwidget�Ŀ��
	*/
	WIDGET_WIDTH = GAME_INFO_WIDGET_WIDTH,

	/** ÿ�������Ŀ��
	*/
	LABEL_WIDTH = 88,

	/** ÿ�������ĸ߶�
	*/
	LABEL_HEIGHT = 22,

	/** ��һ����������ʼ�߶�
	*/
	FIRST_LABEL_BEGIN_HEIGHT = 15,

	/** �������Ҳ�ؼ��ļ�����
	*/
	LABEL_SPACING = 5,

	/** �Ҳ�ؼ�������ʼλ��
	*/
	CONTROL_BEGIN_ORIGIN_X = LABEL_WIDTH + LABEL_SPACING,

	/** �Ҳ�ؼ�������ʼλ��
	*/
	CONTROL_BEGIN_ORIGIN_Y = FIRST_LABEL_BEGIN_HEIGHT,

	/** �Ҳ�ؼ����
	*/
	CONTROL_WIDTH = 147,

	/** �Ҳ�ؼ��߶�
	*/
	CONTROL_HEIGHT = LABEL_HEIGHT,

	/** �Ҳ�ؼ�Բ�ǰ뾶
	*/
	CONTROL_RADIUS = 5,

	/** �ؼ�����߶�
	*/
	CONTROL_SPACING_HEIGHT = 12,

	/** �ؼ��ͼ���ܸ߶�
	*/
	CONTROL_ALL_SPACING = CONTROL_HEIGHT + CONTROL_SPACING_HEIGHT,

	/** ��������λ������ʼλ��
	*/
	JUDGE_ORIGIN_X = 16,

	/** ���水ť������ʼλ��
	*/
	SAVE_ORIGIN_X = 77,

	/** ���水ť������ʼλ��
	*/
	SAVE_ORIGIN_Y = 319,

	/** ���水ť���
	*/
	SAVE_WIDTH = 100,

	/** ���水ť�߶�
	*/
	SAVE_HEIGHT = 28,

	/** ��Ϸ������ҳ���
	*/
	GAME_SETTING_WEBVIEW_WIDTH = WIDGET_WIDTH,

	/** ��Ϸ������ҳ�߶�
	*/
	GAME_SETTING_WEBVIEW_HEIGHT = 170,

	

	/** ������Ѱ�ť���
	*/
	INVITE_FRIEND_WIDTH = WIDGET_WIDTH,

	/** ������Ѱ�ť�߶�
	*/
	INVITE_FRIEND_HEIGHT = 34,

	/** ��ʼ��Ϸ��ť���
	*/
	START_GAME_WIDTH = 164,

	/** ��ʼ��Ϸ��ť�߶�
	*/
	START_GAME_HEIGHT = 38,

	/** �˳���ť���
	*/
	EXIT_WIDTH = 58,

	/** �˳���ť�߶�
	*/
	EXIT_HEIGHT = START_GAME_HEIGHT,

	/** ��ť֮ǰ�ļ�����
	*/
	BUTTONS_SPACING = 6,

	/** ��ʼ��Ϸ��ť������ʼλ��
	*/
	START_GAME_ORIGIN_X = (WIDGET_WIDTH - START_GAME_WIDTH - EXIT_WIDTH - BUTTONS_SPACING) / 2,

	

	/** �˳���ť������ʼλ��
	*/
	EXIT_ORIGIN_X = START_GAME_ORIGIN_X + BUTTONS_SPACING + START_GAME_WIDTH,

	/** �����С
	*/
	GAME_INFO_FONT_SIZE = 13,

	/** �����������С
	*/
	LIST_FONT_SIZE = GAME_INFO_FONT_SIZE - 1,

	/** �Ҳ�ؼ�����ƫ����
	*/
	CONTROL_TEXT_ORIGIN = 4,

	/** ��Ϸģʽ���������ƫ����
	*/
	GAME_MODE_TEXT_ORIGIN = 7,

	/** ������ڵ�߶�
	*/
	LIST_ITEM_HEIGHT = 17,

	/** ���������߶�
	*/
	LIST_MAX_HEIGHT = 36,

	/** ������ƫ����
	*/
	LIST_ORIGIN = 2,

	/** ������߿�ֶ�
	*/
	LIST_BORDER_WIDTH = 1,

	/** ������ڵ�߿�ֶ�
	*/
	LIST_ITEM_BORDER_WIDTH = 0,

	/** ������ͷ���
	*/
	DROP_DOWN_WIDTH = 10,

	/** ������ͷ�߶�
	*/
	DROP_DOWN_HEIGHT = 5,

	/** ������ͷ�������ϽǺ������
	*/
	DROP_DOWN_ORIGIN_X = 7,

	/** ������ͷ�������Ͻ��������
	*/
	DROP_DOWN_ORIGIN_Y = 5,

};