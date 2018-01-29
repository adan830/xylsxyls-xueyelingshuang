#pragma once

/** ��ָ����
*/
#define SAFE(p,method) if(p != nullptr){method;}

/** ����������ɫ
*/
#define LABEL_TEXT_COLOR QColor(209, 209, 209)

/** �Ҳ�ؼ�������ɫ
*/
#define CONTROL_TEXT_COLOR QColor(233, 234, 237, 255)

/** �Ҳ�ؼ�����ʱ������ɫ
*/
#define CONTROL_DISABLED_TEXT_COLOR CONTROL_TEXT_COLOR

/** ��������������ɫ
*/
#define CREATE_GAME_COLOR QColor(183, 187, 204, 255)

/** �������䰴ť��̬��ɫ
*/
#define CREATE_ROOM_NORMAL_COLOR QColor("#53be1e")

/** �������䰴ť��ͣ��ɫ
*/
#define CREATE_ROOM_HOVER_COLOR QColor("#1da403")

/** �Ҳ�ؼ��߿���ɫ
*/
#define CONTROL_BORDER_COLOR QColor(0, 0, 0, 255 * 0.6)

/** �ؼ�������ɫ
*/
#define CONTROL_BACKGROUND_COLOR CONTROL_BORDER_COLOR

/** ����
*/
#define GAME_INFO_FONT_FACE CGeneralStyle::instance()->font().family()

/** ������̬��ɫ
*/
#define LIST_NORMAL_COLOR QColor("#15181f")

/** ������hover��ɫ
*/
#define LIST_HOVER_COLOR QColor("#4486ff")

enum
{
	/** ���崰�ڿ��
	*/
	GAME_INFO_WIDGET_WIDTH = 262,

	/** ����3����ť�ĸ߶�
	*/
	WIDGET_BUTTON_HEIGHT = 35,

	/** widget��ʼλ��
	*/
	WIDGET_ORIGIN = 11,

	/** ÿ����ť��Ӧwidget�Ŀ��
	*/
	WIDGET_WIDTH = 240,

	/** widget�߶�
	*/
	WIDGET_HEIGHT = 265,

	/** ÿ�������Ŀ��
	*/
	LABEL_WIDTH = 77,

	/** ÿ�������ĸ߶�
	*/
	LABEL_HEIGHT = 24,

	/** ��һ����������ʼ�߶�
	*/
	FIRST_LABEL_BEGIN_HEIGHT = 12,

	/** �������Ҳ�ؼ��ļ�����
	*/
	LABEL_SPACING = 10,

	/** �Ҳ�ؼ�������ʼλ��
	*/
	CONTROL_BEGIN_ORIGIN_X = LABEL_WIDTH + LABEL_SPACING,

	/** �Ҳ�ؼ�������ʼλ��
	*/
	CONTROL_BEGIN_ORIGIN_Y = FIRST_LABEL_BEGIN_HEIGHT,

	/** �Ҳ�ؼ����
	*/
	CONTROL_WIDTH = 138,

	/** �Ҳ�ؼ��߶�
	*/
	CONTROL_HEIGHT = LABEL_HEIGHT,

	/** �Ҳ�ؼ�Բ�ǰ뾶
	*/
	CONTROL_RADIUS = 2,

	/** ��������Բ�ǰ뾶
	*/
	CREATE_ROOM_RADIUS = 3,

	/** �ؼ�����߶�
	*/
	CONTROL_SPACING_HEIGHT = 9,

	/** �ؼ��ͼ���ܸ߶�
	*/
	CONTROL_ALL_SPACING = CONTROL_HEIGHT + CONTROL_SPACING_HEIGHT,

	/** ���水ť������ʼλ��
	*/
	CREATE_ROOM_ORIGIN_X = 17,

	/** ���水ť������ʼλ��
	*/
	CREATE_ROOM_ORIGIN_Y = 202,

	/** ���水ť���
	*/
	CREATE_ROOM_WIDTH = 208,

	/** ���水ť�߶�
	*/
	CREATE_ROOM_HEIGHT = 32,

	/** ��Ϸ������ҳ���
	*/
	GAME_SETTING_WEBVIEW_WIDTH = WIDGET_WIDTH,

	/** ��Ϸ������ҳ�߶�
	*/
	GAME_SETTING_WEBVIEW_HEIGHT = 170,

	/** ������Ϸ��ʼλ��
	*/
	CREATE_GAME_ORIGIN_X = 11,

	/** ��������������ʼ�߶�
	*/
	CREATE_GAME_ORIGIN_Y = 1,

	/** ���������������
	*/
	CREATE_GAME_WIDTH = 60,

	/** ������Ϸ�߶�
	*/
	CREATE_GAME_HEIGHT = WIDGET_BUTTON_HEIGHT - 6,

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
	EXIT_WIDTH = 13,

	/** �˳���ť�߶�
	*/
	EXIT_HEIGHT = EXIT_WIDTH,

	/** �˳���ť������ʼλ��
	*/
	EXIT_ORIGIN_X = GAME_INFO_WIDGET_WIDTH - EXIT_WIDTH - 11,

	/** �˳���ť������ʼλ��
	*/
	EXIT_ORIGIN_Y = 9,

	/** ��ť֮ǰ�ļ�����
	*/
	BUTTONS_SPACING = 6,

	/** ��ʼ��Ϸ��ť������ʼλ��
	*/
	START_GAME_ORIGIN_X = (WIDGET_WIDTH - START_GAME_WIDTH - EXIT_WIDTH - BUTTONS_SPACING) / 2,

	/** �����С
	*/
	GAME_INFO_FONT_SIZE = 12,

	/** �����������С
	*/
	LIST_FONT_SIZE = GAME_INFO_FONT_SIZE,

	/** �Ҳ�ؼ�����ƫ����
	*/
	CONTROL_TEXT_ORIGIN = 4,

	/** ��Ϸģʽ���������ƫ����
	*/
	GAME_MODE_TEXT_ORIGIN = 7,

	/** ������ڵ�߶�
	*/
	LIST_ITEM_HEIGHT = 24,

	/** ���������߶�
	*/
	LIST_MAX_HEIGHT = 145,

	/** ������ƫ����
	*/
	LIST_ORIGIN = 1,

	/** ������߿�ֶ�
	*/
	LIST_BORDER_WIDTH = 0,

	/** ������ڵ�߿�ֶ�
	*/
	LIST_ITEM_BORDER_WIDTH = 0,

	/** ������ͷ���
	*/
	DROP_DOWN_WIDTH = 17,

	/** ������ͷ�߶�
	*/
	DROP_DOWN_HEIGHT = 22,

	/** ������ͷ�������ϽǺ������
	*/
	DROP_DOWN_ORIGIN_X = 5,

	/** ������ͷ�������Ͻ��������
	*/
	DROP_DOWN_ORIGIN_Y = 1,

};