@echo off
set PCACHE=%PATH%

call vcvars64.bat
qmake client.pro -spec win32-msvc2015
jom qmake_all
jom Debug
jom Release

set PATH=%PCACHE%