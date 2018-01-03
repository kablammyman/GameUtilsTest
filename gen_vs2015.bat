if not exist "build_vs2015" mkdir build_vs2015
if not exist "x64\Debug" mkdir x64\Debug
if not exist "x64\Release" mkdir x64\Release

cd build_vs2015

cmake -G "Visual Studio 15 2017 Win64" ..

cd ..