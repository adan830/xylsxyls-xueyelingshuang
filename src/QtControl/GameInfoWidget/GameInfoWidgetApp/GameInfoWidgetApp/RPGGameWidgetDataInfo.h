#pragma once

/** ��ָ����
*/
#define SAFE(p,method) if(p != nullptr){method;}

/** ����������ɫ
*/
#define LABEL_TEXT_COLOR QColor("#d1d1d1")

/** �Ҳ�ؼ��߿���ɫ
*/
#define CONTROL_BORDER_COLOR QColor(0, 0, 0, 255 * 0.6)

/** �Ҳ�ؼ�������ɫ
*/
#define CONTROL_TEXT_COLOR QColor(255, 255, 255, 255)

/** �Ҳ�ؼ�����ʱ������ɫ
*/
#define CONTROL_DISABLED_TEXT_COLOR QColor(82, 126, 185, 255)

/** ���水ť�߿���ɫ
*/
#define SAVE_BORDER_COLOR QColor(84, 97, 138, 255)

/** ����
*/
#define GAME_INFO_FONT_FACE QString::fromStdWString(L"΢���ź�")

/** �ؼ�������ɫ
*/
#define CONTROL_BACKGROUND_COLOR CONTROL_BORDER_COLOR

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
	GAME_INFO_WIDGET_WIDTH = 240,

	/** ����3����ť�ĸ߶�
	*/
	WIDGET_BUTTON_HEIGHT = 29,

	/** ��Ϸ����widget��ʼƫ����
	*/
	WIDGET_ORIGIN = 1,

	/** ÿ����ť��Ӧwidget�Ŀ��
	*/
	WIDGET_WIDTH = GAME_INFO_WIDGET_WIDTH,

	/** ÿ�������ĺ�����ʼλ��
	*/
	LABEL_ORIGIN = 15,

	/** ÿ�������Ŀ��
	*/
	LABEL_WIDTH = 77,

	/** ÿ�������ĸ߶�
	*/
	LABEL_HEIGHT = 22,

	/** ��һ����������ʼ�߶�
	*/
	FIRST_LABEL_BEGIN_HEIGHT = 14,

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
	CONTROL_HEIGHT = LABEL_HEIGHT + 2,

	/** �Ҳ�ؼ�Բ�ǰ뾶
	*/
	CONTROL_RADIUS = 3,

	/** �ؼ�����߶�
	*/
	CONTROL_SPACING_HEIGHT = 10,

	/** �ؼ��ͼ���ܸ߶�
	*/
	CONTROL_ALL_SPACING = CONTROL_HEIGHT + CONTROL_SPACING_HEIGHT,

	/** ��������λ������ʼλ��
	*/
	JUDGE_ORIGIN_X = CONTROL_BEGIN_ORIGIN_X,

	/** ���水ť������ʼλ��
	*/
	SAVE_ORIGIN_Y = 220,

	/** ���水ť���
	*/
	SAVE_WIDTH = 208,

	/** ���水ť�߶�
	*/
	SAVE_HEIGHT = 32,

	/** ���水ť������ʼλ��
	*/
	SAVE_ORIGIN_X = (GAME_INFO_WIDGET_WIDTH - SAVE_WIDTH) / 2,

	/** �����߶�
	*/
	LAB_HEIGHT = 10,

	/** ��Ϸ������ҳ���
	*/
	GAME_SETTING_WEBVIEW_WIDTH = WIDGET_WIDTH,

	/** ��Ϸ������ҳ�߶�
	*/
	GAME_SETTING_WEBVIEW_HEIGHT = 180,

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