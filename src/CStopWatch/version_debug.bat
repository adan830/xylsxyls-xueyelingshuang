set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::���빤��
call "%bat%scripts\rebuild_CStopWatch.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ�
xcopy /y /i /r /s "%bat%CStopWatch\src\*.h" "%xueyelingshuang%include\CStopWatch\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CStopWatch\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CStopWatchd.ilk"
del "%xueyelingshuang%lib\CStopWatchd.exp"