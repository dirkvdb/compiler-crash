SET projectdir=%cd%
CALL "C:\Program Files (x86)\Microsoft Visual Studio\Preview\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cd %projectdir%

mkdir build
mkdir build\
cd build\

cmake ^
    -G "Visual Studio 15 2017" ^
    -DCMAKE_GENERATOR_PLATFORM=x64 ^
    ..
cmake --build . --config Release
pause