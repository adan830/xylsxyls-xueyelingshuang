::release-------------------------------------------------------------------------

set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�����Ҫ��ȡ����dll-----------------------------------------------------------
call "%xueyelingshuang%src\..relyproj..\version_release.bat"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\
::�����Ҫ��ȡ����dll-----------------------------------------------------------

::���빤��
call "%bat%scripts\rebuild_DmSoft.py"

::call��֮����Ҫ����set
set bat=%~dp0
set xueyelingshuang=%bat%..\..\

::�򹫹������ṩ�ļ����е�ʱ�����û��inl�ļ�
xcopy /y /i /r /s "%bat%DmSoft\src\*.h"   "%xueyelingshuang%include\DmSoft\"
xcopy /y /i /r /s "%bat%DmSoft\src\*.inl" "%xueyelingshuang%include\DmSoft\"
del "%xueyelingshuang%include\DmSoft\Cdmsoft.h"
xcopy /y /i /r /s "%xueyelingshuang%tools\��Į���\dm.dll" "%xueyelingshuang%lib\"

::ɾ����ʱ�ļ�
del "%bat%@AutomationLog.txt"
del "%bat%scripts\@AutomationLog.txt"
del "%bat%scripts\msbuild.log"
rmdir /q /s "%bat%DmSoft\vcxproj\Release\"

::ɾ��ilk��exp
del "%xueyelingshuang%lib\DmSoft.ilk"
del "%xueyelingshuang%lib\DmSoft.exp"