::release-------------------------------------------------------------------------

set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::����tools
xcopy /y /i /r /s "%xueyelingshuang%tools\ACE_wrappers\ace\*"      "%xueyelingshuang%include\ace\"
xcopy /y /i /r /s "%xueyelingshuang%tools\ACE_wrappers\lib\vc11\*" "%xueyelingshuang%lib\"

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\Cjson\version_release.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\CStopWatch\version_release.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CAceTCPClient.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CAceTCPClient\src\*.h"   "%xueyelingshuang%include\CAceTCPClient\"
xcopy /y /i /r /s "%bat%CAceTCPClient\src\*.inl" "%xueyelingshuang%include\CAceTCPClient\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CAceTCPClient\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CAceTCPClient.ilk"
del "%xueyelingshuang%lib\CAceTCPClient.exp"