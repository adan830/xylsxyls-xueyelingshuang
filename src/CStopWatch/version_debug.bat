set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::���빤��
call "%bat%scripts\rebuild_CStopWatch.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ�
xcopy /y /i /r /s "%bat%CStopWatch\src\*.h" "%xueyelingshuang%include\CStopWatch\"