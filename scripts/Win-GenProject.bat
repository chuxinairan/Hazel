@echo off
Pushd ..\
CALL vendor\premake\premake5.exe vs2019
Popd
PAUSE