::release-------------------------------------------------------------------------

set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::依赖tools
xcopy /y /i /r /s "%xueyelingshuang%tools\ACE_wrappers\ace\*"      "%xueyelingshuang%include\ace\"
xcopy /y /i /r /s "%xueyelingshuang%tools\ACE_wrappers\lib\vc11\*" "%xueyelingshuang%lib\"

::如果需要获取依赖dll-----------------------------------------------------------
call "%xueyelingshuang%src\Cjson\version_release.bat"

::call完之后都需要重新set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::如果需要获取依赖dll-----------------------------------------------------------
call "%xueyelingshuang%src\CStopWatch\version_release.bat"

::call完之后都需要重新set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::如果需要获取依赖dll-----------------------------------------------------------
call "%xueyelingshuang%src\CCharset\version_release.bat"

::call完之后都需要重新set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::如果需要获取依赖dll-----------------------------------------------------------

::编译工程
call "%bat%scripts\rebuild_CAceHttpClient.py"

::call完之后都需要重新set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::向公共部分提供文件，有的时候可能没有inl文件
xcopy /y /i /r /s "%bat%CAceHttpClient\src\*.h"   "%xueyelingshuang%include\CAceHttpClient\"
xcopy /y /i /r /s "%bat%CAceHttpClient\src\*.inl" "%xueyelingshuang%include\CAceHttpClient\"

::删除临时文件
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%CAceHttpClient\vcxproj\Release\"

::删除ilk，exp
del "%xueyelingshuang%lib\CAceHttpClient.ilk"
del "%xueyelingshuang%lib\CAceHttpClient.exp"