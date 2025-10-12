#!/bin/bash

# 清理构建文件和缓存

echo "========================================"
echo "清理构建文件和缓存"
echo "========================================"
echo

echo "正在清理以下内容："
echo "- build/ 目录"
echo "- cmake-build-* 目录"
echo "- *.exe 文件"
echo "- test_results/*.xml 文件"
echo

read -p "确认清理？(y/n): " choice
if [[ ! "$choice" =~ ^[Yy]$ ]]; then
    echo "取消清理"
    exit 0
fi

echo
echo "开始清理..."

# 清理构建目录
if [ -d "build" ]; then
    echo "删除 build/ 目录..."
    rm -rf "build"
    echo "✓ build/ 目录已删除"
else
    echo "✓ build/ 目录不存在"
fi

# 清理CMake构建目录
for dir in cmake-build-*; do
    if [ -d "$dir" ]; then
        echo "删除 $dir 目录..."
        rm -rf "$dir"
        echo "✓ $dir 目录已删除"
    fi
done

# 清理可执行文件
for exe in *.exe; do
    if [ -f "$exe" ]; then
        echo "删除 $exe..."
        rm "$exe"
        echo "✓ $exe 已删除"
    fi
done

# 清理测试结果XML文件
if [ -d "test_results" ]; then
    for xml in test_results/*.xml; do
        if [ -f "$xml" ]; then
            echo "删除 $xml..."
            rm "$xml"
            echo "✓ $xml 已删除"
        fi
    done
fi

echo
echo "========================================"
echo "清理完成！"
echo "========================================"
echo

read -p "按回车键退出..."