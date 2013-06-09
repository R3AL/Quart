@echo off

set includeDest="%VS110COMNTOOLS%..\..\VC\include\Quart"
set libDest="%VS110COMNTOOLS%..\..\VC\lib\Quart"

echo Removing old files...
rmdir /s /q %includeDest%
rmdir /s /q %libDest%
echo Done!

echo Copying new files...
XCOPY "Quart\include\Quart" %includeDest% /D /E /C /R /I /K /Y
XCOPY "Quart\lib\Quart" %libDest% /D /E /C /R /I /K /Y

echo Quart (re)installed !