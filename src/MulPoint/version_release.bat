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
call "%bat%scripts\rebuild_MulPoint.py"

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
rmdir /q /s "%bat%MulPoint\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\MulPoint.ilk"
del "%xueyelingshuang%lib\MulPoint.exp"