set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CBigNumber.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CBigNumber\src\*.h"   "%xueyelingshuang%include\CBigNumber\"
xcopy /y /i /r /s "%bat%CBigNumber\src\*.inl" "%xueyelingshuang%include\CBigNumber\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CBigNumber\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CBigNumberd.ilk"
del "%xueyelingshuang%lib\CBigNumberd.exp"


