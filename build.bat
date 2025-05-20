@echo off
echo Building Student Report Card System...

REM Update these paths according to your MySQL installation
set MYSQL_INCLUDE_DIR=C:\Program Files\MySQL\MySQL Server 8.0\include
set MYSQL_LIB_DIR=C:\Program Files\MySQL\MySQL Server 8.0\lib

REM Compile the program
g++ student_report_card.cpp -o report_card.exe -I"%MYSQL_INCLUDE_DIR%" -L"%MYSQL_LIB_DIR%" -lmysqlclient

if %ERRORLEVEL% EQU 0 (
    echo Build successful! You can now run report_card.exe
) else (
    echo Build failed. Please check your MySQL paths and installation.
    echo Make sure to update the MySQL paths in this script.
)

pause
