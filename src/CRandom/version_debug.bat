set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CRandom.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CRandom\src\*.h"   "%xueyelingshuang%include\CRandom\"
xcopy /y /i /r /s "%bat%CRandom\src\*.inl" "%xueyelingshuang%include\CRandom\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CRandom\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CRandomd.ilk"
del "%xueyelingshuang%lib\CRandomd.exp"
