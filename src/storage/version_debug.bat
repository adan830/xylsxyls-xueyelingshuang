set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::����CMysqlAPI
if exist "%xueyelingshuang%src\CMysqlAPI\version_debug.bat" (
call "%xueyelingshuang%src\CMysqlAPI\version_debug.bat"
) else (
echo src\CMysqlAPI\version_debug.bat no exist
pause
exit
)

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::���빤��
call "%bat%scripts\rebuild_storage.py" debug

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\