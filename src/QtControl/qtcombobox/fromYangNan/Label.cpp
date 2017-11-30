#include "Label.h"

Label::Label(QWidget* parent) :
ControlBase(parent),
m_leftOrigin(0),
m_fontSize(12)
{
	ControlBase::init(L"QLabel", L"");
}

Label::~Label()
{

}

void Label::setFontFace(const QString& fontName, bool rePaint)
{
	m_fontName = fontName.toStdWString();
	ControlFont::setFontFace(fontName, rePaint);
}

void Label::setFontSize(int32_t fontSize, bool rePaint)
{
	m_fontSize = fontSize;
	ControlFont::setFontSize(fontSize, rePaint);
}

void Label::setTextOrigin(int32_t origin, bool rePaint)
{
	m_leftOrigin = origin;
	ControlBase::setPxValue(L"padding-left", origin, false, rePaint);
}

void Label::setText(const QString& str)
{
	m_str = str.toStdWString();
	QFont font(QString::fromStdWString(m_fontName));
	font.setPixelSize(m_fontSize);
	QFontMetrics fontMetrics(font);
	//��ȡ֮ǰ���õ��ַ��������ش�С
	int32_t fontSize = fontMetrics.width(str);
	QString strShow = str;
	int32_t wid = width();
	if (fontSize > width() - m_leftOrigin)
	{
		//����һ������ʡ�Ժŵ��ַ���
		strShow = fontMetrics.elidedText(str, Qt::ElideRight, width() - m_leftOrigin);
	}
	QLabel::setText(strShow);
}

QString Label::text()
{
	return QString::fromStdWString(m_str);
}