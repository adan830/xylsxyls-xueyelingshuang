::release-------------------------------------------------------------------------

set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_release.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CTaskThreadManager.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CTaskThreadManager\src\*.h"   "%xueyelingshuang%include\CTaskThreadManager\"
xcopy /y /i /r /s "%bat%CTaskThreadManager\src\*.inl" "%xueyelingshuang%include\CTaskThreadManager\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CTaskThreadManager\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CTaskThreadManager.ilk"
del "%xueyelingshuang%lib\CTaskThreadManager.exp"