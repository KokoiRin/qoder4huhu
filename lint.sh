#!/bin/bash

# 静态代码分析脚本 - 使用 clang-tidy 检查所有 C++ 文件

echo "Running clang-tidy static analysis..."

# 确保编译数据库存在
if [ ! -f "build/compile_commands.json" ]; then
    echo "Generating compile_commands.json..."
    mkdir -p build
    cd build
    cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cd ..
fi

# 查找所有 .cpp 文件并进行静态分析
find Common DataLayer ServiceLayer PresentationLayer UILayer test \
    -type f -name "*.cpp" \
    -exec clang-tidy {} -p build \;

echo "Static analysis complete!"
