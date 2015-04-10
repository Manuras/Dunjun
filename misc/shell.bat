@echo off

::
::  To run this at startup, use this as your shortcut target:
::  %windir%\system32\cmd.exe /k w:\Dunjun\misc\shell.bat
::

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
set path=w:\Dunjun\misc;%path%
