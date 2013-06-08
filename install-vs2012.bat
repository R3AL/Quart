@echo off
set includeDest="%VS110COMNTOOLS%..\..\VC\include\Quart"
set libDest="%VS110COMNTOOLS%..\..\VC\lib\Quart"

XCOPY "Quart\include\Quart" %includeDest% /D /E /C /R /I /K /Y
XCOPY "Quart\lib\Quart" %libDest% /D /E /C /R /I /K /Y

echo Quart installed !