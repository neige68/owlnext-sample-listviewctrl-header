@rem <exec.bat> -*- coding: cp932-dos -*-
@echo off
rem
rem Project owlnext-sample-listviewctrl-header
rem Copyright (C) 2023 neige68
rem
rem Note: exec
rem
rem Windows:   XP and lator
rem

setlocal
pushd %~dp0
set @config=debug
set @bdir=build
set @u=
set @name=sample
:loop
if "%1"=="--" goto optbreak
if "%1"=="0" goto build0
if "%1"=="1" goto build1
if "%1"=="r" goto rel
if "%1"=="rel" goto rel
if "%1"=="d" goto deb
if "%1"=="deb" goto deb
if "%1"=="u" goto unicode
if "%1"=="" goto optbreak
goto optend
:rel
set @config=release
shift
goto loop
:deb
set @config=debug
shift
goto loop
:unicode
set @u=u
shift
goto loop
:build0
set @bdir=build
shift
goto loop
:build1
set @bdir=build1
shift
goto loop
:optbreak
shift
:optend
if not "%1"=="" set @name=%1
set @exe=%@bdir%%@u%\%@config%\%@name%.exe
if not exist %@bdir%%@u%\%@config%\%@name%.exe set @exe=%@bidr%%@u%\%@name%\%@config%\%@name%.exe
echo exec.bat: %@exe%
%@exe% %2 %3 %4 %5 %6 %7 %8 %9
goto :EOF
:help
echo usage: exec [0/1] [u] [deb/rel] [--] name

@rem end of <exec.bat>
