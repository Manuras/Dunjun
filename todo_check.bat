@echo off

echo.

set Wildcard=*.hpp *.cpp

echo TODOS FOUND:
findstr -s -n -i -l "TODO" %Wildcard%

echo.
echo -------
