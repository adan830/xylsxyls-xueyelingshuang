set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CCharset.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CCharset\src\*.h"   "%xueyelingshuang%include\CCharset\"
xcopy /y /i /r /s "%bat%CCharset\src\*.inl" "%xueyelingshuang%include\CCharset\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CCharset\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CCharsetd.ilk"
del "%xueyelingshuang%lib\CCharsetd.exp"
