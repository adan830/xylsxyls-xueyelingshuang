set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CCheckUSB.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CCheckUSB\src\*.h"   "%xueyelingshuang%include\CCheckUSB\"
xcopy /y /i /r /s "%bat%CCheckUSB\src\*.inl" "%xueyelingshuang%include\CCheckUSB\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CCheckUSB\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CCheckUSBd.ilk"
del "%xueyelingshuang%lib\CCheckUSBd.exp"
