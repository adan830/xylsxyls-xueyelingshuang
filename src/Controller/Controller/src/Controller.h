#pragma once
#include "Control.h"
#include "ControllerMacro.h"

class ControllerAPI Controller{
public:
    //����
    Control* CreateControl(string strControl, bool ifChoke = false);
    void SetChoke(Control* control);
    void SetUnChoke(Control* control);
    //�������ļ���
    void SetTempControl(Control* control, string nextControl);
};