@echo off
set PCACHE=%PATH%

del /S /Q debug\
del /S /Q release\

call vcvarsall.bat amd64
qmake server.pro -spec win32-msvc2015
jom qmake_all
jom Debug
jom Release

set PATH=%PCACHE%