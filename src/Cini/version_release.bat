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
call "%bat%scripts\rebuild_Cini.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%Cini\src\*.h"   "%xueyelingshuang%include\Cini\"
xcopy /y /i /r /s "%bat%Cini\src\*.inl" "%xueyelingshuang%include\Cini\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%Cini\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\Cini.ilk"
del "%xueyelingshuang%lib\Cini.exp"