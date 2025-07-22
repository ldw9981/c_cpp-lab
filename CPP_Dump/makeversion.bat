@echo off
setlocal enabledelayedexpansion

rem -- ��� ���� (�ʿ�� ����)
set VERSION_HEADER=%~dp0Version.h

rem -- ���� ���� ����
if exist "%VERSION_HEADER%" del "%VERSION_HEADER%"

rem -- Git ���丮 ���� ���� Ȯ��
if exist "../.git" (
    for /f %%i in ('git rev-parse --short HEAD') do (
        set GITHASH=%%i
    )
    echo #pragma once > "%VERSION_HEADER%"
    echo #define VERSION_STRING "Git Hash !GITHASH!" >> "%VERSION_HEADER%"
    goto :eof
)

rem -- SVN ���丮 ���� ���� Ȯ��
if exist "../.svn" (
    for /f "tokens=*" %%a in ('svn info ^| findstr /R "^Revision"') do (
        set "line=%%a"
    )
    for %%b in (!line!) do set "revNum=%%~nb"
    echo #pragma once > "%VERSION_HEADER%"
    echo #define VERSION_STRING "SVN Revision !revNum!" >> "%VERSION_HEADER%"
    goto :eof
)

rem -- �� �� �ƴ�: �⺻ ���ڿ�
echo #pragma once > "%VERSION_HEADER%"
echo #define VERSION_STRING "Unknown Version" >> "%VERSION_HEADER%"
