set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\CAceTCPClient\version_release.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CAceTCPServer.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CAceTCPServer\src\*.h"   "%xueyelingshuang%include\CAceTCPServer\"
xcopy /y /i /r /s "%bat%CAceTCPServer\src\*.inl" "%xueyelingshuang%include\CAceTCPServer\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CAceTCPServer\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CAceTCPServer.ilk"
del "%xueyelingshuang%lib\CAceTCPServer.exp"
