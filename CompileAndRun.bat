@echo off
echo =================Clearing build=================
make clean
echo =================Compiling=================
make
echo =================Running=================
make run
:end