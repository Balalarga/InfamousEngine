@echo off
pushd %~dp0%

cmake -B Build -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
mklink InfamousEngine.sln Build\InfamousEngine.sln

popd
pause