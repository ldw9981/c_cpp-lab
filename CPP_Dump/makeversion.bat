@echo off
setlocal enabledelayedexpansion

rem -- 경로 설정 (필요시 수정)
set VERSION_HEADER=%~dp0Version.h

rem -- 이전 파일 제거
if exist "%VERSION_HEADER%" del "%VERSION_HEADER%"

rem -- Git 디렉토리 존재 여부 확인
if exist "../.git" (
    for /f %%i in ('git rev-parse --short HEAD') do (
        set GITHASH=%%i
    )
    echo #pragma once > "%VERSION_HEADER%"
    echo #define VERSION_STRING "Git Hash !GITHASH!" >> "%VERSION_HEADER%"
    goto :eof
)

rem -- SVN 디렉토리 존재 여부 확인
if exist "../.svn" (
    for /f "tokens=*" %%a in ('svn info ^| findstr /R "^Revision"') do (
        set "line=%%a"
    )
    for %%b in (!line!) do set "revNum=%%~nb"
    echo #pragma once > "%VERSION_HEADER%"
    echo #define VERSION_STRING "SVN Revision !revNum!" >> "%VERSION_HEADER%"
    goto :eof
)

rem -- 둘 다 아님: 기본 문자열
echo #pragma once > "%VERSION_HEADER%"
echo #define VERSION_STRING "Unknown Version" >> "%VERSION_HEADER%"
