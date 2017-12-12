#pragma once
#include "LineEdit.h"

class COriginalButton;
/** ���������
*/
class CPasswordInputBox : public LineEdit
{
    Q_OBJECT
public:
	/** ���캯��
	@param [in] parent ������ָ��
	*/
    CPasswordInputBox(QWidget* parent = nullptr);

	/** ��������
	*/
    ~CPasswordInputBox();

public:
	/** ����Ĭ��ֵ
	*/
	void setDefault();
	
private:
    void layoutControl();
	void resizeEvent(QResizeEvent* eve);

private slots:
	void onMaskButtonClicked();

private:
	COriginalButton* m_maskButton;
};