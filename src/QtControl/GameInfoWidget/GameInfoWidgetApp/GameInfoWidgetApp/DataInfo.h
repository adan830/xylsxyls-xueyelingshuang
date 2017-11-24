#pragma once

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

enum
{
	/** ���崰�ڿ��
	*/
	GAME_INFO_WIDGET_WIDTH = 254,

	/** ���崰�ڸ߶�
	*/
	GAME_INFO_WIDGET_HEIGHT = 681,

	/** ����3����ť�ĸ߶�
	*/
	WIDGET_BUTTON_HEIGHT = 29,

	/** ÿ����ť��Ӧwidget�Ŀ��
	*/
	WIDGET_WIDTH = GAME_INFO_WIDGET_WIDTH,

	/** ÿ����ť��Ӧwidget�ĸ߶�
	*/
	WIDGET_HEIGHT = 550,

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

	/** ��Ϸ������ҳ��ʼ�߶�
	*/
	GAME_SETTING_WEBVIEW_ORIGIN = WIDGET_HEIGHT - GAME_SETTING_WEBVIEW_HEIGHT,

	/** ������Ѱ�ť��ʼ�߶�
	*/
	INVITE_FRIEND_ORIGIN = WIDGET_BUTTON_HEIGHT + WIDGET_HEIGHT,

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

	/** ��ʼ��Ϸ��ť������ʼλ��
	*/
	START_GAME_ORIGIN_Y = GAME_INFO_WIDGET_HEIGHT - (GAME_INFO_WIDGET_HEIGHT - WIDGET_HEIGHT - WIDGET_BUTTON_HEIGHT - INVITE_FRIEND_HEIGHT - START_GAME_HEIGHT) / 2 - START_GAME_HEIGHT,

	/** �˳���ť������ʼλ��
	*/
	EXIT_ORIGIN_X = START_GAME_ORIGIN_X + BUTTONS_SPACING + START_GAME_WIDTH,

	/** �˳���ť������ʼλ��
	*/
	EXIT_ORIGIN_Y = START_GAME_ORIGIN_Y,

	/** �����С
	*/
	GAME_INFO_FONT_SIZE = 14,

	/** �Ҳ�ؼ�����ƫ����
	*/
	CONTROL_TEXT_ORIGIN = 4,

	/** ��Ϸģʽ���������ƫ����
	*/
	GAME_MODE_TEXT_ORIGIN = 7,
};