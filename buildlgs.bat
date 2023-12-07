@rem <buildlgs.bat> -*- coding: cp932-dos -*-
@echo off
rem
rem Project owlnext-sample-listviewctrl-header
rem Copyright (C) 2023 neige68
rem
rem Note: library-generator-set ï  build
rem
rem Windows:   XP and lator
rem

rem %1 : LGS : "0" or "1"
rem %2 : UNICODE : "UNICODE" or ""

setlocal
set LGS=%1
set @bdir=build
if "%LGS%"=="1" set @bdir=build1
set @UNICODE=%2
if not "%@UNICODE%"=="" set @bdir=%@bdir%u
set @CMAKEOPT=
if not "%@UNICODE%"=="" set @CMAKEOPT=-D UNICODE=1

if not exist %@bdir% mkdir %@bdir%
pushd %@bdir%
echo cmake...
if "%LGS%"=="0" cmake -G "Visual Studio 16 2019" -A Win32 .. %@CMAKEOPT%
if "%LGS%"=="1" cmake -G "Visual Studio 16 2019" -A x64 .. %@CMAKEOPT%
echo ...cmake end
%@ionice% msbuild ALL_BUILD.vcxproj /m
if errorlevel 1 goto err
%@ionice% msbuild ALL_BUILD.vcxproj /m /p:Configuration=Release
if errorlevel 1 goto err
goto end

:err
echo buildlgs.bat: ÉGÉâÅ[Ç™Ç†ÇËÇ‹Ç∑.
popd
exit /b 1
:end
popd

rem end of <buildlgs.bat>
