set bat=%~dp0
set xueyelingshuang=%bat%..\..\..\

del "%xueyelingshuang%include\DmSoft\Cdmsoft.h"
xcopy /y /i /r /s "%xueyelingshuang%tools\��Į���\dm.dll" "%xueyelingshuang%lib\"