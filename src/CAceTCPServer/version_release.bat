::release-------------------------------------------------------------------------

set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::����tools
xcopy /y /i /r /s "%xueyelingshuang%tools\ACE_wrappers\ace\*"      "%xueyelingshuang%include\ace\"
xcopy /y /i /r /s "%xueyelingshuang%tools\ACE_wrappers\lib\vc11\*" "%xueyelingshuang%lib\"

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call %xueyelingshuang%src\Cjson\version_release.bat

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