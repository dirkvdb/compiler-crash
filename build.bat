SET projectdir=%cd%
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
cd %projectdir%

mkdir build
cd build\

cmake ^
    -G "Visual Studio 16 2019" ^
    -A x64 ^
    ..
cmake --build . --config Release
pause