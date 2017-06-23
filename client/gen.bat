@echo off
set PCACHE=%PATH%

del /S /Q debug\
del /S /Q release\

del /Q ui_*.h

call vcvarsall.bat amd64
qmake client.pro -spec win32-msvc2015
jom qmake_all
jom Debug
jom Release

set PATH=%PCACHE%
del /Q ui_*.h