@echo off
pushd %~dp0%

cmake -B Build ^
    -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT_DIR%/scripts/buildsystems/vcpkg.cmake" ^
    -G "Visual Studio 17 2022"

if exist Build\InfamousEngine.sln (
    if not exist InfamousEngine.sln (
        mklink InfamousEngine.sln Build\InfamousEngine.sln
    )
)

popd
pause
