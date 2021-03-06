@echo off

if not exist %~dp0prepare.bat (
  echo prepare.bat not exist. Copy prepare.bat.sample and edit it.
  goto :error
)
call %~dp0prepare.bat

mkdir %DISTDIR%
if not exist %DISTDIR%\ (
  echo %DISTDIR% is not accessible.
  goto :error
)

copy /y %~dp0README.md "%DISTDIR%\"
copy /y %~dp0history.txt "%DISTDIR%\"

if %PYTHONEXE%x==x (
  echo PYTHONEXE not defined.
  goto :error
)

if not exist %PYTHONEXE% (
  echo %PYTHONEXE% not found. Check the directory.
  goto :error
)
if not exist %QTROOT%\ (
  echo %QTROOT% not found. Check the directory.
  goto :error
)
if not exist %QTROOT%\%QTVERSION%\ (
  echo  %QTROOT%\%QTVERSION% not found. Check the directory.
  goto :error
)
if not exist %QTROOT%\%QTVERSION%\%QTVERSIONTOOLS%\ (
  echo %QTVERSIONTOOLS% not found. Check the directory.
  goto :error
)
::if not exist %QTROOT%\Tools\%QTTOOLS%\ (
::  echo %QTROOT%\Tools\%QTTOOLS% not found. Check the directory.
::  goto :error
::)


set QTPROJECTFILE=%SOURCEDIR%\%PRONAME%.pro
@echo on
%PYTHONEXE% ../distSolution/distqt.py %QTPROJECTFILE% -distdir "%DISTDIR%" -qtroot %QTROOT% -qtversion %QTVERSION% -qtversiontools %QTVERSIONTOOLS% -distfile dist.json -make %MAKE%
@echo off
if ERRORLEVEL 1 (
  goto :error
)


:success
::echo "Goint to close in 30 sec"
::ping 127.0.0.1 -n 30 > nul
::exit /b

:error
pause
exit /b
