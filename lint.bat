@echo off
REM 静态代码分析脚本 - 使用 clang-tidy 检查所有 C++ 文件

echo Running clang-tidy static analysis...

if not exist "build\compile_commands.json" (
    echo Generating compile_commands.json...
    if not exist build mkdir build
    cd build
    cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cd ..
)

echo Analyzing source files...

for /r Common %%f in (*.cpp) do clang-tidy "%%f" -p build
for /r DataLayer %%f in (*.cpp) do clang-tidy "%%f" -p build
for /r ServiceLayer %%f in (*.cpp) do clang-tidy "%%f" -p build
for /r PresentationLayer %%f in (*.cpp) do clang-tidy "%%f" -p build
for /r UILayer %%f in (*.cpp) do clang-tidy "%%f" -p build
for /r test %%f in (*.cpp) do clang-tidy "%%f" -p build

echo Static analysis complete!
pause
