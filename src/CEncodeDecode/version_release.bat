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
call "%bat%scripts\rebuild_CEncodeDecode.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CEncodeDecode\src\*.h"   "%xueyelingshuang%include\CEncodeDecode\"
xcopy /y /i /r /s "%bat%CEncodeDecode\src\*.inl" "%xueyelingshuang%include\CEncodeDecode\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CEncodeDecode\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CEncodeDecode.ilk"
del "%xueyelingshuang%lib\CEncodeDecode.exp"