set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::���빤��
call "%bat%scripts\rebuild_CStopWatch.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ�
xcopy /y /i /r /s "%bat%CStopWatch\src\*.h" "%xueyelingshuang%include\CStopWatch\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CStopWatch\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CStopWatch.ilk"
del "%xueyelingshuang%lib\CStopWatch.exp"