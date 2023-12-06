@rem <build.bat> -*- coding: cp932-dos -*-
@echo off
rem
rem Project owlnext-sample-listviewctrl-header
rem Copyright (C) 2023 neige68
rem
rem Note: build
rem
rem Windows:   XP and lator
rem

setlocal
pushd %~dp0

set @ionice=
if not "%1"=="fg" set @ionice=ionicev

rem lgs0: vc142 x86
setlocal
call "%VC142%\vcvarsall.bat" x86
call buildlgs.bat 0
endlocal
if errorlevel 1 goto err
echo INFO: LGS0, non-UNICODE done.

rem lgs0: vc142 x86, UNICODE
setlocal
call "%VC142%\vcvarsall.bat" x86
call buildlgs.bat 0 UNICODE
endlocal
if errorlevel 1 goto err
echo INFO: LGS0, UNICODE done.

rem lgs1: vc142 x64
setlocal
call "%VC142%\vcvarsall.bat" x86
call buildlgs.bat 1
endlocal
if errorlevel 1 goto err
echo INFO: LGS1, non-UNICODE done.

rem lgs1: vc142 x64, UNICODE
setlocal
call "%VC142%\vcvarsall.bat" x86
call buildlgs.bat 1 UNICODE
endlocal
if errorlevel 1 goto err
echo INFO: LGS1, UNICODE done.

goto end

:err
echo build.bat: ÉGÉâÅ[Ç™Ç†ÇËÇ‹Ç∑.
:end
popd

rem end of <build.bat>
