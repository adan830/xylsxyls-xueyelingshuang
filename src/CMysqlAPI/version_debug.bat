set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::��ȡ��������
call "%bat%public.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::���빤��
call "%bat%scripts\rebuild_CMysqlAPI.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ�
xcopy /y /i /r /s "%bat%CMysqlAPI\src\*.h" "%xueyelingshuang%include\CMysqlAPI\"
xcopy /y /i /r /s "%bat%CMysqlAPI\src\*.inl" "%xueyelingshuang%include\CMysqlAPI\"

xcopy /y /i /r /s "%bat%CMysqlAPI\props\*.props" "%xueyelingshuang%props\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CMysqlAPI\vcxproj\Debug\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\CMysqlAPId.ilk"
del "%xueyelingshuang%lib\CMysqlAPId.exp"