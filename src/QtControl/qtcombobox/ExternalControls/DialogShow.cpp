#include "DialogShow.h"
#include "Label.h"
#include <QPainter>
#include <QMouseEvent>
#include "../COriginalButton.h"
#include <QWindow>
#include "CStringManager.h"
#include "D:\\SendToMessageTest.h"

DialogShow::DialogShow() :
m_cancelEscAltF4(false),
m_bPressed(false),
m_highLight(false)
{
	init();
}

void DialogShow::init()
{
	resize(340, 165);
	m_exit = addButton("", QRect(width() - 3 - 30, 3, 30, 30), 0);
	m_exit->setBkgMargins(0, 0);
	m_exit->setBorderRadius(0);
	m_exit->setBkgImage("E:/newClient/11UI/Resource/Image/PopupBox/PopupCloseButton.png");
	m_title = addLabel("title", QRect(17, 4, 300, 27), QColor(163, 175, 191, 255));
	m_title->setAlignment(m_title->alignment() | Qt::AlignHCenter);
	m_separator = addSeparator(QPoint(13, 33), 308, true);
	m_time = addLabel("", QRect(215, 133, 125, 32), QColor(255, 0, 0, 255));
	m_time->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	QObject::connect(this, &DialogBase::timeRest, this, &DialogShow::timeUpdate);
	setAttribute(Qt::WA_NativeWindow);

}

void DialogShow::setExitVisible(bool visible)
{
	m_exit->setVisible(visible);
	if (visible == false)
	{
		m_cancelEscAltF4 = true;
	}
	else
	{
		m_cancelEscAltF4 = false;
	}
}

void DialogShow::timeUpdate(int32_t timeOut)
{
	if (timeOut <= 0)
	{
		m_time->setVisible(false);
	}
	m_time->setText(QString::fromStdWString(CStringManager::Format(L"����%d���Զ��ر�", timeOut)));
}

void DialogShow::paintEvent(QPaintEvent* eve)
{
	QLinearGradient gradient(QPointF(0, 0), QPoint(0, height()));
	gradient.setColorAt(0.08, QColor(31, 37, 61, 255));
	gradient.setColorAt(0.50, QColor(29, 33, 50, 255));
	gradient.setColorAt(0.92, QColor(27, 29, 41, 255));

	gradient.setSpread(QGradient::PadSpread);

	QPainter painter(this);

	painter.fillRect(QRect(0, 0, width(), height()), gradient);
	if (m_highLight)
	{
		painter.setPen(QColor(255, 0, 0, 255));
	}
	else
	{
		painter.setPen(QColor(75, 85, 134, 255));
	}
	painter.drawRect(0, 0, width() - 1, height() - 1);

	QDialog::paintEvent(eve);
}

void DialogShow::mousePressEvent(QMouseEvent *eve)
{
	if (eve->button() == Qt::LeftButton)
	{
		m_bPressed = true;
		m_point = eve->pos();
	}
}

void DialogShow::mouseMoveEvent(QMouseEvent* eve)
{
	if (m_bPressed)
	{
		move(eve->pos() - m_point + pos());
	}
}

void DialogShow::mouseReleaseEvent(QMouseEvent* eve)
{
	Q_UNUSED(eve);
	m_bPressed = false;
}

void DialogShow::closeEvent(QCloseEvent* eve)
{
	if (m_cancelEscAltF4)
	{
		eve->ignore();
	}
	else
	{
		eve->accept();
	}
	QDialog::closeEvent(eve);
}

bool DialogShow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	bool res = QDialog::nativeEvent(eventType, message, result);
	if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
	{
		MSG* msg = static_cast<MSG*>(message);
		switch (msg->message)
		{
		case WM_NCACTIVATE:
		{
			ncActiveChanged(msg->wParam);
		}
		break;
		default:
			break;
		}
	}
	return res;
}

void DialogShow::ncActiveChanged(int32_t wParam)
{
	m_highLight = !wParam;
	QDialog::repaint();
}