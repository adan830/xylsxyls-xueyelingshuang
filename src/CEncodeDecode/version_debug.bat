set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call %xueyelingshuang%src\..relyproj..\version_debug.bat

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CEncodeDecode.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CEncodeDecode\src\*.h"   "%xueyelingshuang%include\CEncodeDecode\"
xcopy /y /i /r /s "%bat%CEncodeDecode\src\*.inl" "%xueyelingshuang%include\CEncodeDecode\"


