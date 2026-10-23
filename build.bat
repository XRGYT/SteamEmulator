@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" >nul
cl /nologo /LD mini_emulator.c steam_api.def /Fe:steam_api.dll
echo EXITCODE=%ERRORLEVEL%
