set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::��ȡ��������
call "%bat%public.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::���빤��
call "%bat%scripts\rebuild_CMysqlAPI.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ�
xcopy /y /i /r /s "%bat%CMysqlAPI\src\*.h" "%xueyelingshuang%include\CMysqlAPI\"
xcopy /y /i /r /s "%bat%CMysqlAPI\src\*.inl" "%xueyelingshuang%include\CMysqlAPI\"

xcopy /y /i /r /s "%bat%CMysqlAPI\props\*.props" "%xueyelingshuang%props\"