@echo off
::
:: This batch file is used to copy files from a project into the 
:: SDK Include directory. It also marks those files read only.
::

:: FIND THE SDK DIRECTORY 
:: Prefer the most local sdk dir, 
:: so order these checks such that local dirs set the variable last.
set SDK_INCLUDE=not_found
if exist ..\..\..\..\..\SDK set SDK_INCLUDE=..\..\..\..\..\SDK\Include
if exist ..\..\..\..\SDK    set SDK_INCLUDE=..\..\..\..\SDK\Include
if exist ..\..\..\SDK       set SDK_INCLUDE=..\..\..\SDK\Include
if (%SDK_INCLUDE%)==(not_found) goto :ERROR_NO_SDK

if not exist %SDK_INCLUDE% mkdir %SDK_INCLUDE%

echo (only copying new or modified files)

:: COPY STANDARD FILES
if exist Source\*.h      xcopy /D /F /I /R /Y Source\*.h      %SDK_INCLUDE%
if exist Source\*.inl    xcopy /D /F /I /R /Y Source\*.inl    %SDK_INCLUDE%

:: COPY USER SPECIFIED FILES
:==LOOP
if (%~1)==() goto LOOP_END
if exist "%~1" xcopy /D /F /I /R /Y "%~1" %SDK_INCLUDE%
shift
goto LOOP
:==LOOP_END

:: MARK FILES READ ONLY
if exist %SDK_INCLUDE% attrib +R %SDK_INCLUDE%\*

exit /b



:==ERROR_NO_SDK
echo %0: fatal error: Cannot locate SDK directory.
exit 1
