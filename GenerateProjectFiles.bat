@echo off
pushd %~dp0%

cmake -B Build -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
if not exist Build\InfamousEngine.sln (
    if not exist InfamousEngine.sln (
        mklink InfamousEngine.sln Build\InfamousEngine.sln
    )
)

popd
pause
