@ echo off
rmdir /s /q build
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:\Qt\6.8.1\mingw_64"
cmake --build . --parallel 4
windeployqt C:\Users\auten\Documents\qtProyect\biblioteca2_0\build\BibliotecaApp1_0.exe

pause