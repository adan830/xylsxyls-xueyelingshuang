set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\CStringManager\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_IntDateTime.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%IntDateTime\src\*.h"   "%xueyelingshuang%include\IntDateTime\"
xcopy /y /i /r /s "%bat%IntDateTime\src\*.inl" "%xueyelingshuang%include\IntDateTime\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%IntDateTime\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\IntDateTimed.ilk"
del "%xueyelingshuang%lib\IntDateTimed.exp"