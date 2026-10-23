@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
cl /nologo /LD mini_emulator.c steam_api64.def /Fe:steam_api64.dll
echo EXITCODE=%ERRORLEVEL%
