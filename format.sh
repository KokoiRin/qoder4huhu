#!/bin/bash

# 代码格式化脚本 - 使用 clang-format 格式化所有 C++ 文件

echo "Running clang-format on all C++ source files..."

# 查找所有 .cpp 和 .h 文件并格式化
find Common DataLayer ServiceLayer PresentationLayer UILayer test \
    -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec clang-format -i --style=file {} \;

echo "Code formatting complete!"
