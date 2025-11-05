@echo off
REM 代码格式化脚本 - 使用 clang-format 格式化所有 C++ 文件

echo Running clang-format on all C++ source files...

for /r Common %%f in (*.cpp *.h) do clang-format -i --style=file "%%f"
for /r DataLayer %%f in (*.cpp *.h) do clang-format -i --style=file "%%f"
for /r ServiceLayer %%f in (*.cpp *.h) do clang-format -i --style=file "%%f"
for /r PresentationLayer %%f in (*.cpp *.h) do clang-format -i --style=file "%%f"
for /r UILayer %%f in (*.cpp *.h) do clang-format -i --style=file "%%f"
for /r test %%f in (*.cpp *.h) do clang-format -i --style=file "%%f"

echo Code formatting complete!
pause
