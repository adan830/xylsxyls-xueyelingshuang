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
call "%bat%scripts\rebuild_SpeakClass.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%SpeakClass\src\*.h"   "%xueyelingshuang%include\SpeakClass\"
xcopy /y /i /r /s "%bat%SpeakClass\src\*.inl" "%xueyelingshuang%include\SpeakClass\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%SpeakClass\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\SpeakClass.ilk"
del "%xueyelingshuang%lib\SpeakClass.exp"