set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_MulPoint.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%MulPoint\src\*.h"   "%xueyelingshuang%include\MulPoint\"
xcopy /y /i /r /s "%bat%MulPoint\src\*.inl" "%xueyelingshuang%include\MulPoint\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%MulPoint\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\MulPointd.ilk"
del "%xueyelingshuang%lib\MulPointd.exp"
