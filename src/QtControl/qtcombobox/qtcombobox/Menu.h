#include <QMenu>
#include "ControlBase.h"

class Menu : public ControlBase < QMenu >
{
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
	Menu(QWidget* parent = NULL);

public:
	/** ���ñ�����ɫ
	@param [in] color ������ɫ
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBackgroundColor(const QColor& color, bool rePaint = false);

	/** ���ñ߿�ֶ�
	@param [in] width �߿�ֶ�
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderWidth(int32_t width, bool rePaint = false);

	/** ���ñ߿���ɫ
	@param [in] color ��̬
	@param [in] rePaint �Ƿ������ػ�
	*/
	void setBorderColor(const QColor& color, bool rePaint = false);
};