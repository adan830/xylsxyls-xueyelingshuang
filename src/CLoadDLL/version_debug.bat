set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\CStringManager\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CLoadDLL.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CLoadDLL\src\*.h"   "%xueyelingshuang%include\CLoadDLL\"
xcopy /y /i /r /s "%bat%CLoadDLL\src\*.inl" "%xueyelingshuang%include\CLoadDLL\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CLoadDLL\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CLoadDLLd.ilk"
del "%xueyelingshuang%lib\CLoadDLLd.exp"
