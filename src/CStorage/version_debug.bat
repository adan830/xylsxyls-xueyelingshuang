set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::����boost��̬��
xcopy /y /i /r /s "%BOOST_ROOT%\lib32-msvc-11.0\*.dll" "%xueyelingshuang%lib\"

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_debug.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_CStorage.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%CStorage\src\*.h"   "%xueyelingshuang%include\CStorage\"
xcopy /y /i /r /s "%bat%CStorage\src\*.inl" "%xueyelingshuang%include\CStorage\"
xcopy /y /i /r /s "%bat%CStorage\props\*.props" "%xueyelingshuang%props\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CStorage\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CStoraged.ilk"
del "%xueyelingshuang%lib\CStoraged.exp"
