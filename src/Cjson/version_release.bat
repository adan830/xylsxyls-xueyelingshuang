::release-------------------------------------------------------------------------

set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\CStringManager\version_release.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_Cjson.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%Cjson\src\*.h"   "%xueyelingshuang%include\Cjson\"
xcopy /y /i /r /s "%bat%Cjson\src\*.inl" "%xueyelingshuang%include\Cjson\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%Cjson\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\Cjson.ilk"
del "%xueyelingshuang%lib\Cjson.exp"